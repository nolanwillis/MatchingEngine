#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "OrderBookWorker.h"
#include "Stock.h"

#include <gtest/gtest.h>
#include <map>
#include <string>

class EngineTests;
class LimitOrderTests;
class MarketOrderTests;
class Order;

class OrderBook
{
public:
	friend class OrderBookManager;
	friend class OrderBookWorker;

	friend class ::EngineTests;
	FRIEND_TEST(EngineTests, WebsocketMessageWorks);
	friend class ::LimitOrderTests;
	FRIEND_TEST(LimitOrderTests, AddedProperlyWithNoFills);
	FRIEND_TEST(LimitOrderTests, AddedProperlyWithPartialFills);
	FRIEND_TEST(LimitOrderTests, AddedProperlyWithFullFills);
	friend class ::MarketOrderTests;
	FRIEND_TEST(MarketOrderTests, ExecutedWithPartialFill);
	FRIEND_TEST(MarketOrderTests, ExecutedWithFullFill);
	FRIEND_TEST(OrderBookManagerTests, CanProcessOrders);
	
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

#endif