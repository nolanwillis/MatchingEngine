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
		friend class OrderBookManager;
		
		OrderBook() = delete;
		OrderBook(Stock::Symbol symbol, std::shared_future<void> stopSignal);
		OrderBook(const OrderBook& rhs) = delete;
		OrderBook& operator= (const OrderBook& rhs) = delete;
		~OrderBook() = default;

		void Add(std::unique_ptr<Order> order);
		Stock::Symbol GetStockSymbol() const;
		void WaitUntilIdle();
		void Print() const;

	private:
		Stock::Symbol symbol;
		OrderBookWorker worker;
		
		std::map<float, std::deque<std::unique_ptr<Order>>, std::greater<>> buyOrders;
		std::map<float, std::deque<std::unique_ptr<Order>>> sellOrders;
	};
}


#endif