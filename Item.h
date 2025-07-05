#pragma once

#include <map>
#include <set>
#include <string>

#include "nanodbc/nanodbc.h"

class Item
{
public:
    // static bindings
    typedef void (*ItemBindingFunction)(Item& m, const nanodbc::result& result, short colIndex);
    static std::map<std::string, ItemBindingFunction> ColumnBindings;
    
    
    // Generated Properties
    int         Num;
    std::string Name;

    Item()
    {
        // generate with a default val by type to avoid pulling garbage from memory
        Num = 0;
        Name = "";
    }

    // this would be called via a generated method that calls it for each model
    static void InitBindings()
    {
        // generate bindings
        ColumnBindings[std::string("Num")] = Item::BindNum;
        ColumnBindings[std::string("strName")] = Item::BindName;
    }

    // generated functions to implement Model():  TableName, ColumnNames
    static std::string TableName()
    {
        return "ITEM";
    }

    static const std::set<std::string>& ColumnNames()
    {
        return columnNames;
    }

    static std::string DbType()
    {
        return "GAME";
    }

    // generated binding functions
    static void BindNum(Item& m, const nanodbc::result& result, short colIndex)
    {
        m.Num = result.get<int>(colIndex);
    }

    static void BindName(Item& m, const nanodbc::result& result, short colIndex)
    {
        m.Name = result.get<std::string>(colIndex);
    }
    
private:
    static std::set<std::string> columnNames;
};