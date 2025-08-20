#include "Engine.h"
#include "OrderBookManager.h"
#include "Order.h"
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
void Engine::BroadcastTrade(Trade& trade)
{
	Engine& instance = Engine::GetInstance();
	
	size_t size = trade.GetSerializedSize();
	char* data = new char[size];

	trade.Serialize(data);

	std::lock_guard<std::mutex> lock(instance.connectionMtx);
	for (auto& conn : instance.connections) 
	{
		websocketpp::lib::error_code ec;
		instance.webSocketServer.send(conn, data, size, websocketpp::frame::opcode::binary, ec);
		if (ec) 
		{
			printf("Broadcast error: %s\n", ec.message());
		}
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

		// Construct correct message from the JSON payload.
		std::unique_ptr<Message> newMessage;
		Message::Type messageType = (Message::Type)data[0];

		switch (messageType)
		{
		case Message::Type::Order:
			newMessage = std::make_unique<Order>();
			newMessage.get()->Deserialize(data);
			break;
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