#pragma once

#include "stdafx.h"
#include <json/json.h>
#include <vector>

void MakeJson(Json::Value& jValue, const std::string& strKey, const std::string& strValue);

void MakeJson(Json::Value& jValue, const std::string& strKey, const int& nValue);

template<typename Con>
void MakeJson(Json::Value& jValue, const std::string& strKey, const Con& container, const std::string& strElemKey)
{
	Json::Value tmpJValue;

	typename Con::const_iterator b = container.begin();
	typename  Con::const_iterator e = container.end();
	for (; b != e; ++b)
	{
		const typename Con::value_type& elem = *b;

		Json::Value tmpElemValue;
		MakeJson(tmpElemValue, strElemKey, elem);
		tmpJValue.append(tmpElemValue);
	}

	if (strKey.empty())
	{
		jValue = tmpJValue;
	}
	else
	{
		jValue[strKey] = tmpJValue;
	}
}


#define MAKE_JSON_ELEM(strKey, v) MakeJson(tmpJValue, strKey, value.v);

#define MAKE_JSON_ENUM_ELEM(strKey, v) MakeJson(tmpJValue, strKey, (int)value.v);

//todo 思考是否可以去掉inline?
#define MAKE_JSON_STRUCT_START(Type) \
	inline void MakeJson(Json::Value& jValue, const std::string& strKey, const Type& value) \
	{ \
		Json::Value tmpJValue; 

#define MAKE_JSON_STRUCT_END() \
	if (strKey.empty()) \
	{ \
		jValue = tmpJValue; \
	} \
	else \
	{ \
		jValue[strKey] = tmpJValue; \
	} \
}