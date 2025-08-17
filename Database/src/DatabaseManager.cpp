#include "DatabaseManager.h"

#include <assert.h>
#include <sqlite3.h>
#include <stdexcept>

namespace MatchingEngine
{
	DatabaseManager* DatabaseManager::instance = nullptr;
	
	DatabaseManager::DatabaseManager()
		:
		dbPath("database.db"),
		database(nullptr)
	{
		try
		{
			int result = sqlite3_open(DatabaseManager::dbPath.c_str(), &database);
			if (result != SQLITE_OK)
			{
				throw std::invalid_argument("Database not opened properly.");
			}
		}
		catch (std::exception& e)
		{
			printf("Error: %s", e.what());
		}
	}
	DatabaseManager::~DatabaseManager()
	{
		sqlite3_close(database);
	}

	void DatabaseManager::SetupTables()
	{
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
}