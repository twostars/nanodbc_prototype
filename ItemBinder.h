#pragma once

#include <unordered_map>
#include <string>

#include <nanodbc/nanodbc.h>

#include "Item.h"

/// \brief generated column binder for the Item model, using nanodbc
class ItemBinder
{
public:
	// static bindings
	typedef void (*BindColumnFunction_t)(Item& m, const nanodbc::result& result, short colIndex);

	using BindingsMapType = std::unordered_map<std::string, BindColumnFunction_t>;

	static const BindingsMapType& GetColumnBindings()
	{
		static const BindingsMapType bindingsMap =
		{
			{ "Num", &ItemBinder::BindNum },
			{ "strName", &ItemBinder::BindName }
		};
		return bindingsMap;
	}

	/// \brief Generated binding function for Num
	static void BindNum(Item& m, const nanodbc::result& result, short colIndex)
	{
		result.get_ref<int>(colIndex, m.Num);
	}

	/// \brief Generated binding function for Name
	static void BindName(Item& m, const nanodbc::result& result, short colIndex)
	{
		result.get_ref<std::string>(colIndex, m.Name);
	}
};
