#include "Engine.h"
#include "DatabaseManager.h"
#include "OrderBookManager.h"
#include "Order.h"
#include "Login.h"
#include "Trade.h"

Engine* Engine::instance = nullptr;

Engine::Engine()
{
	// Set logging settings.
	webSocketServer.set_error_channels(websocketpp::log::elevel::all);
	webSocketServer.set_access_channels(websocketpp::log::alevel::all ^
		websocketpp::log::alevel::frame_payload);

	// Initialize asio.
	webSocketServer.init_asio();

	// Register handlers.
	webSocketServer.set_open_handler([this](connection_hdl handle) {
		std::lock_guard<std::mutex> lock(connectionMtx);
		connections.insert(handle);
	});
	webSocketServer.set_close_handler([this](connection_hdl handle) {
		// TODO: Remove user with this connection_hdl from the active user map.
		std::lock_guard<std::mutex> lock(connectionMtx);
		connections.erase(handle);
	});
	webSocketServer.set_message_handler([this](connection_hdl handle, message_ptr msg) {
		HandleMessage(handle, msg);
	});
}
Engine::~Engine()
{
	// Send the kill signal to the workers.
	stopSignal.set_value();

	// Tell the worker threads to check the stop signal condition. 
	routingQueueCV.notify_all();
}

void Engine::Create()
{
	if (!instance)
	{
		instance = new Engine();
	}
}
void Engine::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
	else
	{
		assert(false);
	}
}

void Engine::Run(uint16_t port, int threadCount)
{
	Engine& instance = Engine::GetInstance();

	instance.CreateWorkers(threadCount);
	
	instance.webSocketServer.listen(9002);
	instance.webSocketServer.start_accept();
	instance.webSocketServer.run();
}
void Engine::BroadcastTrade(Stock::Symbol symbol, float price, unsigned int quantity,
	unsigned int buyOrderID, unsigned int sellOrderID,
	unsigned int userID, Order::Type orderType)
{
	Engine& instance = Engine::GetInstance();

	Trade trade = Trade(symbol, price, quantity, buyOrderID, sellOrderID, userID, orderType);
	
	size_t size = trade.GetSerializedSize();
	char* data = new char[size];

	trade.Serialize(data);

	std::lock_guard<std::mutex> connectionLock(instance.connectionMtx);
	std::lock_guard<std::mutex> activeUserLock(instance.activeUserMapMtx);
	
	auto& connection = instance.activeUserMap[trade.userID];
	
	websocketpp::lib::error_code ec;
	instance.webSocketServer.send(connection, data, size, websocketpp::frame::opcode::binary, ec);
	if (ec) 
	{
		printf("Broadcast error: %s\n", ec.message());
	}

	delete[] data;
}

void Engine::VerifyLogin(std::unique_ptr<Login> login)
{
	Engine& instance = Engine::GetInstance();

	// Try to get the user from the database. 
	User user = DatabaseManager::GetUser(login->username);
	
	// Set correct values for sending back to the client. If the returned userID is < 0, then
	// the user was not found.
	if (user.userID > 0)
	{
		login->userID = user.userID;
		login->loginType = Login::Type::Acknowledge;

		// Add the user to the active user list.
		std::lock_guard<std::mutex> lock(instance.activeUserMapMtx);
		instance.activeUserMap[user.userID] = login->connectionHandle;
	}
	else
	{
		login->loginType = Login::Type::Reject;
	}

	// Send the Login message back to the client.
	size_t size = login->GetSerializedSize();
	char* data = new char[size];
	
	login->Serialize(data);
	
	std::lock_guard<std::mutex> lock(instance.connectionMtx);
	websocketpp::lib::error_code ec;
	instance.webSocketServer.send(login->connectionHandle, data, size, 
		websocketpp::frame::opcode::binary, ec);
	if (ec)
	{
		printf("Broadcast error: %s\n", ec.message());
	}
	delete[] data;
}

Engine& Engine::GetInstance()
{
	if (instance)
	{
		return(*instance);
	}
	assert(false);
}

void Engine::CreateWorkers(int numWorkers)
{
	std::shared_future stopFuture = stopSignal.get_future().share();

	for (int i = 0; i < numWorkers; i++)
	{
		workers.push_back(
			std::make_unique<EngineWorker>(*this, stopFuture, this->routingQueueCV)
		);
		workers.back()->Start();
	}
}
void Engine::HandleMessage(connection_hdl handle, message_ptr message)
{
	try
	{
		if (message->get_opcode() != websocketpp::frame::opcode::binary)
		{
			throw std::invalid_argument("wrong message type");
		}

		char* data = const_cast<char*>(message->get_payload().data());

		// Construct correct message from the payload data.
		std::unique_ptr<Message> newMessage = nullptr;
		Message::Type messageType = (Message::Type)data[0];

		switch (messageType)
		{
		case Message::Type::Order:
			{
				newMessage = std::make_unique<Order>();
				newMessage->Deserialize(data);
				break;
			}
		case Message::Type::Login:
			{
				// This currently won't work. It needs to be casted to a message ptr 
				// so it can go on a message queue. 
				std::unique_ptr<Login>newLoginMessage = std::make_unique<Login>();
				newLoginMessage->Deserialize(data);
				newLoginMessage->connectionHandle = handle;
				newMessage = std::move(newLoginMessage);
				break;
			}
		default:
			break;
		}

		// Add the new message to the routing queue and tell a worker to route it. 
		{
			std::lock_guard<std::mutex> lock(routingQueueMtx);
			routingQueue.emplace(std::move(newMessage));
		}
		routingQueueCV.notify_one();
	}
	catch (std::exception& e)
	{
		printf("Invalid message: %s\n", e.what());
	}
}