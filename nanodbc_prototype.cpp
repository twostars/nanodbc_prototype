#include <iostream>
#include <string>

#include "DatabaseConnManager.h"
#include "ModelRecordSet.h"
#include "SqlBuilder.h"
#include "nanodbc/nanodbc.h"

import FullModel;
import FullBinder;

namespace model = full_model;
using namespace db;

int main()
{
	struct DbHelper
	{
		DbHelper() { DatabaseConnManager::Create(); }
		~DbHelper() { DatabaseConnManager::Destroy(); }
	};
	DbHelper helper;

	try
	{
		DatabaseConnManager::SetDatasourceConfig(
			modelUtil::DbType::GAME,
			"KN_online",
			"knight",
			"knight");
		
		SqlBuilder<model::Item> filter {};
		filter.SetSelectColumns({ "Num", "strName" });
		filter.Limit = 10;

		// using an iterator
		ModelRecordSet<model::Item> recordSet;
		recordSet.open(filter);

		while (recordSet.next())
		{
			model::Item item = recordSet.get();
			std::cout << item.ID << ": " << item.Name << "\n";
		}

		// loading results in a single query; currently this functions the same way as the iterator above
		// need to look more at nanodbc library functions to see if there's a way to fetch everything
		// in one database trip or not
		std::vector<model::Item> results = Model::BatchSelect<model::Item>(filter);
		for (std::size_t ix = 0; ix < results.size(); ix++)
		{
			std::cout << results.at(ix).ID << ": " << results.at(ix).Name << "\n";
		}
		
		SqlBuilder<model::Item> filter2 {};
		filter2.SetSelectColumns({ "Num", "strName" });
		filter2.Limit = 10;

		// using an iterator
		ModelRecordSet<model::Item> recordSet2;
		recordSet2.open(filter2);

		while (recordSet2.next())
		{
			model::Item item = recordSet2.get();
			std::cout << item.ID << ": " << item.Name << "\n";
		}
	}
	catch (nanodbc::database_error& ex)
	{
		std::cerr << ex.what() << "\n";
	}
}
