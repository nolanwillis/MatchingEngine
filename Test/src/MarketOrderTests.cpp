#include "gtest/gtest.h"
#include "Stock.h"
#include "Order.h"
#include "DatabaseManager.h"

// Make the private fields of OrderBook public.
#define private public
#include "OrderBook.h"
#undef private

#include <deque>

using namespace MatchingEngine;

class MarketOrderTests : public ::testing::Test
{
protected:
	OrderBook* orderBook;
	std::promise<void> stopSignal;

	void SetUp() override
	{
		DatabaseManager::Create();

		this->orderBook = new OrderBook(Stock::Symbol::AAA, stopSignal.get_future().share());
	}

	void TearDown() override
	{
		stopSignal.set_value();
		delete orderBook;

		DatabaseManager::Destroy();
	}
};

TEST_F(MarketOrderTests, ExecutedWithPartialFill)
{
	std::unique_ptr<Order>buyOrder1 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 0, 65, 0, 0, 1, Order::Type::Market);
	std::unique_ptr<Order>buyOrder2 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 100, 50, 1, 1, 1, Order::Type::Limit);
	std::unique_ptr<Order>buyOrder3 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 200, 50, 2, 2, 1, Order::Type::Limit);

	std::unique_ptr<Order>sellOrder1 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 0, 75, 3, 3, 0, Order::Type::Market);
	std::unique_ptr<Order>sellOrder2 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 300, 50, 4, 4, 0, Order::Type::Limit);
	std::unique_ptr<Order>sellOrder3 = 
		std::make_unique<Order>(Stock::Symbol::AAA, 400, 50, 5, 5, 0, Order::Type::Limit);

	orderBook->Add(std::move(sellOrder2));
	orderBook->Add(std::move(sellOrder3));
	orderBook->Add(std::move(buyOrder1));
	orderBook->Add(std::move(buyOrder2));
	orderBook->Add(std::move(buyOrder3));
	orderBook->Add(std::move(sellOrder1));

	orderBook->WaitUntilIdle();

	auto& buyOrders = orderBook->buyOrders.at(100);
	auto& sellOrders = orderBook->sellOrders.at(400);

	EXPECT_EQ(orderBook->buyOrders.size(), 1);
	EXPECT_EQ(orderBook->sellOrders.size(), 1);
	EXPECT_EQ(buyOrders.front()->quantity, 25);
	EXPECT_EQ(sellOrders.front()->quantity, 35);
}
TEST_F(MarketOrderTests, ExecutedWithFullFill)
{
	std::unique_ptr<Order>buyOrder1 = 
		std::make_unique<Order> (Stock::Symbol::AAA, 0, 100, 0, 0, 1, Order::Type::Market);
	std::unique_ptr<Order>buyOrder2 = 
		std::make_unique<Order> (Stock::Symbol::AAA, 100, 50, 1, 1, 1, Order::Type::Limit);
	std::unique_ptr<Order>buyOrder3 = 
		std::make_unique<Order> (Stock::Symbol::AAA, 200, 50, 2, 2, 1, Order::Type::Limit);

	std::unique_ptr<Order>sellOrder1 = 
		std::make_unique<Order> (Stock::Symbol::AAA, 0, 100, 3, 3, 0, Order::Type::Market);
	std::unique_ptr<Order>sellOrder2 = 
		std::make_unique<Order> (Stock::Symbol::AAA, 300, 50, 4, 4, 0, Order::Type::Limit);
	std::unique_ptr<Order>sellOrder3 = 
		std::make_unique<Order> (Stock::Symbol::AAA, 400, 50, 5, 5, 0, Order::Type::Limit);

	orderBook->Add(std::move(sellOrder2));
	orderBook->Add(std::move(sellOrder3));
	orderBook->Add(std::move(buyOrder1));
	orderBook->Add(std::move(buyOrder2));
	orderBook->Add(std::move(buyOrder3));
	orderBook->Add(std::move(sellOrder1));

	orderBook->WaitUntilIdle();

	EXPECT_EQ(orderBook->buyOrders.size(), 0);
	EXPECT_EQ(orderBook->sellOrders.size(), 0);
}