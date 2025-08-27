#include "Engine.h"
#include "DatabaseManager.h"
#include "OrderBookManager.h"

#include <gtest/gtest.h>

class OrderBookManagerTests : public ::testing::Test
{
protected:
	void SetUp() override
	{
		Engine::Create();
		DatabaseManager::Create();
		OrderBookManager::Create();
	}

	void TearDown() override
	{
		OrderBookManager::Destroy();
		DatabaseManager::Destroy();
		Engine::Create();
	}
};

TEST_F(OrderBookManagerTests, CreatesAllOrderBooks)
{
	OrderBookManager& instance = OrderBookManager::GetInstance();

	EXPECT_TRUE(instance.orderBooks.size() == (int)Stock::Symbol::COUNT - 1);

	for (int i = 1; i < (int)Stock::Symbol::COUNT; i++)
	{
		Stock::Symbol currentSymbol = (Stock::Symbol)i;
		EXPECT_TRUE(instance.orderBooks.contains(currentSymbol));
	}
}

TEST_F(OrderBookManagerTests, CanProcessOrders)
{
	std::unique_ptr<Order> buyOrder1 =
		std::make_unique<Order>(Stock::Symbol::AAA, 100, 50, 0, 1, Order::Type::Limit);
	std::unique_ptr<Order> buyOrder2 =
		std::make_unique<Order>(Stock::Symbol::BBB, 100, 50, 1, 1, Order::Type::Limit);
	std::unique_ptr<Order> buyOrder3 =
		std::make_unique<Order>(Stock::Symbol::CCC, 100, 50, 2, 1, Order::Type::Limit);
	std::unique_ptr<Order> buyOrder4 =
		std::make_unique<Order>(Stock::Symbol::DDD, 100, 50, 3, 1, Order::Type::Limit);
	std::unique_ptr<Order> buyOrder5 =
		std::make_unique<Order>(Stock::Symbol::EEE, 100, 50, 4, 1, Order::Type::Limit);

	std::unique_ptr<Order> sellOrder1 =
		std::make_unique<Order>(Stock::Symbol::AAA, 200, 50, 5, 0, Order::Type::Limit);
	std::unique_ptr<Order> sellOrder2 =
		std::make_unique<Order>(Stock::Symbol::BBB, 200, 50, 6, 0, Order::Type::Limit);
	std::unique_ptr<Order> sellOrder3 =
		std::make_unique<Order>(Stock::Symbol::CCC, 200, 50, 7, 0, Order::Type::Limit);
	std::unique_ptr<Order> sellOrder4 =
		std::make_unique<Order>(Stock::Symbol::DDD, 200, 50, 8, 0, Order::Type::Limit);
	std::unique_ptr<Order> sellOrder5 =
		std::make_unique<Order>(Stock::Symbol::EEE, 200, 50, 9, 0, Order::Type::Limit);

	OrderBookManager::AddMessage(std::move(buyOrder1));
	OrderBookManager::AddMessage(std::move(buyOrder2));
	OrderBookManager::AddMessage(std::move(buyOrder3));
	OrderBookManager::AddMessage(std::move(buyOrder4));
	OrderBookManager::AddMessage(std::move(buyOrder5));
	OrderBookManager::AddMessage(std::move(sellOrder1));
	OrderBookManager::AddMessage(std::move(sellOrder2));
	OrderBookManager::AddMessage(std::move(sellOrder3));
	OrderBookManager::AddMessage(std::move(sellOrder4));
	OrderBookManager::AddMessage(std::move(sellOrder5));

	// Wait for transactions to be processed. 
	std::this_thread::sleep_for(std::chrono::milliseconds(5));

	for (auto& [symbol, orderBook] : OrderBookManager::instance->orderBooks)
	{
		Order* buyOrder = orderBook.buyOrders.at(100).front().get();
		Order* sellOrder = orderBook.sellOrders.at(200).front().get();

		EXPECT_TRUE(buyOrder->symbol == symbol && buyOrder->price == 100);
		EXPECT_TRUE(sellOrder->symbol == symbol && sellOrder->price == 200);
	}
}