#include "gtest/gtest.h"

// Make the private fields of OrderBook public.
#define private public
#include "OrderBook.h"
#undef private

#include "OrderBookManager.h"

using namespace MatchingEngine;

class OrderBookManagerTests : public ::testing::Test
{
protected:
	void SetUp() override
	{
		OrderBookManager::Create();
	}

	void TearDown() override
	{
		OrderBookManager::Destroy();
	}
};

TEST_F(OrderBookManagerTests, All)
{
	auto& instance = OrderBookManager::GetInstance();
	EXPECT_TRUE(instance.RunCreatesAllOrderBooksTest());
	EXPECT_TRUE(instance.RunCanProcessOrdersTest());
}