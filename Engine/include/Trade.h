#ifndef TRADE_H
#define TRADE_H

#include "Message.h"
#include "Stock.h"
#include "Order.h"

class Trade : public Message
{
public:
	Stock::Symbol symbol;
	float price;
	unsigned int quantity;
	unsigned int buyOrderID;
	unsigned int sellOrderID;
	unsigned int userID;
	Order::Type orderType;

	Trade();
	Trade(Stock::Symbol symbol, float price, unsigned int quantity, 
		unsigned int buyOrderID, unsigned int sellOrderID, 
		unsigned int userID, Order::Type orderType);
	Trade(const Trade& rhs) = default;
	Trade& operator=(const Trade& rhs) = default;
	virtual ~Trade() = default;

	virtual void Serialize(char* buffer) override;
	virtual void Deserialize(char* buffer) override;
	virtual size_t GetSerializedSize() const override;
	virtual void Print() const override;
};

#endif