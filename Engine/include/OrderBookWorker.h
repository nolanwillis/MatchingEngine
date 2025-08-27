#ifndef ORDER_BOOK_WORKER_H
#define ORDER_BOOK_WORKER_H

#include "Order.h"

#include <queue>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>

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
	void AddOrder(std::unique_ptr<Order> order);
	void WaitUntilIdle();

	void operator()();

private:
	OrderBook& orderBook;

	std::shared_future<void> stopSignal;
	
	std::queue<std::unique_ptr<Order>> messageQueue;
	std::mutex messageQueueMtx;
	std::condition_variable messageQueueCV;
	std::thread thread;

	void AddLimitOrder(std::unique_ptr<Order> order);
	void ExecuteMatchOrder(std::unique_ptr<Order> order);
	void GenerateTrades(Order* buyOrder, Order* sellOrder, unsigned int quantity);
};

#endif