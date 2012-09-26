#include "stdafx.h"
#include "to_json_test.h"
#include <boost/format.hpp>


to_json_test::to_json_test(void)
{
}


to_json_test::~to_json_test(void)
{
}


struct Foo1
{
	std::string m_name;
	int			m_age;
};

JSON_STRUCT_BEGIN(Foo1)
	JSON_STRUCT_MEMBER("name", m_name)
	JSON_STRUCT_MEMBER("age", m_age)
JSON_STRUCT_END()


typedef std::vector<Foo1> FooVec_t;
typedef std::map<std::string, Foo1> FooMap_t;
typedef std::map<std::string, FooVec_t> FooVecMap_t;


static void create_foo_vec(FooVec_t& foos)
{
	for (size_t i = 0; i < 3; ++i) {
		Foo1 foo;
		foo.m_name = "eric";
		foo.m_age = i;

		foos.push_back(foo);
	}
}

void test_foo_vec_map()
{
	using namespace Json;
	Value v;

	FooVecMap_t foo_map;
	for (int i = 0; i < 3; ++i) {
		std::string map_key = (boost::format("foo%d") % i).str();
		FooVec_t foo_vec;
		create_foo_vec(foo_vec);
		foo_map.insert(FooVecMap_t::value_type(map_key, foo_vec));
	}

	to_json(v, "foo_map", foo_map);

	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);
}


void test_FooMap_with_key()
{
	using namespace Json;
	Value v;

	FooMap_t foo_map;
	for (int i = 0; i < 3; ++i) {
		Foo1 foo;
		foo.m_name = "eric";
		foo.m_age = i;

		std::string map_key = (boost::format("foo%d") % i).str();
		foo_map.insert(FooMap_t::value_type(map_key, foo));
	}

	to_json(v, "foo_map", foo_map);

	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);
}

void test_FooMap_without_key()
{
	using namespace Json;
	Value v;

	FooMap_t foo_map;
	for (int i = 0; i < 3; ++i) {
		Foo1 foo;
		foo.m_name = "eric";
		foo.m_age = i;

		std::string map_key = (boost::format("foo%d") % i).str();
		foo_map.insert(FooMap_t::value_type(map_key, foo));
	}

	to_json(v, "", foo_map);

	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);
}




void test_Foo1s_without_key()
{
	FooVec_t foos;
	for (size_t i = 0; i < 3; ++i) {
		Foo1 foo;
		foo.m_name = "eric";
		foo.m_age = i;

		foos.push_back(foo);
	}

	using namespace Json;
	Value v;

	to_json(v, "", foos);
	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);
}

void test_Foo1s_with_key()
{
	FooVec_t foos;
	for (size_t i = 0; i < 3; ++i) {
		Foo1 foo;
		foo.m_name = "eric";
		foo.m_age = i;

		foos.push_back(foo);
	}

	using namespace Json;
	Value v;

	to_json(v, "foo1s", foos);
	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);
}

void test_to_json_Foo1_with_key()
{
	using namespace Json;
	Value v;

	Foo1 foo;
	foo.m_name = "eric";
	foo.m_age = 30;

	to_json(v, "foo", foo);
	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);
}

void test_to_json_Foo1_without_key()
{
	using namespace Json;
	Value v;

	Foo1 foo;
	foo.m_name = "eric";
	foo.m_age = 30;

	to_json(v, "", foo);
	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);
}




void Foo_test()
{
	test_foo_vec_map();
	test_FooMap_without_key();
	test_FooMap_with_key();
	test_Foo1s_without_key();
	test_Foo1s_with_key();
	test_to_json_Foo1_without_key();
	test_to_json_Foo1_with_key();
}

//---------------------------------------------------------------------------------------
struct S3
{
	std::string name;
	int age;
};


struct S2
{
	std::string name;
	int age;
	S3 s3;
};

struct S1
{
	std::string name;
	int age;
	S2 s2;
};


JSON_STRUCT_BEGIN(S3)
	JSON_STRUCT_MEMBER("name", name)
	JSON_STRUCT_MEMBER("age", age)
JSON_STRUCT_END()

