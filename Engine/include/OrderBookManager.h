#ifndef ORDER_BOOK_MANAGER_H
#define ORDER_BOOK_MANAGER_H

#include "OrderBook.h"
#include "Stock.h"
#include "Message.h"

#include <condition_variable>
#include <future>
#include <queue>
#include <map>

namespace MatchingEngine
{
	class Order;

	class OrderBookManager
	{
	public:
		static void Create();
		static void Destroy();
		static OrderBookManager& GetInstance();

		void AddMessage(std::unique_ptr<Message> msg);
		
	private:
		static OrderBookManager* instance;

		std::promise<void> stopSignal;
		std::unordered_map<Stock::Symbol, OrderBook> orderBooks;

		OrderBookManager();
		OrderBookManager(const OrderBookManager& rhs) = delete;
		OrderBookManager& operator=(const OrderBookManager& rhs) = delete;
		~OrderBookManager();
		
		void HandleOrder(std::unique_ptr<Order> order);
		void CreateOrderBooks();
	};
}

#endif