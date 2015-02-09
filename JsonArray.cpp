//JsonArray.cpp

#include <iostream>
#include "JsonArray.h"
#include "JsonNumber.h"
#include "JsonString.h"
#include "Json.h"

using namespace std;

JsonArray::~JsonArray(){
		int i = 0;
		int count = m_value.size();
		while(i < count)
			delete m_value[i++];
}

string JsonArray::toString(){
        int i = 1;
		int count  = m_value.size();
		string result;
		result.append("[");
        if(m_value.size() > 0)
        {
            result.append(m_value[0]->toString());
            while(i < count)
                result.append("," + m_value[i++]->toString());
        }
        result.append("]");
		return result;
}

int JsonArray::fromString(const char *str, int length)
{
    int i = 0;
    int state = 1;
    int len; //return from JsonValue::fromString()
    bool exitFlag = false;
    JsonValue *value;
    m_value.clear();
    str++;
    while(i < length)
    {
        switch(state)
        {
        case 1:
            while(isBlank(*str))
            {
                str++;
                i++;
            }
            if(*str == ']')
            {
                i++;
                exitFlag = true;
                break;
            }
            state = 2;
            break;
        case 2:
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
            m_value.push_back(value);
            state = 3;
            break;
        case 3:
            while(isBlank(*str))
            {
                str++;
                i++;
            }
            if(*str == ']')
            {
                i++;
                exitFlag = true;
                break;
            }
            if(*str == ',')
            {
                do
                {
                    i++;
                    str++;
                }
                while(isBlank(*str));
                state = 2;
                break;
            }
        case -1:
            cout<<"json array error."<<endl;
            break;
        }
        if(exitFlag == true)
            break;
    }
    if(exitFlag == false)
        cout<<"out of range."<<endl;
    return i + 1;
}
