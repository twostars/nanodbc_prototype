#pragma once

#include <string>
#include <set>
#include <iostream>
#include <vector>

template <typename model>
class SqlBuilder
{
public:
    std::string SelectString()
    {
        std::string query = "SELECT ";
        if (selectCols.empty())
        {
            query += "*";
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
    
    // Query filtering stuff
    void SetSelectColumns(const std::vector<std::string> columns)
    {
        selectCols.clear();
        selectCols.insert(columns.begin(), columns.end());
    }

    void ExcludeColumns(const std::vector<std::string> columns)
    {
        // if selectColumns hasn't been populated, assume the default of SELECT * and filter from that
        if (selectCols.empty())
        {
            fillSelectColumns();
        }

        for (std::size_t i = 0; i < columns.size(); i++)
        {
            selectCols.erase(columns.at(i));
        }
    }

private:
    // selectCols is a set of columns that will be used as part of a SELECT query.
    // we use an std::set to prevent duplicate column entries
    std::set<std::string> selectCols;

    // fillSelectColumns gets the associated model's column vector and converts it to a set
    void fillSelectColumns()
    {
        const std::vector<std::string> cols = model::ColumnNames();
        for (std::size_t i = 0; i < cols.size(); i++)
        {
            selectCols.insert(cols[i]);
        }
    }
};