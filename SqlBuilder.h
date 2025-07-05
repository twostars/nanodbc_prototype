#pragma once

#include <string>
#include <set>
#include <iostream>
#include <vector>

/// \brief Used to create safe T-SQL statements for database model objects
template <typename model>
class SqlBuilder
{
public:
	/// \brief returns a select query string based on any configured modifiers
	std::string SelectString()
	{
		std::string query = "SELECT ";
		if (selectCols.empty())
		{
			// fill with all supported model bindings as a default
			fillSelectColumns();
		}

		short i = 0;
		for (const std::string& col : selectCols)
		{
			if (i > 0)
			{
				query += ", ";
			}
			query += '[' + col + ']';
			i++;
		}

		query += " FROM [" + model::TableName() + ']';

		std::cout << "using query: " << query << '\n';
		return query;
	}

	/// \brief sets the columns for a select statement to a subset of bindable values
	///
	/// \param columns list of columns to select
	/// \warning if an input column is not valid for binding it will be ignored and
	/// a warn message will be logged
	void SetSelectColumns(const std::vector<std::string>& columns)
	{
		selectCols.clear();
		for (const std::string& col : columns)
		{
			if (!isValidColumnName(col))
			{
				// TODO:  Logger mechanism
				std::cout << "WARN: Invalid column name: " << col << "for table " << model::TableName() << "\n";
				continue;
			}

			selectCols.insert(col);
		}

	}

	/// \brief excludes a list of columns from the current binding set
	///
	/// \param columns list of columns to exclude from the query
	void ExcludeColumns(const std::vector<std::string>& columns)
	{
		// if selectColumns hasn't been populated, assume the default of SELECT * and filter from that
		if (selectCols.empty())
		{
			fillSelectColumns();
		}

		for (std::size_t i = 0; i < columns.size(); i++)
		{
			if (selectCols.contains(columns.at(i)))
			{
				selectCols.erase(columns.at(i));
			}
		}
	}

private:
	// selectCols is a set of columns that will be used as part of a SELECT query.
	// we use an std::set to prevent duplicate column entries
	std::set<std::string> selectCols;

	bool isValidColumnName(const std::string& colName)
	{
		return model::ColumnNames().contains(colName);
	}

	/// \brief sets selectedCols to the model's supported column set
	void fillSelectColumns()
	{
		selectCols.clear();
		selectCols.insert(model::ColumnNames().begin(), model::ColumnNames().end());
	}
};
