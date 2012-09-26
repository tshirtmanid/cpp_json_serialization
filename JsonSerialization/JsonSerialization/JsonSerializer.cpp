#include "JsonSerializer.h"

void MakeJson(Json::Value& jValue, const std::string& strKey, const std::string& strValue)
{
	jValue[strKey] = strValue;
}

void MakeJson(Json::Value& jValue, const std::string& strKey, const int& nValue)
{
	char buf[512] = {0};
	sprintf_s(buf, "%d", nValue);

	MakeJson(jValue, strKey, std::string(buf));
}