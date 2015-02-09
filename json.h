//json.h

#ifndef _JSON_H_
#define _JSON_H_

#include <string>
#include <vector>
#include <map>
#include "JsonValue.h"
#include "JsonArray.h"
#include "JsonNumber.h"
#include "JsonString.h"


class Json : public JsonValue{
public:
	Json(){}
	~Json();
	int putInteger(std::string key, long long value);
	int putDouble(std::string key, double value);
	int putString(std::string key, std::string value);
	int putJsonObject(std::string key, Json* value);
	int putArray(std::string key, std::vector<JsonValue *> value);
	int putArray(std::string key, std::vector<double> value);
	int putArray(std::string key, std::vector<std::string> value);
	int putArray(std::string key, std::vector<long long> value);
	//int putBool(std::string key, int value);
	long long getInteger(std::string key);
	double getDouble(std::string key);
	std::string getString(std::string key);
	Json* getJsonObject(std::string key);
	JsonArray* getArray(std::string key);
	JsonValue* getJsonValue(std::string key);
	//int getBool(std::string key);
	int fromString(const std::string str);
    int fromString(const char *string, int length);
	std::string toString();
	bool isString(){return false;}
	bool isJsonObject(){return true;}
	bool isArray(){return false;}
	bool isNumber(){return false;}
	bool isInteger(){return false;}
	bool isDouble(){return false;}
	bool isBool(){return false;}
private:
	std::map<std::string, JsonValue *> m_value;
};

#endif//_JSON_H_
