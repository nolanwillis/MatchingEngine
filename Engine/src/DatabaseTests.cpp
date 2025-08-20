#include "gtest/gtest.h"
#include "DatabaseManager.h"
#include "OrderBookManager.h"
#include "Stock.h"
#include "Trade.h"

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
	DatabaseManager& instance = *DatabaseManager::instance;

	instance.AddTrade(Trade(Stock::Symbol::AAA, 100.0f, 50, 8403, 3402, 1024, Order::Type::Limit));
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

TEST_F(DatabaseTests, TradeAddedToDBOnMatch)
{
	std::unique_ptr<Order>buyOrder =
		std::make_unique<Order>(Stock::Symbol::AAA, 100, 50, 1303, 3030, 1, Order::Type::Limit);

	std::unique_ptr<Order>sellOrder =
		std::make_unique<Order>(Stock::Symbol::AAA, 100, 50, 8939, 2222, 0, Order::Type::Limit);

	OrderBookManager::AddMessage(std::move(buyOrder));
	OrderBookManager::AddMessage(std::move(sellOrder));

	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	Trade user3030Trade = DatabaseManager::GetTrade(3030);
	Trade user2222Trade = DatabaseManager::GetTrade(2222);

	EXPECT_EQ(Stock::Symbol::AAA, user3030Trade.symbol);
	EXPECT_EQ(100.0f, user3030Trade.price);
	EXPECT_EQ(50, user3030Trade.quantity);
	EXPECT_EQ(1303, user3030Trade.buyOrderID);
	EXPECT_EQ(8939, user3030Trade.sellOrderID);
	EXPECT_EQ(3030, user3030Trade.userID);
	EXPECT_EQ(Order::Type::Limit, user3030Trade.orderType);
	
	EXPECT_EQ(Stock::Symbol::AAA, user2222Trade.symbol);
	EXPECT_EQ(100.0f, user2222Trade.price);
	EXPECT_EQ(50, user2222Trade.quantity);
	EXPECT_EQ(1303, user2222Trade.buyOrderID);
	EXPECT_EQ(8939, user2222Trade.sellOrderID);
	EXPECT_EQ(2222, user2222Trade.userID);
	EXPECT_EQ(Order::Type::Limit, user2222Trade.orderType);
}