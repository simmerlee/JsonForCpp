//JsonNumber.h

#ifndef _JSONNUMBER_H_
#define _JSONNUMBER_H_

#include <string>
#include "JsonValue.h"

class JsonNumber : public JsonValue{
public:
	JsonNumber(){}
	~JsonNumber(){}
	JsonNumber(int value);
	JsonNumber(short value);
	JsonNumber(long long value);
	JsonNumber(float value);
	JsonNumber(double value);
	static JsonNumber buildJsonNumber(long long value){ JsonNumber n(value); return n;}
	static JsonNumber buildJsonNumber(double value){ JsonNumber n(value); return n;}
	std::string toString();
    int fromString(const char *str, int length);
	int getInt();	
	long long getLongLong();
	float getFloat();
	double getDouble();
	bool isString(){return false;}
	bool isArray(){return false;}
	bool isJsonObject(){return false;}
	bool isNumber(){return true;}
	bool isInteger(){return true;} //TODO
	bool isDouble(){return true;} //TODO
	bool isBool(){return false;}

private:
	void itoa64(long long value);
	long long atoi64(std::string value);
	void ftoa(float value);
	void dtoa(double value);
	float atof(std::string value);
	double atod(std::string value);

	std::string m_value;
	bool m_isInteger;
};

#endif//_JSONNUMBER_H_
