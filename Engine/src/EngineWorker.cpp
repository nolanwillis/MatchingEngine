#include "EngineWorker.h"
#include "Engine.h"
#include "Login.h"
#include "OrderBookManager.h"

#include <condition_variable>

EngineWorker::EngineWorker(Engine& engine, std::shared_future<void> stopSignal,
	std::condition_variable& routingQueueCV)
	:
	engine(engine),
	stopSignal(std::move(stopSignal)),
	routingQueueCV(routingQueueCV)
{}
EngineWorker::~EngineWorker()
{
	if (thread.joinable())
	{
		thread.join();
	}
}

void EngineWorker::Start()
{
	thread = std::thread(std::ref(*this));
}
void EngineWorker::operator()()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(engine.routingQueueMtx);

		// Wait while the queue is empty and the stop signal has not been sent. 
		routingQueueCV.wait(lock, [this]{ return !engine.routingQueue.empty() ||
				stopSignal.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
		});
		// If the stop signal has been sent, allowing us to reach this point, don't
		// process anything just exit.
		if (stopSignal.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
		{
			break;
		}
		
		// Pop a message off the queue. 
		std::unique_ptr<Message> currentMessage = std::move(engine.routingQueue.front());
		engine.routingQueue.pop();
		lock.unlock();

		Message::Type currentMessageType = currentMessage->GetMessageType();

		if (currentMessageType == Message::Type::Order)
		{
			OrderBookManager::AddMessage(std::move(currentMessage));
		}
		else if (currentMessageType == Message::Type::Login)
		{
			std::unique_ptr<Login> loginMessage((Login*)currentMessage.release());
			engine.VerifyLogin(std::move(loginMessage));
		}
	}
}