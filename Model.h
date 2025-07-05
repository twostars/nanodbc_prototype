#pragma once

#include <iostream>
#include <string>

#include "SqlBuilder.h"
#include "nanodbc/nanodbc.h"

// Model implements common underlying members and functions needed to support database operations
class Model
{
    // Mostly hand-coded template with some possible generated functions/properties.
public:
    template <typename T>
    static std::vector<T> BatchSelect(SqlBuilder<T> sql = SqlBuilder<T>()) noexcept(false)
    {
        std::string query = sql.SelectString();
        std::vector<T> resultModels;
        nanodbc::connection conn = DatabaseConnManager::GetConnectionTo(T::DbType());
        nanodbc::statement stmt = nanodbc::statement(conn, query);
        nanodbc::result result = nanodbc::execute(stmt);

        // result always starts before the first row, so calling next will not skip the first result.
        while (result.next())
        {
            T res = T();
            Model::BindResult(result, res);
            resultModels.push_back(res);
        }
        
        stmt.close();
        conn.disconnect();

        return resultModels;
    }

    template <typename T>
    static void BindResult(const nanodbc::result& result, T& model)
    {
        for (short i = 0; i < result.columns(); i++)
        {
            try
            {
                auto bind = T::ColumnBindings[result.column_name(i)];
                if (bind != nullptr)
                {
                    std::invoke(bind, model, result, i);
                }
                else
                {
                    std::cout << "WARN: No binding found for:" << T::TableName() << "." << result.column_name(i) << "\n";
                }
            }
            catch (std::out_of_range& ex)
            {
                std::cout << "WARN: No binding found for:" << T::TableName() << "." << result.column_name(i) << "\n";
            }
            catch (std::exception& ex2)
            {
                std::cout << ex2.what() << "\n";
            }
        }
    }
};