#pragma once

#include <unordered_set>
#include <string>

class ItemBinder;

/// \brief jsonSchema table description
class Item
{
public:
	using BinderType = ItemBinder;

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
		static const std::string tableName = "ITEM";
		return tableName;
	}

	/// \brief returns a constant reference to the std::unordered_set of column names
	///
	/// \note this set should not be manipulated
	static const std::unordered_set<std::string>& ColumnNames()
	{
		static const std::unordered_set<std::string> columnNames =
		{
			"Num", "strName"
		};
		return columnNames;
	}

	/// \brief database type for the model
	static const std::string& DbType()
	{
		static const std::string dbType = "GAME";
		return dbType;
	}
};
