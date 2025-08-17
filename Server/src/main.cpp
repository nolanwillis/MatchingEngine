#include "Engine.h"
#include "OrderBookManager.h"

using namespace MatchingEngine;

int main()
{
	OrderBookManager::Create();

	Engine engine;
	printf("Engine server running...\n");
	engine.Run(9002);

	OrderBookManager::Destroy();
	return 0;
}