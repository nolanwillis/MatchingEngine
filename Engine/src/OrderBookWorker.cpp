#include "Engine.h"
#include "OrderBookWorker.h"
#include "DatabaseManager.h"
#include "OrderBook.h"
#include "Trade.h"

OrderBookWorker::OrderBookWorker(OrderBook& orderBook, std::shared_future<void> stopSignal)
	:
	orderBook(orderBook),
	stopSignal(std::move(stopSignal)),
	messageQueue(),
	messageQueueMtx(),
	messageQueueCV(),
	thread()
{}
OrderBookWorker::~OrderBookWorker()
{
	// Tell the thread to check it's stop signal condition.
	messageQueueCV.notify_one();

	if (thread.joinable())
	{
		thread.join();
	}
}

void OrderBookWorker::Start()
{
	thread = std::thread(std::ref(*this));
}
void OrderBookWorker::AddOrder(std::unique_ptr<Order> order)
{
	std::lock_guard<std::mutex> lock(messageQueueMtx);
	messageQueue.push(std::move(order));
	messageQueueCV.notify_one();
}
void OrderBookWorker::WaitUntilIdle()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(messageQueueMtx);
		if (messageQueue.empty())
		{
			break;
		}
		lock.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void OrderBookWorker::operator()()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(messageQueueMtx);
		
		// Wait while the queue is empty and the stop signal has not been sent. 
		messageQueueCV.wait(lock, [this] 
		{ 
			return !messageQueue.empty() || 
			stopSignal.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready;
		});
		// If the stop signal has been sent, allowing us to reach this point, don't
		// process anything just exit.
		if (stopSignal.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
		{
			break;
		}

		std::unique_ptr<Order> newOrder = std::move(messageQueue.front());
		messageQueue.pop();

		lock.unlock();

		if (newOrder->orderType == Order::Type::Limit)
		{
			AddLimitOrder(std::move(newOrder));
		}
		else if (newOrder->orderType == Order::Type::Market)
		{
			ExecuteMatchOrder(std::move(newOrder));
		}
	}
}

