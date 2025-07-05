#include "Item.h"

std::map<std::string, Item::ItemBindingFunction> Item::ColumnBindings = std::map<std::string, Item::ItemBindingFunction>();
std::set<std::string> Item::columnNames = std::set<std::string>{"Num", "strName"};