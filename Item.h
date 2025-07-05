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
	typedef void (*ItemBindingFunction)(Item& m, const nanodbc::result& result, short colIndex);
	static std::unordered_map<std::string, ItemBindingFunction> ColumnBindings;

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
		m.Num = result.get<int>(colIndex);
	}

	/// \brief Generated binding function for Name
	static void BindName(Item& m, const nanodbc::result& result, short colIndex)
	{
		m.Name = result.get<std::string>(colIndex);
	}

private:
	static std::unordered_set<std::string> columnNames;
};

std::unordered_map<std::string, Item::ItemBindingFunction> Item::ColumnBindings =
{
	{ "Num", &Item::BindNum },
	{ "strName", &Item::BindName }
};

std::unordered_set<std::string> Item::columnNames = { "Num", "strName" };
