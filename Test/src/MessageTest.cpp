#include "gtest/gtest.h"

#include "PlaceOrderMessage.h"

TEST(NetworkMessageTests, PlaceOrderMessageSerialization)
{
	PlaceOrderMessage pom;
	PlaceOrderMessage pom2;
	
	pom.SetSymbol("AWSA");
	pom.userID = 38950493040;
	pom.quantity = 50;
	pom.isBuy = 0;
	pom.limit = 1200.0f;
	pom.orderType = PlaceOrderMessage::Type::Limit;

	char* dataBuffer2 = new char[pom.GetSerializedSize()];

	pom.Serialize(dataBuffer2);
	pom2.Deserialize(dataBuffer2);

	EXPECT_EQ(strcmp(pom.symbol, pom2.symbol), 0);
	EXPECT_EQ(pom.userID, pom2.userID);
	EXPECT_EQ(pom.quantity, pom2.quantity);
	EXPECT_EQ(pom.isBuy, pom2.isBuy);
	EXPECT_EQ(pom.limit, pom2.limit);
	EXPECT_EQ(pom.orderType, pom2.orderType);

	delete dataBuffer2;
}
