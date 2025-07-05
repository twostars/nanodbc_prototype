#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "nanodbc/nanodbc.h"

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
	static std::string TableName()
	{
		return "ITEM";
	}

	/// \brief returns a constant reference to the std::unordered_set of column names
	///
	/// \note this set should not be manipulated
	static const std::unordered_set<std::string>& ColumnNames()
	{
		return columnNames;
	}

	/// \brief database type for the model
	static std::string DbType()
	{
		return "GAME";
	}

	/// \brief Generated binding function for Num
	static void BindNum(Item& m, const nanodbc::result& result, short colIndex)
	{
		result.get_ref<int>(colIndex, m.Num);
	}

	/// \brief Generated binding function for Name
	static void BindName(Item& m, const nanodbc::result& result, short colIndex)
	{
		result.get_ref<std::string>(colIndex, m.Name);
	}

private:
	static std::unordered_set<std::string> columnNames;
};

std::unordered_map<std::string, Item::BindColumnFunction_t> Item::ColumnBindings =
{
	{ "Num", &Item::BindNum },
	{ "strName", &Item::BindName }
};

std::unordered_set<std::string> Item::columnNames = { "Num", "strName" };
