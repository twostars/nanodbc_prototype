#include "Item.h"
#include "nanodbc/nanodbc.h"

std::unordered_map<std::string, Item::BindColumnFunction_t> Item::ColumnBindings =
{
	{ "Num", &Item::BindNum },
	{ "strName", &Item::BindName }
};

std::string Item::tableName = "ITEM";
std::string Item::dbType = "GAME";

std::unordered_set<std::string> Item::columnNames = { "Num", "strName" };

/// \brief Generated binding function for Num
void Item::BindNum(Item& m, const nanodbc::result& result, short colIndex)
{
	result.get_ref<int>(colIndex, m.Num);
}

/// \brief Generated binding function for Name
void Item::BindName(Item& m, const nanodbc::result& result, short colIndex)
{
	result.get_ref<std::string>(colIndex, m.Name);
}
