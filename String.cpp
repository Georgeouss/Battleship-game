#include "stdafx.h"
#include "String.h" 

void String::copy(const String& other)
{
	/*if (!&other)
		return; */
	this->value = new char[strlen(other.value) + 1];
	strcpy(this->value, other.value);
}
void String::copy(const char* other)
{
	this->value = new char[strlen(other) + 1];
	strcpy(this->value, other);
}
void String::erase()
{
	if(this->value != nullptr)
	delete[] this->value;
}
String::String()
{
	this->value = new char[1];
	strcpy(this->value, "");
}
String::String(const String& other)
{
	this->copy(other);
}

String::String(const char* str)
{
	this->copy(str);
}

String&::String::operator = (const String& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}
	return *this; 
}
String&::String::operator = (const char* other)
{
	this->erase();
	this->copy(other);

	return *this;
}
char* String ::operator + (const String& other)
{
	char* temp = new char[this->lenght() + other.lenght() + 1];
	strcpy(temp, this->value);
	return strcat(temp, other.value);
}
String&::String::operator += (const String& other)
{
	int temp = strlen(this->value) + strlen(other.value) + 1;
	char* tempString = new char[temp];
	strcpy(tempString, this->value); 
	strcat(tempString, other.value); 
	return *this = tempString;
}
char String::operator [] (const size_t index)const
{
	return this->value[index];
}
bool String::operator == (const String& other)
{
	return (!(strcmp(this->value, other.value)));
}
size_t String::lenght() const
{
	return strlen(this->value);
}
String::~String()
{
	this->erase();
}

std::ostream &operator << (std::ostream &output,const String& str1)
{
	for (size_t i = 0; i < str1.lenght(); i++)
	{
		output << str1[i]; 
	}
	return output; 
}
std::istream &operator >> (std::istream &input, String& str1)
{
	char temp[256];
	input.getline(temp, 256); 
	str1.value = new char[strlen(temp) + 1];
	strcpy(str1.value, temp);
	return input;
}
