#pragma once

#include <iostream>
#include <string>

#include "SqlBuilder.h"
#include "nanodbc/nanodbc.h"

/// \brief acts as an identifying base class for generated model classes and contains
/// static binding and SQL operations.  Should never have non-static methods/members
/// to maintain a minimal footprint
class Model
{
	// Mostly hand-coded template with some possible generated functions/properties.
public:
	/// \brief uses a SqlBuilder to select a batch of data in a single trip to the database
	///
	/// \param sql SqlBuilder used to modify the select query
	/// \note this currently acts as an iterator and is not efficient
	/// \see ModelRecordSet for efficient iterator implementation until this is done correctly
	template <typename T>
	static std::vector<T> BatchSelect(SqlBuilder<T> sql = SqlBuilder<T>()) noexcept(false)
	{
		std::string query = sql.SelectString();
		std::vector<T> resultModels;
		nanodbc::connection conn = DatabaseConnManager::GetConnectionTo(T::DbType());
		nanodbc::statement stmt = nanodbc::statement(conn, query);
		nanodbc::result result = nanodbc::execute(stmt);

		// result always starts before the first row, so calling next will not skip the first result.
		while (result.next())
		{
			T res = T();
			Model::BindResult(result, res);
			resultModels.push_back(res);
		}

		stmt.close();
		conn.disconnect();

		return resultModels;
	}

	/// \brief attempts to bind a result row to a given model class's members
	template <typename T>
	static void BindResult(const nanodbc::result& result, T& model)
	{
		for (short i = 0; i < result.columns(); i++)
		{
			auto bind = T::ColumnBindings[result.column_name(i)];
			if (bind == nullptr)
			{
				// TODO: logger impl
				std::cout << "WARN: No binding found for:" << T::TableName() << "." << result.column_name(i) << "\n";
				continue;
			}

			std::invoke(bind, model, result, i);
		}
	}
};
