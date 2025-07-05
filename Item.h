#pragma once

#include <map>
#include <set>
#include <string>

#include "nanodbc/nanodbc.h"

/// \brief jsonSchema table description
class Item
{
public:
    // static bindings
    typedef void (*ItemBindingFunction)(Item& m, const nanodbc::result& result, short colIndex);
    static std::map<std::string, ItemBindingFunction> ColumnBindings;
    
    
    /// \brief jsonSchema column description
    int         Num;

    /// \brief jsonSchema column description
    /// \note maxLength: jsonSchema.column.length
    std::string Name;

    Item()
    {
        // generate with a default val by type to avoid pulling garbage from memory
        Num = 0;
        Name = "";
    }

    /// \brief initiates the 
    /// \note this would be called via a generated method that calls it for each model
    static void InitBindings()
    {
        if (!isBindInit)
        {
            ColumnBindings[std::string("Num")] = Item::BindNum;
            ColumnBindings[std::string("strName")] = Item::BindName;
            isBindInit = true;
        }
    }

    /// \brief table name
    static std::string TableName()
    {
        return "ITEM";
    }

    /// \brief returns a constant reference to the std::set of column names
    ///
    /// \note this set should not be manipulated
    static const std::set<std::string>& ColumnNames()
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
    static std::set<std::string> columnNames;
    static bool isBindInit;
};