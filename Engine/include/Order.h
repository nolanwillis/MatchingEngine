#ifndef ORDER_H
#define ORDER_H

#include "Message.h"
#include "Stock.h"

namespace MatchingEngine
{
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
		unsigned int userID;
		unsigned int quantity;
		unsigned int isBuy;
		float price;
		Order::Type orderType;

		Order();
		Order(Stock::Symbol symbol, unsigned int userID, unsigned int quantity,
			unsigned int isBuy, float limit, Order::Type orderType);
		Order(const Order& rhs);
		Order& operator=(const Order& rhs);
		virtual ~Order() = default;

		virtual void Serialize(char* buffer) override;
		virtual void Deserialize(char* buffer) override;
		virtual size_t GetSerializedSize() const override;
		virtual void Print() const override;
	};
}

#endif
