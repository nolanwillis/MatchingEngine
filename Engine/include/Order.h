#ifndef ORDER_H
#define ORDER_H

#include "Message.h"
#include "Stock.h"

class Order : public Message
{
public:
	enum class Type
	{
		Uninitialized,
		Market,
		Limit
	};

	Stock::Symbol symbol;
	float price;
	unsigned int quantity;
	unsigned int orderID;
	unsigned int userID;
	unsigned int isBuy;
	Order::Type orderType;

	Order();
	Order(Stock::Symbol symbol, float price, unsigned int quantity, 
		unsigned int orderID, unsigned int userID, unsigned int isBuy, 
		Order::Type orderType);
	Order(const Order& rhs);
	Order& operator=(const Order& rhs);
	virtual ~Order() = default;

	virtual void Serialize(char* buffer) override;
	virtual void Deserialize(char* buffer) override;
	virtual size_t GetSerializedSize() const override;
	virtual void Print() const override;
};

#endif
