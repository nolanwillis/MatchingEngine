#include "gtest/gtest.h"

// Make the private field of OrderBookManager public.
#define private public
#include "OrderBookManager.h"
#undef private

using namespace MatchingEngine;

class OrderBookManagerTests : public ::testing::Test
{
protected:
	void SetUp() override
	{
		OrderBookManager::Create();
	}

	void TearDown() override
	{
		OrderBookManager::Destroy();
	}
};

//TEST_F(OrderBookManagerTests, All)
//{
//	auto& instance = OrderBookManager::GetInstance();
//	EXPECT_TRUE(instance.CanProcessOrdersTest());
//}

TEST_F(OrderBookManagerTests, CreatesALLOrderBooks)
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
	auto& instance = OrderBookManager::GetInstance();

	std::unique_ptr<Order> buyOrder1 =
		std::make_unique<Order>(Stock::Symbol::AAA, 100, 50, 0, 0, 1, Order::Type::Limit);
	std::unique_ptr<Order> buyOrder2 =
		std::make_unique<Order>(Stock::Symbol::BBB, 100, 50, 1, 1, 1, Order::Type::Limit);
	std::unique_ptr<Order> buyOrder3 =
		std::make_unique<Order>(Stock::Symbol::CCC, 100, 50, 2, 2, 1, Order::Type::Limit);
	std::unique_ptr<Order> buyOrder4 =
		std::make_unique<Order>(Stock::Symbol::DDD, 100, 50, 3, 3, 1, Order::Type::Limit);
	std::unique_ptr<Order> buyOrder5 =
		std::make_unique<Order>(Stock::Symbol::EEE, 100, 50, 4, 4, 1, Order::Type::Limit);

	std::unique_ptr<Order> sellOrder1 =
		std::make_unique<Order>(Stock::Symbol::AAA, 200, 50, 5, 5, 0, Order::Type::Limit);
	std::unique_ptr<Order> sellOrder2 =
		std::make_unique<Order>(Stock::Symbol::BBB, 200, 50, 6, 6, 0, Order::Type::Limit);
	std::unique_ptr<Order> sellOrder3 =
		std::make_unique<Order>(Stock::Symbol::CCC, 200, 50, 7, 7, 0, Order::Type::Limit);
	std::unique_ptr<Order> sellOrder4 =
		std::make_unique<Order>(Stock::Symbol::DDD, 200, 50, 8, 8, 0, Order::Type::Limit);
	std::unique_ptr<Order> sellOrder5 =
		std::make_unique<Order>(Stock::Symbol::EEE, 200, 50, 9, 9, 0, Order::Type::Limit);

	instance.AddMessage(std::move(buyOrder1));
	instance.AddMessage(std::move(buyOrder2));
	instance.AddMessage(std::move(buyOrder3));
	instance.AddMessage(std::move(buyOrder4));
	instance.AddMessage(std::move(buyOrder5));
	instance.AddMessage(std::move(sellOrder1));
	instance.AddMessage(std::move(sellOrder2));
	instance.AddMessage(std::move(sellOrder3));
	instance.AddMessage(std::move(sellOrder4));
	instance.AddMessage(std::move(sellOrder5));

	// Wait for transactions to be processed. 
	std::this_thread::sleep_for(std::chrono::milliseconds(5));

	for (auto& [symbol, orderBook] : instance.orderBooks)
	{
		Order* buyOrder = orderBook.buyOrders.at(100).front().get();
		Order* sellOrder = orderBook.sellOrders.at(200).front().get();

		EXPECT_TRUE(buyOrder->symbol == symbol && buyOrder->price == 100);
		EXPECT_TRUE(sellOrder->symbol == symbol && sellOrder->price == 200);
	}
}