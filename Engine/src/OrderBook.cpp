#include "OrderBook.h"
#include "OrderBookWorker.h"

#include <iostream>
#include <windows.h>

OrderBook::OrderBook(Stock::Symbol symbol, std::shared_future<void> stopSignal)
	:
	symbol(symbol),
	worker(*this, stopSignal)
{
	worker.Start();
}

void OrderBook::Add(std::unique_ptr<Order> order)
{
	worker.AddOrder(std::move(order));
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

	// Print in green.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("\nBuy Orders\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	
	for (auto itr = buyOrders.begin(); itr != buyOrders.end(); itr++)
	{
		for (const auto& order : itr->second)
		{
			order->Print();
		}

	}
	
	// Print in red.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("\nSell Orders\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	
	for (auto itr = sellOrders.begin(); itr != sellOrders.end(); itr++)
	{
		for (const auto& order : itr->second)
		{
			order->Print();
		}
	}
	printf("\n========================================================\n");
	printf("========================================================\n");
	printf("========================================================\n");
}
