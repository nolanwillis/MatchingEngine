#ifndef ORDER_BOOK_MANAGER_H
#define ORDER_BOOK_MANAGER_H

#include "OrderBook.h"
#include "Stock.h"
#include "Message.h"

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

		static void AddMessage(std::unique_ptr<Message> msg);
		static void Process();
		static OrderBookManager& GetInstance();
		
		static bool RunCreatesAllOrderBooksTest();
		static bool RunCanProcessOrdersTest();
		
	private:
		std::promise<void> stopSignal;
		std::unordered_map<Stock::Symbol, OrderBook> orderBooks;
		std::deque<std::unique_ptr<Message>> messageQueue;
		std::mutex messageQueueMtx;
		bool isRunning;

		OrderBookManager() = default;
		OrderBookManager(const OrderBookManager& rhs) = delete;
		OrderBookManager& operator=(const OrderBookManager& rhs) = delete;
		~OrderBookManager() = default;
		
		void HandlePlaceOrder(std::unique_ptr<Order> order);
		void CreateOrderBooks();
	};
}

#endif