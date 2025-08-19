#include "OrderBookManager.h"
#include "Order.h"

#include <assert.h>

OrderBookManager* OrderBookManager::instance = nullptr;

OrderBookManager::OrderBookManager()
{
	CreateOrderBooks();
}
OrderBookManager::~OrderBookManager()
{
	stopSignal.set_value();
}

void OrderBookManager::Create()
{
	if (!instance) 
	{
		instance = new OrderBookManager();
	}
}
void OrderBookManager::Destroy() 
{
	if (instance) 
	{ 
		delete instance;
		instance = nullptr;
	}
	else
	{
		assert(false);
	}
}

void OrderBookManager::AddMessage(std::unique_ptr<Message> message)
{
	OrderBookManager& instance = OrderBookManager::GetInstance();

	switch (message->GetMessageType())
	{
	case Message::Type::Order: 
	{
		std::unique_ptr<Order> orderPtr((Order*)message.release());
		instance.HandleOrder(std::move(orderPtr));
		break;
	}
	default:
		break;
	}
}

OrderBookManager& OrderBookManager::GetInstance()
{
	if (instance)
	{
		return *instance;
	}
	assert(false);
}

void OrderBookManager::HandleOrder(std::unique_ptr<Order> order)
{
	auto& orderBook = orderBooks.at(order->symbol);
	orderBook.Add(std::move(order));
}
void OrderBookManager::CreateOrderBooks()
{
	std::shared_future<void> future = stopSignal.get_future().share();

	for (int i = 1; i < (int)Stock::Symbol::COUNT; i++)
	{
		Stock::Symbol currentSymbol = (Stock::Symbol)i;
		orderBooks.try_emplace(currentSymbol, currentSymbol, future);
	}	
}