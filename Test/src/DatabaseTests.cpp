#include "gtest/gtest.h"
#include "OrderBookManager.h"
#include "Stock.h"
#include "Trade.h"

// Make the private fields of OrderBook public.
#define private public
#include "DatabaseManager.h"
#undef private

using namespace MatchingEngine;

class DatabaseTests : public ::testing::Test
{
protected:
	void SetUp() override
	{
		DatabaseManager::Create();
		OrderBookManager::Create();
	}

	void TearDown() override
	{
		OrderBookManager::Destroy();
		DatabaseManager::Destroy();
	}
};

TEST_F(DatabaseTests, CanAddAndGetTrade)
{
	DatabaseManager& instance = DatabaseManager::GetInstance();

	instance.AddTrade(Stock::Symbol::AAA, 100.0f, 50, 8403, 3402, 1024, Order::Type::Limit);
	instance.WaitUntilWriterIsIdle();

	Trade trade2 = instance.GetTrade(1024);

	EXPECT_EQ(Stock::Symbol::AAA, trade2.symbol);
	EXPECT_EQ(100.0f, trade2.price);
	EXPECT_EQ(50, trade2.quantity);
	EXPECT_EQ(8403, trade2.buyOrderID);
	EXPECT_EQ(3402, trade2.sellOrderID);
	EXPECT_EQ(1024, trade2.userID);
	EXPECT_EQ(Order::Type::Limit, trade2.orderType);
}

//TEST_F(DatabaseTests, TradeAddedToDBOnMatch)
//{
//
//}