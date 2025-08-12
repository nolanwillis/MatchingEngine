#include "OrderBookManager.h"
#include "Order.h"

#include <assert.h>

namespace MatchingEngine
{
	void OrderBookManager::Create()
	{
		OrderBookManager& instance = GetInstance();
		instance.CreateOrderBooks();
		instance.isRunning = true;
	}
	void OrderBookManager::Destroy() 
	{
		OrderBookManager& instance = GetInstance();
		
		// Ensure the process function exits.
		instance.isRunning = false;

		// Signal all the order books to stop processing.
		instance.stopSignal.set_value();
	}

	void OrderBookManager::AddMessage(std::unique_ptr<Message> msg)
	{
		OrderBookManager& instance = OrderBookManager::GetInstance();
		std::lock_guard<std::mutex> lock(instance.messageQueueMtx);
		
		instance.messageQueue.push_back(std::move(msg));
	}
	void OrderBookManager::Process()
	{
		OrderBookManager& instance = OrderBookManager::GetInstance();
		
		std::unique_lock<std::mutex> lock(instance.messageQueueMtx);

		if (instance.messageQueue.empty())
		{
			return;
		}

		std::unique_ptr<Message> message = std::move(instance.messageQueue.front());
		
		switch (message->GetMessageType())
		{
		case Message::Type::PlaceOrder: 
		{
			std::unique_ptr<Order> orderPtr((Order*)message.release());
			instance.HandlePlaceOrder(std::move(orderPtr));
			break;
		}
		default:
			break;
		}
		
		instance.messageQueue.pop_front();

	}

	void OrderBookManager::HandlePlaceOrder(std::unique_ptr<Order> order)
	{
		auto& orderBook = orderBooks.at(order->symbol);
		orderBook.Add(std::move(order));
	}
	void OrderBookManager::CreateOrderBooks()
	{
		OrderBookManager& instance = OrderBookManager::GetInstance();

		std::shared_future<void> future = instance.stopSignal.get_future().share();

		for (int i = 1; i < (int)Stock::Symbol::COUNT; i++)
		{
			Stock::Symbol currentSymbol = (Stock::Symbol)i;
			instance.orderBooks.try_emplace(currentSymbol, currentSymbol, future);
		}	
	}
	
	bool OrderBookManager::RunCreatesAllOrderBooksTest()
	{
		OrderBookManager& instance = OrderBookManager::GetInstance();

		if (instance.orderBooks.size() != (int)Stock::Symbol::COUNT - 1)
		{
			return false;
		}

		for (int i = 1; i < (int)Stock::Symbol::COUNT; i++)
		{
			Stock::Symbol currentSymbol = (Stock::Symbol)i;
			if (!instance.orderBooks.contains(currentSymbol))
			{
				return false;
			}
		}

		return true;
	}
	bool OrderBookManager::RunCanProcessOrdersTest()
	{
		auto& instance = OrderBookManager::GetInstance();

		std::unique_ptr<Order> buyOrder1 = 
			std::make_unique<Order>(Stock::Symbol::AAA, 100, 50, 0, 1, Order::Type::Limit);
		std::unique_ptr<Order> buyOrder2 = 
			std::make_unique<Order>(Stock::Symbol::BBB, 100, 50, 1, 1, Order::Type::Limit);
		std::unique_ptr<Order> buyOrder3 =
			std::make_unique<Order>(Stock::Symbol::CCC, 100, 50, 2, 1, Order::Type::Limit);
		std::unique_ptr<Order> buyOrder4 = 
			std::make_unique<Order>(Stock::Symbol::DDD, 100, 50, 3, 1, Order::Type::Limit);
		std::unique_ptr<Order> buyOrder5 = 
			std::make_unique<Order>(Stock::Symbol::EEE, 100, 50, 4, 1, Order::Type::Limit);

		std::unique_ptr<Order> sellOrder1 = 
			std::make_unique<Order>(Stock::Symbol::AAA, 200, 50, 5, 0, Order::Type::Limit);
		std::unique_ptr<Order> sellOrder2 = 
			std::make_unique<Order>(Stock::Symbol::BBB, 200, 50, 6, 0, Order::Type::Limit);
		std::unique_ptr<Order> sellOrder3 = 
			std::make_unique<Order>(Stock::Symbol::CCC, 200, 50, 7, 0, Order::Type::Limit);
		std::unique_ptr<Order> sellOrder4 = 
			std::make_unique<Order>(Stock::Symbol::DDD, 200, 50, 8, 0, Order::Type::Limit);
		std::unique_ptr<Order> sellOrder5 = 
			std::make_unique<Order>(Stock::Symbol::EEE, 200, 50, 9, 0, Order::Type::Limit);
		
		instance.AddMessage(std::move(buyOrder1));
		instance.Process();

		instance.AddMessage(std::move(buyOrder2));
		instance.Process();
		
		instance.AddMessage(std::move(buyOrder3));
		instance.Process();

		instance.AddMessage(std::move(buyOrder4));
		instance.Process();

		instance.AddMessage(std::move(buyOrder5));
		instance.Process();

		instance.AddMessage(std::move(sellOrder1));
		instance.Process();

		instance.AddMessage(std::move(sellOrder2));
		instance.Process();

		instance.AddMessage(std::move(sellOrder3));
		instance.Process();

		instance.AddMessage(std::move(sellOrder4));
		instance.Process();

		instance.AddMessage(std::move(sellOrder5));
		instance.Process();

		// Wait for transactions to be processed. 
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		for (auto& [symbol, orderBook] : instance.orderBooks)
		{
			Order* buyOrder = orderBook.buyOrders.at(100).front().get();
			Order* sellOrder = orderBook.sellOrders.at(200).front().get();

			if (buyOrder->symbol != symbol || buyOrder->price != 100)
			{
				return false;
			}
			if (sellOrder->symbol != symbol || sellOrder->price != 200)
			{
				return false;
			}
		}

		return true;
	}
	
	OrderBookManager& OrderBookManager::GetInstance()
	{
		static OrderBookManager instance;
		return instance;
	}
}