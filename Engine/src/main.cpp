#include "Engine.h"
#include "OrderBookManager.h"

#include <gtest/gtest.h>

int main()
{
	//OrderBookManager::Create();

	//Engine engine;
	//printf("Engine server running...\n");
	//engine.Run(9002);

	//OrderBookManager::Destroy();
	//return 0;
	
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}