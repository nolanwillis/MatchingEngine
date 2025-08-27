#include "DatabaseManager.h"
#include "Engine.h"
#include "OrderBookManager.h"
#include "Controls.h"

#include <gtest/gtest.h>

int main()
{
#ifdef TEST_MODE_ACTIVE
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
#endif

#ifndef TEST_MODE_ACTIVE
	Engine::Create();
	DatabaseManager::Create();
	OrderBookManager::Create();

	DatabaseManager::AddUser("Nolan");
	DatabaseManager::AddUser("Liam");

	printf("Engine server running...\n");
	Engine::Run(9002);

	OrderBookManager::Destroy();
	DatabaseManager::Destroy();
	Engine::Destroy();

	return 0;
#endif
	
}