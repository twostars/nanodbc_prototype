#include "Item.h"

// static member initialization.  Needs to be done here or there'll be linker errors
std::map<std::string, Item::ItemBindingFunction> Item::ColumnBindings = std::map<std::string, Item::ItemBindingFunction>();
std::set<std::string> Item::columnNames = std::set<std::string> { "Num", "strName" };
bool Item::isBindInit = false;
