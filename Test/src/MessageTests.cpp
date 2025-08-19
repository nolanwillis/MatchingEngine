#include "gtest/gtest.h"
#include "Order.h"
#include "Trade.h"
#include "Stock.h"

using namespace MatchingEngine;

TEST(MessageTests, OrderMessageSerialization)
{
	Order order1;
	Order order2;

	order1.symbol = Stock::Symbol::AAA;
	order1.price = 1200.0f;
	order1.quantity = 50;
	order1.orderID = 4598;
	order1.userID = 3895;
	order1.isBuy = 0;
	order1.orderType = Order::Type::Limit;

	char* dataBuffer = new char[order1.GetSerializedSize()];

	order1.Serialize(dataBuffer);
	order2.Deserialize(dataBuffer);

	EXPECT_EQ(order1.GetMessageType(), order2.GetMessageType());
	EXPECT_EQ(order1.symbol, order2.symbol);
	EXPECT_EQ(order1.price, order2.price);
	EXPECT_EQ(order1.quantity, order2.quantity);
	EXPECT_EQ(order1.orderID, order2.orderID);
	EXPECT_EQ(order1.userID, order2.userID);
	EXPECT_EQ(order1.isBuy, order2.isBuy);
	EXPECT_EQ(order1.orderType, order2.orderType);

	delete dataBuffer;
}

TEST(MessageTests, TradeMessageSerialization)
{
	Trade trade1;
	Trade trade2;

	trade1.symbol = Stock::Symbol::AAA;
	trade1.price = 1200.0f;
	trade1.quantity = 50;
	trade1.buyOrderID = 9060;
	trade1.sellOrderID = 4598;
	trade1.userID = 3895;
	trade1.orderType = Order::Type::Limit;

	char* dataBuffer = new char[trade1.GetSerializedSize()];

	trade1.Serialize(dataBuffer);
	trade2.Deserialize(dataBuffer);

	EXPECT_EQ(trade1.GetMessageType(), trade2.GetMessageType());
	EXPECT_EQ(trade1.symbol, trade2.symbol);
	EXPECT_EQ(trade1.price, trade2.price);
	EXPECT_EQ(trade1.quantity, trade2.quantity);
	EXPECT_EQ(trade1.buyOrderID, trade2.buyOrderID);
	EXPECT_EQ(trade1.sellOrderID, trade2.sellOrderID);
	EXPECT_EQ(trade1.userID, trade2.userID);
	EXPECT_EQ(trade1.orderType, trade2.orderType);

	delete dataBuffer;
}