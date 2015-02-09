//Json.cpp

#include "Json.h"
#include <vector>
#include <iostream>

using namespace std;

Json::~Json(){
	map<string, JsonValue*>::iterator it = m_value.begin();
	while(it != m_value.end()){
		delete it->second;
		it++;
	}
}

string Json::toString(){
	string s;
	s.append("{");
	map<string, JsonValue*>::iterator it = m_value.begin();
    if(m_value.size() > 0){
        s.append("\"" + it->first + "\":" + it->second->toString());
        it++;
        while(it != m_value.end()){
            s.append(",\"" + it->first + "\":" + it->second->toString());
            it++;
        }
    }
    s.append("}");
	return s;
}
	

int Json::putArray(string key, vector<double> value){
	JsonValue *number;
	JsonValue *array;
	vector<JsonValue *> valueVector;
	int i = 0, count = value.size();
	while(i < count){
		number = new JsonNumber(value[i++]);
		valueVector.push_back(number);
	}
	array = new JsonArray(valueVector);
	m_value[key] = array;
	return 0;
}

int Json::putArray(string key, vector<long long> value){
	JsonValue *number;
	JsonValue *array;
	vector<JsonValue *> valueVector;
	int i = 0, count = value.size();
	while(i < count){
		number = new JsonNumber(value[i++]);
		valueVector.push_back(number);
	}
	array = new JsonArray(valueVector);
	m_value[key] = array;
	return 0;
}

int Json::putArray(string key, vector<string> value){
    JsonValue *v;
	JsonValue *array;
	vector<JsonValue *> valueVector;
	int i = 0, count = value.size();
	while(i < count){
        v = new JsonString(value[i++]);
        valueVector.push_back(v);
	}
	array = new JsonArray(valueVector);
	m_value[key] = array;
	return 0;
}
	
int Json::putInteger(string key, long long value){
	JsonValue *number = new JsonNumber(value);
	m_value[key] = number;
    return 0;
}

int Json::putDouble(string key, double value){
	JsonValue *number = new JsonNumber(value);
	m_value[key] = number;
    return 0;
}

int Json::putString(string key, string value){
	JsonValue *str = new JsonString(value);
	m_value[key] = str;
    return 0;
}

int Json::putJsonObject(string key, Json* value){
	JsonValue *json = new Json(*value);
	m_value[key] = json;
    return 0;
}


long long Json::getInteger(string key){
	if(m_value.find(key) != m_value.end())
		if(m_value[key]->isInteger())
			return (long long)(((JsonNumber*)(m_value[key]))->getLongLong());
	return -1;
}

double Json::getDouble(string key){
	if(m_value.find(key) != m_value.end())
		if(m_value[key]->isDouble())
			return (double)(((JsonNumber*)(m_value[key]))->getDouble());
	return -1;
}

string Json::getString(string key){
	if(m_value.find(key) != m_value.end())
		if(m_value[key]->isString())
			return m_value[key]->toString();
	return "";
}

Json* Json::getJsonObject(string key){
	if(m_value.find(key) != m_value.end())
		if(m_value[key]->isJsonObject())
			return (Json *)(m_value[key]);
	return NULL;
}

JsonArray* Json::getArray(string key){
	if(m_value.find(key) != m_value.end())
		if(m_value[key]->isArray())
			return (JsonArray *)(m_value[key]);
	return NULL;
}

JsonValue* Json::getJsonValue(string key){
	if(m_value.find(key) != m_value.end())
		return m_value[key];
	return NULL;
}

int Json::fromString(const char* str, int length){
    int state = 1;
    int len;
    int i = 0;
    bool exitFlag = false;
    JsonValue *value;
    JsonString js;
    str++;
    m_value.clear();
    while(1)
    {
        switch(state)
        {
        case 1:
            while(isBlank(*str))
            {
                i++;
                str++;
            }
            if(*str == '}')
            {
                i++;
                exitFlag = true;
                break;
            }
            state = 2;
            break;
        case 2:
            if(*str != '\"')
            {
                state = -1;
                break;
            }
            len = js.fromString(str, length-i);
            i += len;
            str += len;
            while(isBlank(*str))
            {
                i++;
                str++;
            }
            if(*str != ':')
            {
                state = -1;
                break;
            }
            i++;
            str++;
            while(isBlank(*str))
            {
                i++;
                str++;
            }
            if(*str == '\"')
                value = new JsonString();
            else if(*str >= '0' && *str <= '9')
                value = new JsonNumber();
            else if(*str == '[')
                value = new JsonArray();
            else if(*str == '{')
                value = new Json();
            else
            {
                state = -1;
                break;
            }
            len = value->fromString(str, length-i);
            i += len;
            str += len;
            m_value[js.getValue()] = value;
            state = 3;
            break;
        case 3:
            while(isBlank(*str))
            {
                i++;
                str++;
            }
            if(*str == '}')
            {
                i++;
                exitFlag = true;
                break;
            }
            if(*str != ',')
            {
                state = -1;
                break;
            }
            do
            {
                i++;
                str++;
            }
            while(isBlank(*str));
            state = 2;
            break;
        case -1:
            cout<<"format error."<<endl;
            break;
        }
        if(exitFlag == true)
            break;
    }
    if(exitFlag == false)
        cout<<"Out of range."<<endl;
    return i+1;
}
