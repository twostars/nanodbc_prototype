#include <iostream>
#include <string>

#include "DatabaseConnManager.h"
#include "Item.h"
#include "ItemBinder.h"
#include "ModelRecordSet.h"
#include "SqlBuilder.h"
#include "nanodbc/nanodbc.h"

int main()
{
	try
	{
		std::string dsn = "KN_online";
		std::string user = "knight";
		std::string password = "knight";
		DatabaseConnManager::SetGameDsn(dsn, user, password);

		SqlBuilder<Item> filter {};
		filter.SetSelectColumns({ "Num", "strName" });

		// using an iterator
		ModelRecordSet<Item> recordSet(filter);
		int i = 0;
		while (recordSet.next() && i < 10)
		{
			Item item = recordSet.get();
			std::cout << item.Num << ": " << item.Name << "\n";
			i++;
		}

		// loading results in a single query; currently this functions the same way as the iterator above
		// need to look more at nanodbc library functions to see if there's a way to fetch everything
		// in one database trip or not
		std::vector<Item> results = Model::BatchSelect<Item>(filter);
		for (std::size_t ix = 0; ix < results.size() && ix < 10; ix++)
		{
			std::cout << results.at(ix).Num << ": " << results.at(ix).Name << "\n";
		}
	}
	catch (nanodbc::database_error& ex)
	{
		std::cerr << ex.what() << "\n";
	}
}
