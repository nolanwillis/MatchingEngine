#include "Engine.h"
#include "DatabaseManager.h"
#include "OrderBookManager.h"
#include "Stock.h"
#include "Trade.h"
#include "User.h"

#include <gtest/gtest.h>

class DatabaseTests : public ::testing::Test
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
		Engine::Destroy();
	}
};

TEST_F(DatabaseTests, CanAddAndGetTrade)
{
	DatabaseManager& instance = *DatabaseManager::instance;

	instance.AddMessage(
		std::make_unique<Trade>(Stock::Symbol::AAA, 100.0f, 50, 8403, 
			3402, 1024, Order::Type::Limit)
	);
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

	Trade trade = DatabaseManager::GetTrade(2222);

	EXPECT_EQ(Stock::Symbol::AAA, trade.symbol);
	EXPECT_EQ(100.0f, trade.price);
	EXPECT_EQ(50, trade.quantity);
	EXPECT_EQ(1303, trade.buyOrderID);
	EXPECT_EQ(8939, trade.sellOrderID);
	EXPECT_EQ(2222, trade.userID);
	EXPECT_EQ(Order::Type::Limit, trade.orderType);
}

TEST_F(DatabaseTests, CanAddAndGetUser)
{
	DatabaseManager::AddUser("person1@gmail.com");
	DatabaseManager::AddUser("person2@gmail.com");

	User person1 = DatabaseManager::GetUser("person1@gmail.com");
	User person2 = DatabaseManager::GetUser("person2@gmail.com");
	User fakePerson = DatabaseManager::GetUser("fake_person@gmail.com");

	EXPECT_EQ(person1.userID, 1);
	EXPECT_EQ(person1.username, "person1@gmail.com");
	EXPECT_EQ(person2.userID, 2);
	EXPECT_EQ(person2.username, "person2@gmail.com");
	EXPECT_EQ(fakePerson.userID, 0);
	EXPECT_EQ(fakePerson.username, "");
}


