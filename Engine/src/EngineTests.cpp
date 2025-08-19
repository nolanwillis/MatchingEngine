#include "DatabaseManager.h"
#include "Engine.h"
#include "Order.h"
#include "OrderBookManager.h"

#include <gtest/gtest.h>
#include <string>

class EngineTests : public ::testing::Test
{
protected:
	Engine engine;

	void SetUp() override
	{
		DatabaseManager::Create();
		OrderBookManager::Create();

		std::shared_future<void> stopFuture = engine.stopSignal.get_future().share();

		// Manually create four EngineWorkers.
		for (int i = 0; i < 4; i++)
		{
			engine.workers.push_back(
				std::make_unique<EngineWorker>(engine, stopFuture, engine.routingQueueCV)
			);
			engine.workers.back()->Start();
		}
	}

	void TearDown() override
	{
		OrderBookManager::Destroy();
		DatabaseManager::Destroy();
	}
};

class FakeMessage
{
public:
	FakeMessage(const std::string& payload)
		: 
		payload(payload) 
	{}

	const std::string& get_payload() const
	{
		return payload;
	}

private:
	std::string payload;
};

TEST_F(EngineTests, WebsocketMessageWorks)
{
	// Create the serialized orders.
	std::unique_ptr<Order>newOrder1 =
		std::make_unique<Order>(Stock::Symbol::AAA, 100, 25, 0, 0, 1, Order::Type::Limit);
	std::unique_ptr<Order>newOrder2 =
		std::make_unique<Order>(Stock::Symbol::BBB, 100, 25, 1, 1, 1, Order::Type::Limit);
	std::unique_ptr<Order>newOrder3 =
		std::make_unique<Order>(Stock::Symbol::CCC, 100, 25, 2, 2, 1, Order::Type::Limit);
	std::unique_ptr<Order>newOrder4 =
		std::make_unique<Order>(Stock::Symbol::DDD, 100, 25, 3, 3, 1, Order::Type::Limit);
	size_t size = newOrder1->GetSerializedSize();
	char* serializedOrder1 = new char[size];
	char* serializedOrder2 = new char[size];
	char* serializedOrder3 = new char[size];
	char* serializedOrder4 = new char[size];
	newOrder1->Serialize(serializedOrder1);
	newOrder2->Serialize(serializedOrder2);
	newOrder3->Serialize(serializedOrder3);
	newOrder4->Serialize(serializedOrder4);
	
	// Create a fake websocket messages from the serialized orders. 
	std::string payload1(serializedOrder1, size);
	std::string payload2(serializedOrder2, size);
	std::string payload3(serializedOrder3, size);
	std::string payload4(serializedOrder4, size);
	FakeMessage fakeMessage1(payload1);
	FakeMessage fakeMessage2(payload2);
	FakeMessage fakeMessage3(payload3);
	FakeMessage fakeMessage4(payload4);

	// HandleMessage(). This is need because the normal HandleMessage function 
	// takes a websocketpp specific type, which can't be inherited from.
	try
	{
		// Deserialize the messages into orders.
		auto& dataRef1 = fakeMessage1.get_payload();
		char* data1 = const_cast<char*>(dataRef1.data());
		auto& dataRef2 = fakeMessage2.get_payload();
		char* data2 = const_cast<char*>(dataRef2.data());
		auto& dataRef3 = fakeMessage3.get_payload();
		char* data3 = const_cast<char*>(dataRef3.data());
		auto& dataRef4 = fakeMessage4.get_payload();
		char* data4 = const_cast<char*>(dataRef4.data());

		std::unique_ptr<Message> newMessage1 = std::make_unique<Order>();
			newMessage1->Deserialize(data1);
		std::unique_ptr<Message> newMessage2 = std::make_unique<Order>();
			newMessage2->Deserialize(data2);
		std::unique_ptr<Message> newMessage3 = std::make_unique<Order>();
			newMessage3->Deserialize(data3);
		std::unique_ptr<Message> newMessage4 = std::make_unique<Order>();
			newMessage4->Deserialize(data4);

		// Add the new message to the routing queue. 
		{
			std::lock_guard<std::mutex> lock(engine.routingQueueMtx);
			engine.routingQueue.emplace(std::move(newMessage1));
			engine.routingQueue.emplace(std::move(newMessage2));
			engine.routingQueue.emplace(std::move(newMessage3));
			engine.routingQueue.emplace(std::move(newMessage4));
		}
		engine.routingQueueCV.notify_all();
	}
	catch (std::exception& e)
	{
		printf("Invalid message: %s\n", e.what());
	}

	// Need to wait for one of the OrderBookWorkers.
	std::this_thread::sleep_for(std::chrono::milliseconds(5));

	Order* buyOrderAAA = OrderBookManager::instance->orderBooks.at(Stock::Symbol::AAA)
		.buyOrders.at(100).front().get();
	Order* buyOrderBBB = OrderBookManager::instance->orderBooks.at(Stock::Symbol::BBB)
		.buyOrders.at(100).front().get();
	Order* buyOrderCCC = OrderBookManager::instance->orderBooks.at(Stock::Symbol::CCC)
		.buyOrders.at(100).front().get();
	Order* buyOrderDDD = OrderBookManager::instance->orderBooks.at(Stock::Symbol::DDD)
		.buyOrders.at(100).front().get();

	EXPECT_TRUE
	(
		buyOrderAAA->symbol == Stock::Symbol::AAA && buyOrderAAA->price == 100 &&
		buyOrderAAA->quantity == 25 && buyOrderAAA->orderID == 0 &&
		buyOrderAAA->userID == 0 && buyOrderAAA->isBuy == 1 &&
		buyOrderAAA->orderType == Order::Type::Limit
	);

	EXPECT_TRUE
	(
		buyOrderBBB->symbol == Stock::Symbol::BBB && buyOrderBBB->price == 100 &&
		buyOrderBBB->quantity == 25 && buyOrderBBB->orderID == 1 &&
		buyOrderBBB->userID == 1 && buyOrderBBB->isBuy == 1 &&
		buyOrderBBB->orderType == Order::Type::Limit
	);

	EXPECT_TRUE
	(
		buyOrderCCC->symbol == Stock::Symbol::CCC && buyOrderCCC->price == 100 &&
		buyOrderCCC->quantity == 25 && buyOrderCCC->orderID == 2 &&
		buyOrderCCC->userID == 2 && buyOrderCCC->isBuy == 1 &&
		buyOrderCCC->orderType == Order::Type::Limit
	);

	EXPECT_TRUE
	(
		buyOrderDDD->symbol == Stock::Symbol::DDD && buyOrderDDD->price == 100 &&
		buyOrderDDD->quantity == 25 && buyOrderDDD->orderID == 3 &&
		buyOrderDDD->userID == 3 && buyOrderDDD->isBuy == 1 &&
		buyOrderDDD->orderType == Order::Type::Limit
	);

	delete[] serializedOrder4;
	delete[] serializedOrder3;
	delete[] serializedOrder2;
	delete[] serializedOrder1;
}