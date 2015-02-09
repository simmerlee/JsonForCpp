//JsonValue.h

#ifndef _JSONVALUE_H_
#define _JSONVALUE_H_

#include <string>

class JsonValue{
public:
	JsonValue(){}
	virtual ~JsonValue(){}
	virtual std::string toString()=0;
    virtual int fromString(const char *str, int length)=0;
    //从str指向的缓冲区中读取一个Josn对象，返回读取的str后面的字节数
    //length是指从str后面的那个字符起，剩下的内容的长度
	virtual bool isString()=0;
	virtual bool isJsonObject()=0;
	virtual bool isArray()=0;
	virtual bool isNumber()=0;
	virtual bool isInteger()=0;
	virtual bool isDouble()=0;
    virtual bool isBool()=0;

protected:
    bool inline isBlank(const char c)
    {
        if(c == ' ' || c == '\n' || c =='\r')
            return true;
        return false;
    }
};

#endif//_JSONVALUE_H_
