#pragma once

#include <string>

#include "Model.h"
#include "SqlBuilder.h"
#include "nanodbc/nanodbc.h"

template <typename T>
class ModelRecordSet
{
public:
    ModelRecordSet(SqlBuilder<T> filterObj = SqlBuilder<T>()) noexcept(false)
    {
        conn = DatabaseConnManager::GetConnectionTo(T::DbType());
        std::string query = filterObj.SelectString();
        stmt = nanodbc::statement(conn, query);
        result = nanodbc::execute(stmt);
    }

    ~ModelRecordSet()
    {
        Close();
    }

    void Close()
    {
        stmt.close();
        conn.disconnect();
    }

    bool empty()
    {
        return result.rows() == 0;
    }

    int rows()
    {
        return result.rows();
    }

    T get()
    {
        T model = T();
        Model::BindResult(result, model);
        return model;
    }

    bool next()
    {
        return result.next();
    }

private:
    nanodbc::connection conn;
    nanodbc::statement stmt;
    nanodbc::result result;
};