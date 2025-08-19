#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "Order.h"
#include "sqlite3.h"
#include "Stock.h"

#include <condition_variable>
#include <future>
#include <gtest/gtest.h>
#include <queue>
#include <mutex>
#include <string>
#include <thread>

class DatabaseTests;
class Trade;

class DatabaseManager
{
public:
	FRIEND_TEST(DatabaseTests, CanAddAndGetTrade);

	static void Create();
	static void Destroy();

	static void AddTrade(Stock::Symbol symbol, float price, unsigned int quantity,
		unsigned int buyOrderID, unsigned int sellOrderID, unsigned int userID, 
		Order::Type orderType);
	static Trade GetTrade(const unsigned int userID);
	static void WaitUntilWriterIsIdle();

private:
	static DatabaseManager* instance;
	
	std::string dbPath;
	::sqlite3* database;

	std::atomic<bool> shouldStopWriting;
	std::queue<std::unique_ptr<Trade>> tradeQueue;
	std::mutex tradeQueueMtx;
	std::condition_variable tradeQueueCV;
	std::thread tradeWriterThread;
	
	static DatabaseManager& GetInstance();

	DatabaseManager();
	DatabaseManager(const DatabaseManager& rhs) = delete;
	DatabaseManager& operator=(const DatabaseManager& rhs) = delete;
	~DatabaseManager();

	void SetupTables();
	void WriteTradeToDatabase();
};

#endif
