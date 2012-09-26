#ifndef XMG_TO_JSON
#define XMG_TO_JSON
#include <vector>
#include <list>
#include <map>
#include <boost/foreach.hpp>
#include <boost/static_assert.hpp>
#include <boost/format.hpp>
#include <json/json.h>

#define JSON_STRUCT_BEGIN(MyStruct) \
	void to_json(Json::Value& v, const std::string& key, const MyStruct& foo)  \
	{ \
		Json::Value tmp_v; 

#define JSON_STRUCT_MEMBER(MyMemberName, MyMember) \
	{\
		Json::Value member_v; \
		to_json(member_v, "", (foo.MyMember)); \
		tmp_v[(MyMemberName)] = member_v;\
	}



#define JSON_STRUCT_END() \
	if (!key.empty()) { \
		v[key] = tmp_v; \
	} else { \
		v = tmp_v; \
	} \
}


template<typename T>
inline void to_json_common_type(Json::Value& v, const std::string& key, const T& value)
{
	if (!key.empty())
		v[key] = value;
	else
		v = Json::Value(value);
}

#define COMMON_TYPE_TO_JSON(type) \
	inline void to_json(Json::Value& v, const std::string& key, type value) \
{\
	to_json_common_type(v, key, value); \
}

COMMON_TYPE_TO_JSON(char)
COMMON_TYPE_TO_JSON(unsigned char)
COMMON_TYPE_TO_JSON(short)
COMMON_TYPE_TO_JSON(unsigned short)
COMMON_TYPE_TO_JSON(int)
COMMON_TYPE_TO_JSON(unsigned int)
COMMON_TYPE_TO_JSON(long)
COMMON_TYPE_TO_JSON(double)


inline void to_json(Json::Value& v, const std::string& key, const std::string& value)
{
	to_json_common_type(v, key, value);
}

inline void to_json(Json::Value& v, const std::string& key, float f);

/*
//TODO the compiler didn't tell which line call this function
inline void to_json(Json::Value& v, const std::string& key, float f)
{
#define FLOAT_TYPE_NOT_SUPPORTED 0
//	BOOST_STATIC_ASSERT(FLOAT_TYPE_NOT_SUPPORTED);
}
*/

//TODO
//COMMON_TYPE_TO_JSON(long long)
//COMMON_TYPE_TO_JSON(unsigned long long)


template<typename Container>
void to_json_serial_container(Json::Value& v, const std::string& key, const Container& foos) 
{
	using namespace Json;
	Value tmp_v;

	BOOST_FOREACH(const Container::value_type& foo, foos) {
		Value item_json;
		to_json(item_json, "", foo);
		tmp_v.append(item_json);
	}

	if (!key.empty()) {
		v[key] = tmp_v;
	} else {
		v = tmp_v;
	}
}

template<typename T>
void to_json(Json::Value& v, const std::string& key, const std::vector<T>& foos) 
{
	to_json_serial_container(v, key, foos);
}

template<typename T>
void to_json(Json::Value& v, const std::string& key, const std::list<T>& foos) 
{
	to_json_serial_container(v, key, foos);
}

inline std::string to_json_key(int value)
{
	return (boost::format("%1%") % value).str();
}

inline std::string to_json_key(const std::string& value)
{
	return value;
}

template<typename K, typename V>
void to_json(Json::Value& v, const std::string& key, const std::map<K, V>& foos) 
{
	typedef std::map<K, V> MapType_t;
	using namespace Json;
	Value tmp_v;

	BOOST_FOREACH(const MapType_t::value_type& foo, foos) {
		const MapType_t::key_type& item_key = foo.first;
		const MapType_t::mapped_type& item_value = foo.second;
		//TODO make item_key_to_string
		Value item_value_json;
		to_json(item_value_json, "", item_value);

		std::string item_json_key = to_json_key(item_key);
		tmp_v[item_json_key] = item_value_json;
	}

	if (!key.empty()) {
		v[key] = tmp_v;
	} else {
		v = tmp_v;
	}
}



#endif //XMG_TO_JSON