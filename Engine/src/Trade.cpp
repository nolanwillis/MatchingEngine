#include "Trade.h"

#include <assert.h>
#include <string>
#include <atomic>

namespace MatchingEngine
{
	Trade::Trade()
		:
		Message(Message::Type::Trade),
		symbol(Stock::Symbol::NA),
		price(0.0f),
		quantity(0),
		buyOrderID(0),
		sellOrderID(0),
		userID(0),
		orderType(Order::Type::Uninitialized)
	{}
	Trade::Trade(Stock::Symbol symbol, float price, unsigned int quantity,
		unsigned int buyOrderID, unsigned int sellOrderID, unsigned int userID, 
		Order::Type orderType)
		:
		Message(Message::Type::Trade),
		symbol(symbol),
		price(price),
		quantity(quantity),
		buyOrderID(buyOrderID),
		sellOrderID(sellOrderID),
		userID(userID),
		orderType(orderType)
	{}

	void Trade::Serialize(char* buffer)
	{
		Message::Serialize(buffer);

		// symbol
		memcpy_s(
			buffer + sizeof(Message::Type),
			sizeof(Stock::Symbol),
			&this->symbol,
			sizeof(Stock::Symbol)
		);
		// price
		memcpy_s(
			buffer + sizeof(Message::Type) + sizeof(Stock::Symbol),
			sizeof(float),
			&this->price,
			sizeof(float)
		);
		// quantity
		memcpy_s(
			buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float),
			sizeof(unsigned int),
			&this->quantity,
			sizeof(unsigned int)
		);
		// buyOrderID
		memcpy_s(
			buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) + 
			sizeof(unsigned int),
			sizeof(unsigned int),
			&this->buyOrderID,
			sizeof(unsigned int)
		);
		// sellUserID
		memcpy_s(
			buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) +
			sizeof(unsigned int) * 2,
			sizeof(unsigned int),
			&this->sellOrderID,
			sizeof(unsigned int)
		);
		// userID
		memcpy_s(
			buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) +
			sizeof(unsigned int) * 3,
			sizeof(unsigned int),
			&this->userID,
			sizeof(unsigned int)
		);
		// orderType
		memcpy_s(
			buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) +
			sizeof(unsigned int) * 4,
			sizeof(Order::Type),
			&this->orderType,
			sizeof(Order::Type)
		);
	}
	void Trade::Deserialize(char* buffer)
	{
		Message::Deserialize(buffer);

		// symbol
		memcpy_s(
			&this->symbol,
			sizeof(Stock::Symbol),
			buffer + sizeof(Message::Type),
			sizeof(Stock::Symbol)
		);
		// price
		memcpy_s(
			&this->price,
			sizeof(float),
			buffer + sizeof(Message::Type) + sizeof(Stock::Symbol),
			sizeof(float)
		);
		// quantity
		memcpy_s(
			&this->quantity,
			sizeof(unsigned int),
			buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float),
			sizeof(unsigned int)
		);
		// buyOrderID
		memcpy_s(
			&this->buyOrderID,
			sizeof(unsigned int),
			buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) +
			sizeof(unsigned int),
			sizeof(unsigned int)
		);
		// sellOrderID
		memcpy_s(
			&this->sellOrderID,
			sizeof(unsigned int),
			buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) +
			sizeof(unsigned int) * 2,
			sizeof(unsigned int)
		);
		// userID
		memcpy_s(
			&this->userID,
			sizeof(unsigned int),
			buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) +
			sizeof(unsigned int) * 3,
			sizeof(unsigned int)
		);
		// orderType
		memcpy_s(
			&this->orderType,
			sizeof(Order::Type),
			buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) +
			sizeof(unsigned int) * 4,
			sizeof(Order::Type)
		);
	}
	size_t Trade::GetSerializedSize() const
	{
		return Message::GetSerializedSize() + sizeof(Stock::Symbol) + sizeof(float) +
			sizeof(unsigned int) * 4 + sizeof(Order::Type);
	}
	void Trade::Print() const
	{
		printf("\t{ [Symbol]: %s [Price]: $%.4f [Quantity]: %u [Buy Order ID]: %u" 
			"[Sell Order ID] %u [User ID] %u",
			Stock::ToString(symbol), price, quantity, buyOrderID, sellOrderID, userID);

		if (orderType == Order::Type::Limit)
		{
			printf("[Type]: Limit }\n");
		}
		else if (orderType == Order::Type::Market)
		{
			printf("[Type]: Market }\n");
		}
	}
}