void OrderBookWorker::AddLimitOrder(std::unique_ptr<Order> order)
{
	auto& sellOrders = orderBook.sellOrders;
	auto& buyOrders = orderBook.buyOrders;

	if (order->isBuy)
	{
		// Go through all the price levels until the price level is above our price or 
		// we've filled the buy order.
		auto itr = sellOrders.begin();
		while (itr != sellOrders.end() && order->price >= itr->first && order->quantity > 0
			&& !sellOrders.empty())
		{
			// Get reference to the dequeue of sell orders at this price level. 
			auto& priceLevel = itr->second;

			// Go through all the sell orders at this price level until the order is filled
			// or the price level is emptied.
			for (auto orderItr = priceLevel.begin(); orderItr != priceLevel.end() &&
				order->quantity > 0;)
			{
				Order* sellOrder = priceLevel.front().get();

				if (sellOrder->userID == order->userID)
				{
					orderItr++;
					continue;
				}

				int quantitySold = std::min(order->quantity, sellOrder->quantity);
				
				order->quantity -= quantitySold;
				sellOrder->quantity -= quantitySold;

				GenerateTrades(order.get(), sellOrder, quantitySold);
				
				if (sellOrder->quantity == 0)
				{
					orderItr = priceLevel.erase(orderItr);
				}
				else
				{
					orderItr++;
				}
			}

			if (priceLevel.empty())
			{
				itr = sellOrders.erase(itr);
			}
			else
			{
				itr++;
			}
		}
		
		// If there's unfilled quantity push the buy order onto the order book. 
		if (order->quantity != 0)
		{
			buyOrders[order->price].push_back(std::move(order));
		}
	}
	else
	{
		// Go through all the price levels until the price level is below our price or 
		// we've filled the sell order.
		auto itr = buyOrders.begin();
		while (itr != buyOrders.end() && order->price <= itr->first && order->quantity > 0 &&
			!buyOrders.empty())
		{
			// Get reference to the dequeue of buy orders at this price level. 
			auto& priceLevel = itr->second;

			// Go through all the buy orders at this price level until the order is filled
			// or the price level is emptied.
			for (auto orderItr = priceLevel.begin(); orderItr != priceLevel.end() &&
				order->quantity > 0;)
			{
				Order* buyOrder = priceLevel.front().get();

				if (buyOrder->userID == order->userID)
				{
					orderItr++;
					continue;
				}

				int quantitySold = std::min(order->quantity, buyOrder->quantity);
				
				order->quantity -= quantitySold;
				buyOrder->quantity -= quantitySold;
				
				GenerateTrades(buyOrder, order.get(), quantitySold);

				if (buyOrder->quantity == 0)
				{
					orderItr = priceLevel.erase(orderItr);
				}
				else
				{
					orderItr++;
				}
			}

			if (priceLevel.empty())
			{
				itr = buyOrders.erase(itr);
			}
			else
			{
				itr++;
			}
		}

		// If there's unfilled quantity push the sell order onto the order book. 
		if (order->quantity != 0)
		{
			sellOrders[order->price].push_back(std::move(order));
		}
	}
}
void OrderBookWorker::ExecuteMatchOrder(std::unique_ptr<Order> order)
{
	auto& sellOrders = orderBook.sellOrders;
	auto& buyOrders = orderBook.buyOrders;

	if (order->isBuy)
	{
		while (order->quantity > 0 && !sellOrders.empty())
		{
			auto itr = sellOrders.begin();
			auto& priceLevel = itr->second;

			for (auto orderItr = priceLevel.begin(); 
				orderItr != priceLevel.end() && order->quantity > 0;)
			{
				Order* sellOrder = priceLevel.front().get();

				if (sellOrder->userID == order->userID)
				{
					orderItr++;
					continue;
				}

				int quantitySold = std::min(order->quantity, sellOrder->quantity);

				order->quantity -= quantitySold;
				sellOrder->quantity -= quantitySold;
				
				GenerateTrades(order.get(), sellOrder, quantitySold);

				if (sellOrder->quantity == 0)
				{
					orderItr = priceLevel.erase(orderItr);
				}
				else
				{
					orderItr++;
				}
			}

			if (priceLevel.empty())
			{
				sellOrders.erase(itr);
			}
		}
	}
	else
	{
		while (order->quantity > 0 && !buyOrders.empty())
		{
			auto itr = buyOrders.begin();
			auto& priceLevel = itr->second;

			for (auto orderItr = priceLevel.begin();
				orderItr != priceLevel.end() && order->quantity > 0;)
			{
				Order* buyOrder = priceLevel.front().get();

				if (buyOrder->userID == order->userID)
				{
					orderItr++;
					continue;
				}

				int quantitySold = std::min(order->quantity, buyOrder->quantity);

				order->quantity -= quantitySold;
				buyOrder->quantity -= quantitySold;
				
				GenerateTrades(buyOrder, order.get(), quantitySold);

				if (buyOrder->quantity == 0)
				{
					orderItr = priceLevel.erase(orderItr);
				}
				else
				{
					orderItr++;
				}
			}

			if (priceLevel.empty())
			{
				buyOrders.erase(itr);
			}
		}
	}
}

void OrderBookWorker::GenerateTrades(Order* buyOrder, Order* sellOrder, unsigned int quantity)
{
	std::unique_ptr<Trade> buyerTrade = std::make_unique<Trade>(buyOrder->symbol,
		buyOrder->price, quantity, buyOrder->orderID, sellOrder->orderID,
		buyOrder->userID, buyOrder->orderType);

	std::unique_ptr<Trade> sellerTrade = std::make_unique<Trade>(sellOrder->symbol,
		sellOrder->price, quantity, buyOrder->orderID, sellOrder->orderID,
		sellOrder->userID, sellOrder->orderType);

	// Log trades to the database for the incoming order and the sell order.
	DatabaseManager::AddMessage(std::move(buyerTrade));
	DatabaseManager::AddMessage(std::move(sellerTrade));

	// Tell the client to add a trade to it's list.
	Engine::BroadcastTrade(buyOrder->symbol,
		buyOrder->price, quantity, buyOrder->orderID, sellOrder->orderID,
		buyOrder->userID, buyOrder->orderType);
	Engine::BroadcastTrade(sellOrder->symbol,
		sellOrder->price, quantity, buyOrder->orderID, sellOrder->orderID,
		sellOrder->userID, sellOrder->orderType);
}
