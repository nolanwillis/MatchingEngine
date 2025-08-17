#ifndef ENGINE_WORKER_H
#define ENGINE_WORKER_H

#include <thread>
#include <future>

namespace MatchingEngine
{
	class Engine;
	class condition_variable;

	class EngineWorker
	{
	public:
		EngineWorker() = delete;
		EngineWorker(Engine& engine, std::shared_future<void> stopSignal,
			std::condition_variable& routingQueueCV);
		EngineWorker(const EngineWorker& rhs) = delete;
		EngineWorker& operator= (const EngineWorker& rhs) = delete;
		~EngineWorker();

		void Start();
		void operator()();

	private:
		Engine& engine;
		std::shared_future<void> stopSignal;
		std::condition_variable& routingQueueCV;
		std::thread thread;
	};
}

#endif
