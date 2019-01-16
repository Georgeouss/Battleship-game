#pragma once

#include "stdafx.h"
#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

#pragma warning(disable : 4996)

class String
{
private:
	char* value;
	void copy(const String& other);
	void copy(const char* other);
	void erase();
public:
	String();
	String(const String& other);
	String(const char* str);
	String& operator = (const String& other);
	String& operator = (const char* other);
	char* operator + (const String& other);
	String& operator += (const String& other);
	char operator [] (const size_t index)const;
	bool operator ==(const String& other);
	size_t lenght()const;
	friend std::ostream &operator << (std::ostream &output, const String& str1);
	friend std::istream &operator >> (std::istream &input, String& str1);

	~String();
};
 