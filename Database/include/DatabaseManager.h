#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <string>

namespace MatchingEngine
{
	class Trade;
	class sqlite3;

	class DatabaseManager
	{
	public:
		static void Create();
		static void Destroy();
		static DatabaseManager& GetInstance();

		void InsertTrade(const Trade& trade);

	private:
		static DatabaseManager* instance;
		
		std::string dbPath;
		::sqlite3* database;

		DatabaseManager();
		DatabaseManager(const DatabaseManager& rhs) = delete;
		DatabaseManager& operator=(const DatabaseManager& rhs) = delete;
		~DatabaseManager();

		void SetupTables();
	};
}

#endif
