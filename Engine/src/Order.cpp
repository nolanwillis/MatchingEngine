#include "Order.h"

#include <assert.h>
#include <string>

namespace MatchingEngine
{
	Order::Order()
		:
		Message(Message::Type::PlaceOrder),
		symbol(Stock::Symbol::NA),
		userID(0),
		price(0.0f),
		quantity(0),
		isBuy(false),
		orderType(Order::Type::Uninitialized)
	{}
	Order::Order(Stock::Symbol symbol, unsigned int userID, unsigned int quantity, unsigned int isBuy, 
		float limit, Order::Type orderType)
		:
		Message(Message::Type::PlaceOrder),
		symbol(symbol),
		userID(userID),
		quantity(quantity),
		isBuy(isBuy),
		price(limit),
		orderType(orderType)
	{}
	Order::Order(const Order& rhs)
		:
		Message(Message::Type::PlaceOrder),
		symbol(rhs.symbol),
		userID(rhs.userID),
		quantity(rhs.quantity),
		isBuy(rhs.isBuy),
		price(rhs.price),
		orderType(rhs.orderType)
	{}
	Order& Order::operator=(const Order& rhs)
	{
		if (&rhs != this)
		{
			this->symbol = rhs.symbol;
			this->userID = rhs.userID;
			this->quantity = rhs.quantity;
			this->isBuy = rhs.isBuy;
			this->price = rhs.price;
			this->orderType = rhs.orderType;

		}

		return *this;
	}

	void Order::Serialize(char* buffer)
	{
		Message::Serialize(buffer);

		// symbol
		memcpy_s(
			buffer + sizeof(Type), 
			sizeof(Stock::Symbol),
			&this->symbol, 
			sizeof(Stock::Symbol)
		);
		// userID
		memcpy_s(
			buffer + sizeof(Type) + sizeof(Stock::Symbol), 
			sizeof(unsigned int),
			&this->userID, 
			sizeof(unsigned int)
		);
		// quantity
		memcpy_s(
			buffer + sizeof(Type) + sizeof(Stock::Symbol) + sizeof(unsigned int),
			sizeof(unsigned int),
			&this->quantity, 
			sizeof(unsigned int)
		);
		// isBuy
		memcpy_s(
			buffer + sizeof(Type) + sizeof(Stock::Symbol) + sizeof(unsigned int) * 2,
			sizeof(unsigned int),
			&this->isBuy, 
			sizeof(unsigned int)
		);
		// limit
		memcpy_s(
			buffer + sizeof(Type) + sizeof(Stock::Symbol) + sizeof(unsigned int) * 3,
			sizeof(float),
			&this->price, 
			sizeof(float)
		);
		// orderType
		memcpy_s(
			buffer + sizeof(Type) + sizeof(Stock::Symbol) + sizeof(unsigned int) * 3 + sizeof(float),
			sizeof(Type),
			&this->orderType, 
			sizeof(Type)
		);
	}
	void Order::Deserialize(char* buffer)
	{
		Message::Deserialize(buffer);

		// symbol
		memcpy_s(
			&this->symbol, 
			sizeof(Stock::Symbol),
			buffer + sizeof(Type),
			sizeof(Stock::Symbol)
		);
		// userID
		memcpy_s(
			&this->userID, 
			sizeof(unsigned int),
			buffer + sizeof(Type) + sizeof(Stock::Symbol), 
			sizeof(unsigned int)
		);
		// quantity
		memcpy_s(
			&this->quantity, 
			sizeof(unsigned int),
			buffer + sizeof(Type) + sizeof(Stock::Symbol) + sizeof(unsigned int),
			sizeof(unsigned int)
		);
		// isBuy
		memcpy_s(
			&this->isBuy, 
			sizeof(unsigned int),
			buffer + sizeof(Type) + sizeof(Stock::Symbol) + sizeof(unsigned int) * 2,
			sizeof(unsigned int)
		);
		// limit
		memcpy_s(
			&this->price, 
			sizeof(float),
			buffer + sizeof(Type) + sizeof(Stock::Symbol) + sizeof(unsigned int) * 3,
			sizeof(float)
		);
		// orderType
		memcpy_s(
			&this->orderType, 
			sizeof(Type),
			buffer +  sizeof(Type) + sizeof(Stock::Symbol) + sizeof(unsigned int) * 3 + sizeof(float),
			sizeof(Type)
		);
	}
	size_t Order::GetSerializedSize() const
	{
		return Message::GetSerializedSize() + sizeof(Stock::Symbol) + sizeof(userID) + 
			sizeof(quantity) + sizeof(isBuy) + sizeof(price) + sizeof(orderType);
	}
	void Order::Print() const
	{
		printf("\t{ Price: %4f Symbol: %s Quantity: %u User ID: %u ", price, Stock::ToString(symbol), 
			quantity, userID);


		if (orderType == Order::Type::Limit)
		{
			isBuy ? printf("Type: Buy Limit Order }\n") : printf("Type: Sell Limit Order }\n");
		}
		else if (orderType == Order::Type::Market)
		{
			isBuy ? printf("Type: Buy Market Order }\n") : printf("Type: Sell Market Order } \n");
		}
	}
}
