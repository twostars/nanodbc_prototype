#pragma once

#include <string>

#include "Model.h"
#include "SqlBuilder.h"
#include "nanodbc/nanodbc.h"

/// \brief queries the templated model table using an iterator to the result set
template <typename T>
class ModelRecordSet
{
public:
	/// \brief opens a connection to the model's database and queries its table using 
	/// a SqlBuilder.
	/// Results are accessed by iterating with next() and requesting a bound model object
	/// with get()
	///
	/// \see next(), get()
	/// \throws nanodbc::database_error
	ModelRecordSet(SqlBuilder<T>& filterObj) noexcept(false)
	{
		open(filterObj);
	}

	/// \brief opens a connection to the model's database and queries its table using 
	/// a SqlBuilder.
	/// Results are accessed by iterating with next() and requesting a bound model object
	/// with get()
	///
	/// \see next(), get()
	/// \throws nanodbc::database_error
	ModelRecordSet() noexcept(false)
	{
		SqlBuilder<T> filterObj {};
		open(filterObj);
	}

	~ModelRecordSet()
	{
		Close();
	}

	/// \brief closes and releases all associated database resources
	void Close()
	{
		stmt.close();
		conn.disconnect();
		conn.deallocate();
	}

	/// \brief binds the current result record to an associated model object and returns it
	T get()
	{
		T model {};
		Model::BindResult(result, model, bindingIndex);
		return model;
	}

	/// \brief attempts to move the result iterator one forward
	///
	/// \return Boolean: true if there is a next record, false otherwise
	bool next()
	{
		return result.next();
	}

protected:
	/// \brief opens a connection to the model's database and queries its table using 
	/// a SqlBuilder.
	/// Results are accessed by iterating with next() and requesting a bound model object
	/// with get()
	///
	/// \see next(), get()
	/// \throws nanodbc::database_error
	void open(SqlBuilder<T>& filterObj) noexcept(false)
	{
		conn = DatabaseConnManager::GetConnectionTo(T::DbType());
		std::string query = filterObj.SelectString();
		stmt = nanodbc::statement(conn, query);
		result = nanodbc::execute(stmt);

		Model::IndexColumnNameBindings<T>(result, bindingIndex);
	}

private:
	nanodbc::connection conn;
	nanodbc::statement stmt;
	nanodbc::result result;
	Model::BindingIndex<T> bindingIndex;
};
