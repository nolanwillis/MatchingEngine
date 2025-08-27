#include "Order.h"

#include <assert.h>
#include <atomic>
#include <string>
#include <chrono>

Order::Order()
	:
	Message(Message::Type::Order),
	symbol(Stock::Symbol::NA),
	price(0.0f),
	quantity(0),
	orderID(Order::GetNewOrderID()),
	userID(0),
	isBuy(false),
	orderType(Order::Type::Uninitialized)
{}
Order::Order(Stock::Symbol symbol, float price, unsigned int quantity,
	unsigned int userID, unsigned int isBuy, Order::Type orderType)
	:
	Message(Message::Type::Order),
	symbol(symbol),
	price(price),
	quantity(quantity),
	orderID(Order::GetNewOrderID()),
	userID(userID),
	isBuy(isBuy),
	orderType(orderType)
{}
Order::Order(const Order& rhs)
	:
	Message(Message::Type::Order),
	symbol(rhs.symbol),
	price(rhs.price),
	quantity(rhs.quantity),
	orderID(rhs.orderID),
	userID(rhs.userID),
	isBuy(rhs.isBuy),
	orderType(rhs.orderType)
{}
Order& Order::operator=(const Order& rhs)
{
	if (&rhs != this)
	{
		this->symbol = rhs.symbol;
		this->price = rhs.price;
		this->quantity = rhs.quantity;
		this->orderID = rhs.orderID;
		this->userID = rhs.userID;
		this->isBuy = rhs.isBuy;
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
	// orderID
	memcpy_s(
		buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) + 
		sizeof(unsigned int),
		sizeof(unsigned int),
		&this->orderID,
		sizeof(unsigned int)
	);
	// userID
	memcpy_s(
		buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) + 
		sizeof(unsigned int) * 2,
		sizeof(unsigned int),
		&this->userID,
		sizeof(unsigned int)
	);
	// isBuy
	memcpy_s(
		buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) +
		sizeof(unsigned int) * 3,
		sizeof(unsigned int),
		&this->isBuy,
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
	// orderID
	// Skipped because when receiving data and deserilizing into a new Order, 
	// the order auto generates an orderID. 
	//memcpy_s(
	//	&this->orderID,
	//	sizeof(unsigned int),
	//	buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) + 
	//	sizeof(unsigned int),
	//	sizeof(unsigned int)
	//);
	// userID
	memcpy_s(
		&this->userID,
		sizeof(unsigned int),
		buffer + sizeof(Message::Type) + sizeof(Stock::Symbol) + sizeof(float) + 
		sizeof(unsigned int) * 2,
		sizeof(unsigned int)
	);
	// isBuy
	memcpy_s(
		&this->isBuy,
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
size_t Order::GetSerializedSize() const
{
	return Message::GetSerializedSize() + sizeof(Stock::Symbol) + sizeof(float) +
		sizeof(unsigned int) * 4 + sizeof(Order::Type);
}
void Order::Print() const
	{
		printf("\t{ [Symbol]: %s [Price]: $%.4f [Quantity]: %u [Order ID]: %u [User ID]: %u", 
			Stock::ToString(symbol), price, quantity, orderID, userID);

		if (orderType == Order::Type::Limit)
		{
			isBuy ? printf("[Type]: Buy Limit Order }\n") : 
				printf("[Type]: Sell Limit Order }\n");
		}
		else if (orderType == Order::Type::Market)
		{
			isBuy ? printf("[Type]: Buy Market Order }\n") : 
				printf("[Type]: Sell Market Order } \n");
		}
	}

unsigned int Order::GetNewOrderID()
{
	using namespace std::chrono;

	// Get current time since epoch in milliseconds
	auto now = system_clock::now();
	auto ms = duration_cast<milliseconds>(now.time_since_epoch()).count();

	// To avoid collisions within the same ms, add an atomic counter
	static std::atomic<unsigned int> counter{ 0 };
	unsigned int localCounter = counter++;

	// Combine: take lower 32 bits of ms and mix with counter
	return static_cast<unsigned int>((ms & 0xFFFFFFF0ULL) ^ localCounter);
}
