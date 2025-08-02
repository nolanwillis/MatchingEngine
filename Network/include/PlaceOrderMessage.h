#ifndef PLACE_ORDER_MESSAGE_H
#define PLACE_ORDER_MESSAGE_H

#include "Message.h"

class PlaceOrderMessage : public Message
{
public:
	enum class Type
	{
		Uninitialized,
		Market,
		Limit
	};

	char* symbol;
	unsigned int userID;
	unsigned int quantity;
	unsigned int isBuy;
	float limit;
	Type orderType;

	PlaceOrderMessage();
	PlaceOrderMessage(const PlaceOrderMessage& rhs) = delete;
	PlaceOrderMessage& operator=(const PlaceOrderMessage& rhs) = delete;
	virtual ~PlaceOrderMessage();

	virtual void Serialize(char* buffer) override;
	virtual void Deserialize(char* buffer) override;
	virtual size_t GetSerializedSize() const override;
	virtual void Print() const override;

	void SetSymbol(const char* symbolIn);
};

#endif
