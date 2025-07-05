#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

namespace nanodbc
{
	class result;
}

/// \brief jsonSchema table description
class Item
{
public:
	// static bindings
	typedef void (*BindColumnFunction_t)(Item& m, const nanodbc::result& result, short colIndex);
	static std::unordered_map<std::string, BindColumnFunction_t> ColumnBindings;

	/// \brief jsonSchema column description
	int         Num;

	/// \brief jsonSchema column description
	/// \note maxLength: jsonSchema.column.length
	std::string Name;

	Item()
	{
		// generate with a default val by type to avoid pulling garbage from memory
		Num = 0;
	}

	/// \brief table name
	static const std::string& TableName()
	{
		return tableName;
	}

	/// \brief returns a constant reference to the std::unordered_set of column names
	///
	/// \note this set should not be manipulated
	static const std::unordered_set<std::string>& ColumnNames()
	{
		return columnNames;
	}

	/// \brief database type for the model
	static const std::string& DbType()
	{
		return dbType;
	}

	/// \brief Generated binding function for Num
	static void BindNum(Item& m, const nanodbc::result& result, short colIndex);

	// \brief Generated binding function for Name
	static void BindName(Item& m, const nanodbc::result& result, short colIndex);

private:
	static std::string tableName;
	static std::string dbType;
	static std::unordered_set<std::string> columnNames;
};
