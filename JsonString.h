//JsonString.h

#ifndef _JSONSTRING_H_
#define _JSONSTRING_H_

#include <string>
#include "JsonValue.h"

class JsonString : public JsonValue{
public:
    JsonString(){}
	JsonString(std::string str):m_value(str){}
	~JsonString(){}
    int fromString(const char *str, int length);
    std::string toString();
    std::string getValue(){ return m_value; }
	bool isString(){return true;}
	bool isArray(){return false;}
	bool isJsonObject(){return false;}
	bool isNumber(){return false;}
	bool isInteger(){return false;}
	bool isDouble(){return false;}
	bool isBool(){return false;}
private:
	std::string m_value;
};

#endif//_JSONSTRING_H_