JSON_STRUCT_BEGIN(S2)
	JSON_STRUCT_MEMBER("name", name)
	JSON_STRUCT_MEMBER("age", age)
	JSON_STRUCT_MEMBER("s3", s3)
JSON_STRUCT_END()

JSON_STRUCT_BEGIN(S1)
	JSON_STRUCT_MEMBER("name", name)
	JSON_STRUCT_MEMBER("age", age)
	JSON_STRUCT_MEMBER("s2", s2)
JSON_STRUCT_END()

void test_subchild()
{
	S3 s3;
	s3.name = "s3";
	s3.age = 3;

	S2 s2;
	s2.name = "s2";
	s2.age = 2;
	s2.s3 = s3;

	S1 s1;
	s1.name = "s1";
	s1.age = 1;
	s1.s2 = s2;

	using namespace Json;
	Value v;

	to_json(v, "", s1);
	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);
}

//--------------------------------------------------------------------------
struct SWithVec
{
	std::string name;
	std::vector<std::string> nicknames;
};

JSON_STRUCT_BEGIN(SWithVec)
	JSON_STRUCT_MEMBER("name", name)
	JSON_STRUCT_MEMBER("nicknames", nicknames)
JSON_STRUCT_END()

void test_struct_with_vec()
{
	SWithVec s;
	s.name = "eric";
	s.nicknames.push_back("xmg");
	s.nicknames.push_back("xmg1");

	using namespace Json;
	Value v;

	to_json(v, "", s);
	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);
}

//-------------------------------------------------------------------------------------------
//map key not string
void test_map_key_not_string()
{
	typedef std::map<int, int> IntMap_t;
	IntMap_t int_map;
	int_map.insert(IntMap_t::value_type(0, 0));
	int_map.insert(IntMap_t::value_type(1, 1));
	int_map.insert(IntMap_t::value_type(2, 2));

	using namespace Json;
	Value v;

	to_json(v, "", int_map);
	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);
}

enum STUPID_ENUM { STUPID_0, STUPID_1, STUPID_2};

struct SWithEnum
{
	std::string name;
	STUPID_ENUM  e;
};

JSON_STRUCT_BEGIN(SWithEnum)
	JSON_STRUCT_MEMBER("name", name)
	JSON_STRUCT_MEMBER("enum", e)
JSON_STRUCT_END()

void test_enum_member()
{
	SWithEnum s;
	s.name = "SWithEnum";
	s.e = STUPID_2;

	using namespace Json;
	Value v;

	to_json(v, "", s);
	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);


}

/*
//not supported
struct SWithFloat
{
	float	f;
};

JSON_STRUCT_BEGIN(SWithFloat)
	JSON_STRUCT_MEMBER("float", f)
JSON_STRUCT_END()


void test_float_member()
{
	SWithFloat s;
	s.f = 1.7f;

	using namespace Json;
	Value v;

	to_json(v, "", s);
	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);
}
*/

struct SWithCommonType
{
	char c;
	unsigned char uc;
	short s;
	unsigned short us;
	int i;
	unsigned int ui;
	long l;
	double d;
};

JSON_STRUCT_BEGIN(SWithCommonType)
	JSON_STRUCT_MEMBER("char", c)
	JSON_STRUCT_MEMBER("unsigned char", uc)
	JSON_STRUCT_MEMBER("short", s)
	JSON_STRUCT_MEMBER("unsigned short", us)
	JSON_STRUCT_MEMBER("int", i)
	JSON_STRUCT_MEMBER("unsigned int", ui)
	JSON_STRUCT_MEMBER("long", l)
	JSON_STRUCT_MEMBER("double", d)
JSON_STRUCT_END()

void test_common_type()
{
	SWithCommonType s;
	s.c = 'c';
	s.uc = 255;
	s.s = -255;
	s.us = 255;
	s.i = -255;
	s.ui = 255;
	s.l = 255;
	s.d = 1.7;

	using namespace Json;
	Value v;

	to_json(v, "", s);
	std::string ret = v.toStyledString();
	PRINT_RESULT(ret);
}

void json_test()
{
	test_common_type();
	//test_float_member();
	test_enum_member();
	test_map_key_not_string();
	test_struct_with_vec();
	test_subchild();
	Foo_test();
}





