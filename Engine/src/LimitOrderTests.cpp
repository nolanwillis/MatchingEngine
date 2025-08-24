#include "Engine.h"
#include "DatabaseManager.h"
#include "OrderBook.h"
#include "Stock.h"

#include <deque>
#include <gtest/gtest.h>

class LimitOrderTests : public ::testing::Test
{
protected:
	OrderBook* orderBook;  
	std::promise<void> stopSignal;

	void SetUp() override
	{
		Engine::Create();
		DatabaseManager::Create();
		
		this->orderBook = new OrderBook(Stock::Symbol::AAA, stopSignal.get_future().share());
	}

	void TearDown() override
	{
		stopSignal.set_value();
		delete orderBook;
		
		DatabaseManager::Destroy();
		Engine::Destroy();
	}
};

TEST_F(LimitOrderTests, AddedProperlyWithNoFills)
{
	std::unique_ptr<Order>buyOrder1 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 100, 50, 0, 0, 1, Order::Type::Limit);
	std::unique_ptr<Order>buyOrder2 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 200, 50, 1, 1, 1, Order::Type::Limit);
	std::unique_ptr<Order>buyOrder3 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 300, 50, 2, 2, 1, Order::Type::Limit);
	std::unique_ptr<Order>buyOrder4 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 400, 50, 3, 3, 1, Order::Type::Limit);
	std::unique_ptr<Order>buyOrder5 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 500, 50, 4, 4, 1, Order::Type::Limit);

	std::unique_ptr<Order>sellOrder1 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 600, 50, 5, 5, 0, Order::Type::Limit);
	std::unique_ptr<Order>sellOrder2 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 700, 50, 6, 6, 0, Order::Type::Limit);
	std::unique_ptr<Order>sellOrder3 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 800, 50, 7, 7, 0, Order::Type::Limit);
	std::unique_ptr<Order>sellOrder4 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 900, 50, 8, 8, 0, Order::Type::Limit);
	std::unique_ptr<Order>sellOrder5 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 1000, 50, 9, 9, 0, Order::Type::Limit);

	orderBook->Add(std::move(buyOrder1));
	orderBook->Add(std::move(buyOrder2));
	orderBook->Add(std::move(buyOrder3));
	orderBook->Add(std::move(buyOrder4));
	orderBook->Add(std::move(buyOrder5));
	orderBook->Add(std::move(sellOrder1));
	orderBook->Add(std::move(sellOrder2));
	orderBook->Add(std::move(sellOrder3));
	orderBook->Add(std::move(sellOrder4));
	orderBook->Add(std::move(sellOrder5));

	orderBook->WaitUntilIdle();

	EXPECT_EQ(orderBook->buyOrders.size(), 5);
	EXPECT_EQ(orderBook->sellOrders.size(), 5);
}

TEST_F(LimitOrderTests, AddedProperlyWithPartialFills)
{
	std::unique_ptr<Order>buyOrder1 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 100, 50, 0, 0, 1, Order::Type::Limit);
	std::unique_ptr<Order>buyOrder2 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 75, 100, 1, 1, 1, Order::Type::Limit);

	std::unique_ptr<Order>sellOrder1 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 100, 100, 2, 2, 0, Order::Type::Limit);
	std::unique_ptr<Order>sellOrder2 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 75, 50, 3, 3, 0, Order::Type::Limit);

	orderBook->Add(std::move(buyOrder1));
	orderBook->Add(std::move(sellOrder1));
	orderBook->Add(std::move(buyOrder2));
	orderBook->Add(std::move(sellOrder2));

	orderBook->WaitUntilIdle();

	auto& buyOrders = orderBook->buyOrders.at(75);
	auto& sellOrders = orderBook->sellOrders.at(100);

	EXPECT_EQ(orderBook->buyOrders.size(), 1);
	EXPECT_EQ(orderBook->sellOrders.size(), 1);
	EXPECT_EQ(buyOrders.front()->quantity, 50);
	EXPECT_EQ(sellOrders.front()->quantity, 50);
}
TEST_F(LimitOrderTests, AddedProperlyWithFullFills)
{
	std::unique_ptr<Order>buyOrder1 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 100, 50, 0, 0, 1, Order::Type::Limit);
	std::unique_ptr<Order>buyOrder2 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 75, 50, 1, 1, 1, Order::Type::Limit);

	std::unique_ptr<Order>sellOrder1 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 100, 50, 2, 2, 0, Order::Type::Limit);
	std::unique_ptr<Order>sellOrder2 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 75, 50, 3, 3, 0, Order::Type::Limit);

	orderBook->Add(std::move(buyOrder1));
	orderBook->Add(std::move(sellOrder1));
	orderBook->Add(std::move(buyOrder2));
	orderBook->Add(std::move(sellOrder2));

	orderBook->WaitUntilIdle();

	EXPECT_EQ(orderBook->buyOrders.size(), 0);
	EXPECT_EQ(orderBook->sellOrders.size(), 0);
}
