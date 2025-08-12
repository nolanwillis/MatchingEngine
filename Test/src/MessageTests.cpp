#include "gtest/gtest.h"
#include "Order.h"
#include "Stock.h"

using namespace MatchingEngine;

TEST(MessageTests, PlaceOrderMessageSerialization)
{
	Order order1;
	Order order2;
	
	order1.symbol = Stock::Symbol::AAA;
	order1.userID = 38950493040;
	order1.quantity = 50;
	order1.isBuy = 0;
	order1.price = 1200.0f;
	order1.orderType = Order::Type::Limit;

	char* dataBuffer = new char[order1.GetSerializedSize()];

	order1.Serialize(dataBuffer);
	order2.Deserialize(dataBuffer);

	EXPECT_EQ(order1.GetMessageType(), order2.GetMessageType());
	EXPECT_EQ(order1.symbol, order2.symbol);
	EXPECT_EQ(order1.userID, order2.userID);
	EXPECT_EQ(order1.quantity, order2.quantity);
	EXPECT_EQ(order1.isBuy, order2.isBuy);
	EXPECT_EQ(order1.price, order2.price);
	EXPECT_EQ(order1.orderType, order2.orderType);

	delete dataBuffer;
}
