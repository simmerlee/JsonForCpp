//JsonNumber.cpp

#include "JsonNumber.h"
#include <iostream>

using namespace std;

JsonNumber::JsonNumber(short value){
	m_isInteger = true;
	itoa64(value);
}

JsonNumber::JsonNumber(int value){
	m_isInteger = true;
	itoa64(value);
}

JsonNumber::JsonNumber(long long value){
	m_isInteger = true;
	itoa64(value);
}

JsonNumber::JsonNumber(float value){
	m_isInteger = false;
	ftoa(value);
}

JsonNumber::JsonNumber(double value){
	m_isInteger = false;
	dtoa(value);
}


int JsonNumber::getInt(){
	if(m_isInteger == true)
		return (int)atoi64(m_value);
	else
		return (int)atod(m_value);
}

long long JsonNumber::getLongLong(){
	if(m_isInteger == true)
		return atoi64(m_value);
	else
		return (long long)atod(m_value);
}

float JsonNumber::getFloat(){
	if(m_isInteger == true)
		return (float)atoi64(m_value);
	else
		return atof(m_value);
}

double JsonNumber::getDouble(){
	if(m_isInteger == true)
		return (double)atoi64(m_value);
	else
		return atod(m_value);
}

string JsonNumber::toString(){
	return m_value;
}

void JsonNumber::itoa64(long long value){
	char temp[24];
	temp[23] = '\0';
	char *p = &temp[22];
	while(value/10 != 0)
	{ 
		*(p--) = value%10 + 48; 
		value = value /10;
	}
	*p = value%10 + 48;
	m_value.assign(p);
}

long long JsonNumber::atoi64(string value){
	int e = 1, result = 0;
	int i = value.length() -1;
	while(i >= 0){
		result += (value[i--] - '0') * e;
		e *= 10;
	}
	return result;
}


void JsonNumber::ftoa(float value){
	char buf[128];
	sprintf(buf, "%f", value);
	m_value.assign(buf);
}

void JsonNumber::dtoa(double value){
	char buf[128];
	sprintf(buf, "%lf", value);
	m_value.assign(buf);
}

double JsonNumber::atod(string value){
	double result;
	sscanf(value.c_str(), "%lf", &result);
	return result;
}

float JsonNumber::atof(string value){
	float result;
	sscanf(value.c_str(), "%f", &result);
	return result;
}

int JsonNumber::fromString(const char *str, int length)
{
    bool exitFlag = false;
    int state = 1;
    int i = 0;
    m_value.clear();
    while(i < length)
    {
        switch(state)
        {
        case 1:
            if(*str == '-')
            {
                m_value.push_back(*str);
                str++;
                i++;
            }
            state = 2;
            break;
        case 2:
            if((*str) <= '9' && (*str) >= '1')
            {
                m_value.push_back(*str);
                str++;
                i++;
                state = 3;
            }
            else if(*str == '0')
            {
                m_value.push_back(*str);
                str++;
                i++;
                state = 4;
            }
            else
                state = -1;
            break;
        case 3:
            while((*str) <= '9' && (*str) >= '0')
            {
                m_value.push_back(*str);
                str++;
                i++;
            }
            state = 4;
            break;
        case 4:
            if(*str == '.')
            {
                m_value.push_back(*str);
                str++;
                i++;
                state = 5;
            }
            else
                state = 6;
            break;
        case 5:
            while((*str) <= '9' && (*str) >= '0')
            {
                m_value.push_back(*str);
                str++;
                i++;
            }
            state = 6;
        case 6:
            if(*str == 'e' || *str == 'E')
            {
                m_value.push_back(*str);
                str++;
                i++;
                state = 7;
            }
            else
                exitFlag = true;
            break;
        case 7:
            if(*str == '-' || *str == '+')
            {
                m_value.push_back(*str);
                str++;
                i++;
            }
            while((*str) <= '9' && (*str) >= '0')
            {
                m_value.push_back(*str);
                str++;
                i++;
            }
            exitFlag = true;
            break;
        case -1:
            //throw exception
            break;
        default:
            //throw exception
            break;
        }
        if(exitFlag == true)
            break;
    }
    if(exitFlag == false && i >= length)
        cout<<"Out of range."<<endl;
    return i;
}
