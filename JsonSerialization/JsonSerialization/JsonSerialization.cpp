// JsonSerialization.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"



#include "to_json_test.h"



void test_json_usage1()
{
	Json::Value root;
	root["hello"] = "hehe";
	Json::StyledWriter writer;
	std::string json_str = writer.write(root);
	PRINT_RESULT(json_str);
}

void test_json_usage2()
{
	using namespace std;  

	Json::Value root;  
	Json::Value arrayObj;  
	Json::Value item;  
	item["cpp"] = "jsoncpp";  
	item["java"] = "jsoninjava";  
	item["php"] = "support";  
	arrayObj.append(item);  
	root["name"] = "json";  
	root["array"] = arrayObj;  
	root.toStyledString();  
	std::string out= root.toStyledString();  
	PRINT_RESULT(out);
}
/*
void test_json_float()
{
	Json::Value root;
	//TODO not supported
	root["hello"] = 1.7f; 
	Json::StyledWriter writer;
	std::string json_str = writer.write(root);
	PRINT_RESULT(json_str);
}
*/

void test()
{
	json_test();
	test_json_usage1();
	test_json_usage2();
	//test_json_float();
}

int _tmain(int argc, _TCHAR* argv[])
{
	test();
	getchar();
	return 0;
}

