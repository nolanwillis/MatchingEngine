#include "DatabaseManager.h"
#include "Trade.h"

#include <assert.h>
#include <stdexcept>

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager()
	:
	dbPath("database.db"),
	database(nullptr),
	tradeQueue(),
	tradeQueueMtx(),
	tradeWriterThread(&DatabaseManager::WriteTradeToDatabase, this)
{
	shouldStopWriting.store(false);

	// Open the database.
	try
	{
		int result = sqlite3_open(DatabaseManager::dbPath.c_str(), &database);
		if (result != SQLITE_OK)
		{
			throw std::runtime_error("Database not opened properly.");
		}
	}
	catch (std::exception& e)
	{
		printf("Error: %s", e.what());
	}

	SetupTables();
}
DatabaseManager::~DatabaseManager()
{
	shouldStopWriting.store(true);
	tradeQueueCV.notify_one();

	sqlite3_close(database);

	if (tradeWriterThread.joinable())
	{
		tradeWriterThread.join();
	}
}

void DatabaseManager::Create()
{
	if (!instance)
	{
		instance = new DatabaseManager();
	}
}
void DatabaseManager::Destroy()
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
DatabaseManager& DatabaseManager::GetInstance()
{
	if (instance)
	{
		return *instance;
	}
	assert(false);
}

void DatabaseManager::AddTrade(const Trade& trade)
{
	DatabaseManager& instance = GetInstance();

	{
		std::lock_guard<std::mutex> lock(instance.tradeQueueMtx);
		instance.tradeQueue.emplace(
			std::make_unique<Trade>(trade.symbol, trade.price, trade.quantity, trade.buyOrderID, 
				trade.sellOrderID, trade.userID, trade.orderType)
		);
	}

	instance.tradeQueueCV.notify_one();
}
Trade DatabaseManager::GetTrade(const unsigned int userID)
{
	try
	{
		DatabaseManager& instance = GetInstance();

		// Create the SQL statement.
		const char* sql = "SELECT * FROM Trades WHERE UserID = ?;";
		sqlite3_stmt* stmt = nullptr;
		int result = sqlite3_prepare_v2(instance.database, sql, -1, &stmt, nullptr);
		if (result != SQLITE_OK)
		{
			std::string fullErrorMessage = "Failed to prepare statement ";
			fullErrorMessage.append(sqlite3_errmsg(instance.database)).append("\n");
			
			throw std::runtime_error(fullErrorMessage);
		}

		// Bind the tradeID to the statement (the WHERE clause).
		result = sqlite3_bind_int(stmt, 1, userID);
		if (result != SQLITE_OK)
		{
			sqlite3_finalize(stmt);
			
			std::string fullErrorMessage = "Failed to bind parameter tradeID ";
			fullErrorMessage.append(sqlite3_errmsg(instance.database)).append("\n");

			throw std::runtime_error(fullErrorMessage);
		}

		int rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW)
		{
			Trade trade
			(
				(Stock::Symbol)sqlite3_column_int(stmt, 1),
				(float)sqlite3_column_double(stmt, 2),
				sqlite3_column_int(stmt, 3),
				sqlite3_column_int(stmt, 4),
				sqlite3_column_int(stmt, 5),
				sqlite3_column_int(stmt, 6),
				(Order::Type)sqlite3_column_int(stmt, 7)
			);

			sqlite3_finalize(stmt);

			return trade;
		}
		else if (rc == SQLITE_DONE)
		{
			printf("No trade found with ID: %d.\n", userID);
		}
		else
		{

			std::string fullErrorMessage = "Error while finding trade ";
			fullErrorMessage.append(sqlite3_errmsg(instance.database)).append("\n");

			throw std::runtime_error(fullErrorMessage);
		}

	}
	catch (std::exception& e)
	{
		printf("Error: %s", e.what());
	}

	return Trade();
}
void DatabaseManager::WaitUntilWriterIsIdle()
{
	DatabaseManager& instance = GetInstance();
	
	while (true)
	{
		std::unique_lock<std::mutex> lock(instance.tradeQueueMtx);
		if (instance.tradeQueue.empty())
		{
			break;
		}
		lock.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void DatabaseManager::SetupTables()
{
	 try
	{
		int result = sqlite3_open(dbPath.c_str(), &database);
		if (result != SQLITE_OK)
		{
			throw std::runtime_error("Could not open the database.");
		}

		// Trades
		const char* createTableSQL = R"(
			DROP TABLE IF EXISTS Trades;

			CREATE TABLE Trades (
				TradeID     INTEGER PRIMARY KEY AUTOINCREMENT,
				Symbol      INTEGER NOT NULL,
				Price       DOUBLE NOT NULL,
				Quantity    INTEGER NOT NULL,
				BuyOrderID  INTEGER NOT NULL,
				SellOrderID INTEGER NOT NULL,
				UserID      INTEGER NOT NULL,
				OrderType   INTEGER NOT NULL, 
				Timestamp   DATETIME DEFAULT CURRENT_TIMESTAMP
			);
		)";

		// Try to create the tables.
		char* errorMessage = nullptr;
		result = sqlite3_exec(database, createTableSQL, nullptr, nullptr, &errorMessage);
		if (result != SQLITE_OK)
		{
			std::string fullErrorMessage = "Could not create the table ";
			fullErrorMessage.append(sqlite3_errmsg(database)).append("\n");
			
			sqlite3_free(errorMessage);

			throw std::runtime_error(fullErrorMessage);
		}
	}
	catch(std::exception& e)
	{
		printf("Error: %s", e.what());
	}
}
void DatabaseManager::WriteTradeToDatabase()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(tradeQueueMtx);

		// Wait while the queue is empty and the stop signal has not been sent. 
		tradeQueueCV.wait(lock, [this]{ return !tradeQueue.empty() || shouldStopWriting.load(); });
		// If the signal to stop has been sent, allowing us to reach this point, don't
		// process anything just exit.
		if (shouldStopWriting.load())
		{
			break;
		}
		
		try
		{
			std::unique_ptr<Trade> trade = std::move(tradeQueue.front());
			tradeQueue.pop();
			lock.unlock();
			
			const char* sql = "INSERT INTO Trades (Symbol, Price, Quantity, BuyOrderID, "
				"SellOrderID, UserID, OrderType) VALUES(? , ? , ? , ? , ? , ? , ?);";
			sqlite3_stmt* stmt;

			int result = sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr);
			if (result != SQLITE_OK)
			{
				std::string fullErrorMessage = "Failed to prepare the statement ";
				fullErrorMessage.append(sqlite3_errmsg(database)).append("\n");

				throw std::runtime_error(fullErrorMessage);
			}
			sqlite3_bind_int(stmt, 1, (int)trade->symbol);
			sqlite3_bind_double(stmt, 2, (double)trade->price);
			sqlite3_bind_int(stmt, 3, (int)trade->quantity);
			sqlite3_bind_int(stmt, 4, (int)trade->buyOrderID);
			sqlite3_bind_int(stmt, 5, (int)trade->sellOrderID);
			sqlite3_bind_int(stmt, 6, (int)trade->userID);
			sqlite3_bind_int(stmt, 7, (int)trade->orderType);

			if (sqlite3_step(stmt) != SQLITE_DONE)
			{
				std::string fullErrorMessage = "Failed to insert trade ";
				fullErrorMessage.append(sqlite3_errmsg(database)).append("\n");

				throw std::runtime_error(fullErrorMessage);
			}

			sqlite3_finalize(stmt);
		
		}
		catch (std::exception& e)
		{
			printf("Error: %s", e.what());
		}
	}
}