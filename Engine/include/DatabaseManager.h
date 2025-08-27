#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "Order.h"
#include "Message.h"
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
class Login;
class User;
class Trade;

class DatabaseManager
{
public:
	FRIEND_TEST(DatabaseTests, CanAddAndGetTrade);

	static void Create();
	static void Destroy();

	static void AddMessage(std::unique_ptr<Message> message);
	static void AddUser(std::string username);
	static User GetUser(std::string username);
	static Trade GetTrade(const unsigned int userID);
	//static User GetUser(const std::string& username);
	static void WaitUntilWriterIsIdle();

private:
	static DatabaseManager* instance;
	
	std::string dbPath;
	::sqlite3* database;

	std::atomic<bool> shouldStopWriting;
	std::queue<std::unique_ptr<Message>> messageQueue;
	std::mutex messageQueueMtx;
	std::condition_variable messageQueueCV;
	std::thread thread;
	
	static DatabaseManager& GetInstance();

	DatabaseManager();
	DatabaseManager(const DatabaseManager& rhs) = delete;
	DatabaseManager& operator=(const DatabaseManager& rhs) = delete;
	~DatabaseManager();

	void SetupTables();
	void ProcessMessages();

	// Processing helpers.
	void AddTrade(std::unique_ptr<Trade> trade);
};

#endif
