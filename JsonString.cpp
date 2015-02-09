//JsonString.cpp

#include "JsonString.h"

using namespace std;

string JsonString::toString()
{
    string s;
    const char *str = m_value.c_str();
    s.append("\"");
    while(*str != '\0')
    {
        if(*str > 32)
        {
            if(*str == '\\')
                s.append("\\\\");
//            else if(*str == '\/')
//                s.append("\\\/");
            else if(*str == '"')
                s.append("\\\"");
            else
                s.push_back(*str);
        }
        else
        {
            if(*str == '\b')
                s.append("\\b");
            else if(*str == '\f')
                s.append("\\f");
            else if(*str == '\n')
                s.append("\\n");
            else if(*str == '\r')
                s.append("\\r");
            else if(*str == '\t')
                s.append("\\t");
        }
        str++;
    }
    return s;
}

int JsonString::fromString(const char *str, int length)
{
    int i = 1;
    str++;
    m_value.clear();
    while(i < length)
    {
        if(*str != '"')
        {
            if(*str == '\\')
            {
                i++;
                str++;
                if(*str == '\\')
                    m_value.push_back('\\');
                else if(*str == '\"')
                    m_value.push_back('\"');
//                else if(*str == '\/')
//                    m_value.push_back('\/');
                else if(*str == 'b')
                    m_value.push_back('\b');
                else if(*str == 'f')
                    m_value.push_back('\f');
                else if(*str == 'n')
                    m_value.push_back('\n');
                else if(*str == 'r')
                    m_value.push_back('\r');
                else if(*str == 't')
                    m_value.push_back('\t');
            }
            else
                m_value.push_back(*str);
            str++;
            i++;
        }
        else
            break;
    }
    if(*str != '"')
    {
        //throw exception
    }
    return i+1;
}
