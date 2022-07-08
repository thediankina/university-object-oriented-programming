#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

class StringNumConverter {
public:
	string data;

	StringNumConverter(StringNumConverter&);
	StringNumConverter(const char*);
	StringNumConverter(string);
	StringNumConverter(double);
	StringNumConverter(long double);
	StringNumConverter(float);
	StringNumConverter(int);
	StringNumConverter(unsigned int);
	StringNumConverter(short);
	StringNumConverter(unsigned short);
	StringNumConverter(long long);
	StringNumConverter(unsigned long long int);

	StringNumConverter operator+(const char* str);

	StringNumConverter operator+(StringNumConverter str);

	StringNumConverter& operator=(const char* str);

	StringNumConverter& operator=(const StringNumConverter str);

	explicit operator double() const {
		return stod(data);
	}

	explicit operator long double() const {
		return stold(data);
	}

	explicit operator float() const {
		return stof(data);
	}

	explicit operator int() const {
		return stoi(data);
	}

	explicit operator short int() const {
		return (short)stoi(data);
	}

	explicit operator long int() const {
		return stol(data);
	}

	explicit operator unsigned int() const {
		return stoul(data);
	}

	explicit operator unsigned long long int() const {
		return stoull(data);
	}

	friend ostream& operator<<(ostream& os, const StringNumConverter& str);

	bool operator!=(const StringNumConverter& str);

	bool operator==(const StringNumConverter& str);

	string getInt() const;

	string getFormat(string& number1, string& number2);

	string getFormat2(string& number1, string& number2);

	string getDec() const;

	bool operator<(const StringNumConverter& str);

	bool operator>(const StringNumConverter& str);

	string printSNC(const char*, StringNumConverter);
};

