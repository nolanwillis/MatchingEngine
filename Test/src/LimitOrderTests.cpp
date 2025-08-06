#include "gtest/gtest.h"
#include "Stock.h"

// Make the private fields of OrderBook public.
#define private public
#include "OrderBook.h"
#undef private

#include <deque>

using namespace MatchingEngine;

class LimitOrderTests : public ::testing::Test
{
protected:
	OrderBook* orderBook;  
	std::promise<void> stopSignal;

	void SetUp() override
	{
		this->orderBook = new OrderBook(Stock::Symbol::AAA, stopSignal.get_future().share());
	}

	void TearDown() override
	{
		stopSignal.set_value();
		delete orderBook;
	}
};

TEST_F(LimitOrderTests, AddedProperlyWithNoFills)
{
	Order buyOrder1(Stock::Symbol::AAA, 0, 50, 1, 100, Order::Type::Limit);
	Order buyOrder2(Stock::Symbol::AAA, 1, 50, 1, 200, Order::Type::Limit);
	Order buyOrder3(Stock::Symbol::AAA, 2, 50, 1, 300, Order::Type::Limit);
	Order buyOrder4(Stock::Symbol::AAA, 3, 50, 1, 400, Order::Type::Limit);
	Order buyOrder5(Stock::Symbol::AAA, 4, 50, 1, 500, Order::Type::Limit);

	Order sellOrder1(Stock::Symbol::AAA, 5, 50, 0, 600, Order::Type::Limit);
	Order sellOrder2(Stock::Symbol::AAA, 6, 50, 0, 700, Order::Type::Limit);
	Order sellOrder3(Stock::Symbol::AAA, 7, 50, 0, 800, Order::Type::Limit);
	Order sellOrder4(Stock::Symbol::AAA, 8, 50, 0, 900, Order::Type::Limit);
	Order sellOrder5(Stock::Symbol::AAA, 9, 50, 0, 1000, Order::Type::Limit);

	orderBook->Add(buyOrder1);
	orderBook->Add(buyOrder2);
	orderBook->Add(buyOrder3);
	orderBook->Add(buyOrder4);
	orderBook->Add(buyOrder5);
	orderBook->Add(sellOrder1);
	orderBook->Add(sellOrder2);
	orderBook->Add(sellOrder3);
	orderBook->Add(sellOrder4);
	orderBook->Add(sellOrder5);

	orderBook->WaitUntilIdle();

	EXPECT_EQ(orderBook->buyOrders.size(), 5);
	EXPECT_EQ(orderBook->sellOrders.size(), 5);
}

TEST_F(LimitOrderTests, AddedProperlyWithPartialFills)
{
	Order buyOrder1(Stock::Symbol::AAA, 0, 50, 1, 100, Order::Type::Limit);
	Order buyOrder2(Stock::Symbol::AAA, 1, 100, 1, 75, Order::Type::Limit);

	Order sellOrder1(Stock::Symbol::AAA, 2, 100, 0, 100, Order::Type::Limit);
	Order sellOrder2(Stock::Symbol::AAA, 3, 50, 0, 75, Order::Type::Limit);

	orderBook->Add(buyOrder1);
	orderBook->Add(sellOrder1);
	orderBook->Add(buyOrder2);
	orderBook->Add(sellOrder2);

	orderBook->WaitUntilIdle();

	auto& buyOrders = orderBook->buyOrders.at(75);
	auto& sellOrders = orderBook->sellOrders.at(100);

	EXPECT_EQ(orderBook->buyOrders.size(), 1);
	EXPECT_EQ(orderBook->sellOrders.size(), 1);
	EXPECT_EQ(buyOrders.front().quantity, 50);
	EXPECT_EQ(sellOrders.front().quantity, 50);
}
TEST_F(LimitOrderTests, AddedProperlyWithFullFills)
{
	Order buyOrder1(Stock::Symbol::AAA, 0, 50, 1, 100, Order::Type::Limit);
	Order buyOrder2(Stock::Symbol::AAA, 1, 50, 1, 75, Order::Type::Limit);

	Order sellOrder1(Stock::Symbol::AAA, 2, 50, 0, 100, Order::Type::Limit);
	Order sellOrder2(Stock::Symbol::AAA, 3, 50, 0, 75, Order::Type::Limit);

	orderBook->Add(buyOrder1);
	orderBook->Add(sellOrder1);
	orderBook->Add(buyOrder2);
	orderBook->Add(sellOrder2);

	orderBook->WaitUntilIdle();

	EXPECT_EQ(orderBook->buyOrders.size(), 0);
	EXPECT_EQ(orderBook->sellOrders.size(), 0);
}