#ifndef ORDER_BOOK_WORKER_H
#define ORDER_BOOK_WORKER_H

#include "Order.h"

#include <queue>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>

namespace MatchingEngine
{
	class OrderBook;

	class OrderBookWorker
	{
	public:
		OrderBookWorker() = delete;
		OrderBookWorker(OrderBook& orderBook, std::shared_future<void> stopSignal);
		OrderBookWorker(const OrderBookWorker& rhs) = delete;
		OrderBookWorker& operator= (const OrderBookWorker& rhs) = delete;
		~OrderBookWorker();

		void Start();
		void AddOrder(const Order& order);
		void WaitUntilIdle();

		void operator()();

	private:
		OrderBook& orderBook;

		std::shared_future<void> stopSignal;
		
		std::queue<Order> orderQueue;
		std::mutex orderQueueMtx;

		std::condition_variable cv;
		std::thread thread;

		void AddLimitOrder(Order& order);
		void ExecuteMatchOrder(Order& order);
	};
}

#endif