#include "DatabaseManager.h"
#include "Engine.h"
#include "OrderBookManager.h"

#include <gtest/gtest.h>

//#define TEST_MODE

int main()
{
#ifdef TEST_MODE
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
#endif

#ifndef TEST_MODE
	Engine::Create();
	DatabaseManager::Create();
	OrderBookManager::Create();

	printf("Engine server running...\n");
	Engine::Run(9002);

	OrderBookManager::Destroy();
	DatabaseManager::Destroy();
	Engine::Destroy();

	return 0;
#endif
	
}