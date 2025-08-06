#include "OrderBook.h"
#include "OrderBookWorker.h"

namespace MatchingEngine
{
	OrderBook::OrderBook(Stock::Symbol symbol, std::shared_future<void> stopSignal)
		:
		symbol(symbol),
		worker(*this, std::move(stopSignal))
	{
		worker.Start();
	}

	void OrderBook::Add(const Order& order)
	{
		worker.AddOrder(order);
	}
	Stock::Symbol OrderBook::GetStockSymbol() const
	{
		return this->symbol;
	}
	void OrderBook::WaitUntilIdle() 
	{
		worker.WaitUntilIdle();
	}
	void OrderBook::Print() const
	{
		printf("\n========================================================\n");
		printf("==================== ORDER BOOK %s ====================\n", 
			Stock::ToString(this->symbol));
		printf("========================================================\n");

		printf("\nBuy Orders:\n");
		for (auto itr = buyOrders.begin(); itr != buyOrders.end(); itr++)
		{
			for (auto& order : itr->second)
			{
				order.Print();
			}

		}
		printf("\nSell Orders:\n");
		for (auto itr = sellOrders.begin(); itr != sellOrders.end(); itr++)
		{
			for (auto& order : itr->second)
			{
				order.Print();
			}
		}
		printf("\n========================================================\n");
		printf("========================================================\n");
		printf("========================================================\n");
	}
}
