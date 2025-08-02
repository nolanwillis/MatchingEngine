#include "PlaceOrderMessage.h"

#include <assert.h>
#include <string>

const static size_t SYMBOL_LENGTH = 5;

PlaceOrderMessage::PlaceOrderMessage()
	:
	Message(Message::Type::PlaceOrder),
	userID(0),
	limit(0.0f),
	quantity(0),
	isBuy(false),
	orderType(Type::Uninitialized),
	symbol(new char[SYMBOL_LENGTH])
{}
PlaceOrderMessage::~PlaceOrderMessage()
{
	if (this->symbol)
	{
		delete this->symbol;
		this->symbol = nullptr;
	}
}

void PlaceOrderMessage::Serialize(char* buffer)
{
	// symbol
	memcpy_s(
		buffer, 
		SYMBOL_LENGTH,
		this->symbol, 
		SYMBOL_LENGTH
	);
	// userID
	memcpy_s(
		buffer + SYMBOL_LENGTH, 
		sizeof(unsigned int),
		&this->userID, 
		sizeof(unsigned int)
	);
	// quantity
	memcpy_s(
		buffer + SYMBOL_LENGTH + sizeof(unsigned int), 
		sizeof(unsigned int),
		&this->quantity, 
		sizeof(unsigned int)
	);
	// isBuy
	memcpy_s(
		buffer + SYMBOL_LENGTH + sizeof(unsigned int) * 2,
		sizeof(unsigned int),
		&this->isBuy, 
		sizeof(unsigned int)
	);
	// limit
	memcpy_s(
		buffer + SYMBOL_LENGTH + sizeof(unsigned int) * 3,
		sizeof(float),
		&this->limit, 
		sizeof(float)
	);
	// orderType
	memcpy_s(
		buffer + SYMBOL_LENGTH + sizeof(unsigned int) * 3 + sizeof(float),
		sizeof(Type),
		&this->orderType, 
		sizeof(Type)
	);
}
void PlaceOrderMessage::Deserialize(char* buffer)
{
	// symbol
	memcpy_s(
		this->symbol, 
		SYMBOL_LENGTH,
		buffer, 
		SYMBOL_LENGTH
	);
	// userID
	memcpy_s(
		&this->userID, 
		sizeof(unsigned int),
		buffer + SYMBOL_LENGTH, 
		sizeof(unsigned int)
	);
	// quantity
	memcpy_s(
		&this->quantity, 
		sizeof(unsigned int),
		buffer + SYMBOL_LENGTH + sizeof(unsigned int),
		sizeof(unsigned int)
	);
	// isBuy
	memcpy_s(
		&this->isBuy, 
		sizeof(unsigned int),
		buffer + SYMBOL_LENGTH + sizeof(unsigned int) * 2,
		sizeof(unsigned int)
	);
	// limit
	memcpy_s(
		&this->limit, 
		sizeof(float),
		buffer + SYMBOL_LENGTH + sizeof(unsigned int) * 3,
		sizeof(float)
	);
	// orderType
	memcpy_s(
		&this->orderType, 
		sizeof(Type),
		buffer + SYMBOL_LENGTH + sizeof(unsigned int) * 3 + sizeof(float),
		sizeof(Type)
	);
}
size_t PlaceOrderMessage::GetSerializedSize() const
{
	return sizeof(char*) + sizeof(userID) + sizeof(quantity) + sizeof(isBuy) + 
		sizeof(limit) + sizeof(orderType);
}
void PlaceOrderMessage::Print() const
{
	printf("=============================\n");
	printf("     Symbol: %s\n", symbol);
	printf("    User ID: %u\n", userID);
	printf("   Quantity: %u\n", quantity);
	isBuy ? printf("     Is Buy: true\n") : printf("     Is Buy: false\n");

	if (orderType == Type::Limit)
	{
		printf("      Limit: $%.3f\n", limit);
		isBuy ? printf(" Order Type: Buy Limit Order\n") : 
			printf(" Order Type: Sell Limit Order\n");
	}
	else if (orderType == Type::Market)
	{
		isBuy ? printf(" Order Type: Buy Market Order\n") : printf(" Order Type: Sell Market Order\n");
	}
	printf("=============================\n");
}

void PlaceOrderMessage::SetSymbol(const char* symbolIn)
{
	assert(symbolIn);
	strcpy_s(this->symbol, SYMBOL_LENGTH, symbolIn);
}
