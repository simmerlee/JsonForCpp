//JsonArray.h

#ifndef _JSONARRAY_H_
#define _JSONARRAY_H_

#include <string>
#include <vector>
#include "JsonValue.h"

class JsonArray : public JsonValue{
public:
    JsonArray(){}
	JsonArray(std::vector<JsonValue *> value):m_value(value){}
	~JsonArray();
	std::string toString();
    int fromString(const char *str, int length);
	bool isString(){return false;}
	bool isArray(){return true;}
	bool isJsonObject(){return false;}
	bool isNumber(){return false;}
	bool isInteger(){return false;}
	bool isDouble(){return false;}
	bool isBool(){return false;}
	
private:
	std::vector<JsonValue *> m_value;
};

#endif//_JSONARRAY_H_
