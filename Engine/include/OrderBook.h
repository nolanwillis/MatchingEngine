#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "Stock.h"
#include "OrderBookWorker.h"

#include <map>
#include <string>

namespace MatchingEngine
{
	class Order;

	class OrderBook
	{
	public:
		friend class OrderBookWorker;
		
		OrderBook() = delete;
		OrderBook(Stock::Symbol symbol, std::shared_future<void> stopSignal);
		OrderBook(const OrderBook& rhs) = delete;
		OrderBook& operator= (const OrderBook& rhs) = delete;
		~OrderBook() = default;

		void Add(const Order& order);
		Stock::Symbol GetStockSymbol() const;
		void WaitUntilIdle();
		void Print() const;

	private:
		Stock::Symbol symbol;
		OrderBookWorker worker;
		
		std::map<float, std::deque<Order>, std::greater<>> buyOrders;
		std::map<float, std::deque<Order>> sellOrders;
	};
}


#endif