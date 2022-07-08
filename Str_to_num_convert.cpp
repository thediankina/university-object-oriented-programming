#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <typeinfo>
#include "StringNumConverter.h"

using namespace std;


StringNumConverter StringNumConverter::operator+(const char* str) {
	string temp = data + str;

	StringNumConverter abc(temp);

	return abc;
}

StringNumConverter StringNumConverter::operator+(StringNumConverter str) {
	string temp = data + str.data;

	StringNumConverter abc(temp);

	return abc;
}

StringNumConverter& StringNumConverter::operator=(const char* str) {
	this->data = str;
	return *this;
}

StringNumConverter& StringNumConverter::operator=(const StringNumConverter str) {
	this->data = str.data;
	return *this;
}

ostream& operator<<(ostream& os, const StringNumConverter& str) {
	os << str.data;
	return os;
}

bool StringNumConverter::operator!=(const StringNumConverter& str) {
	if (this->data == str.data) return false;
	else return true;
}

bool StringNumConverter::operator==(const StringNumConverter& str) {
	if (*this != str) return false;
	else return true;
}

string StringNumConverter::getInt() const {
	string number;
	for (int i = 0; this->data[i] != '.' && i < (int)(this->data).length(); i++) {
		number += this->data[i];
	}
	return number;
}

string StringNumConverter::getFormat(string& number1, string& number2) {	// Подгоняет второе число под размер первого
	int diff = (int)number1.length() - (int)number2.length();
	for (int i = 0; i < diff; i++) {	// 0020
		if (number2[0] == '-') {
			number2[0] = '0';
			for (int i = 0; i < diff - 1; i++) {
				number2 = "0" + number2;
			}
			number2 = "-" + number2;
			return number2;
		}
		number2 = "0" + number2;
	}
	return number2;
}

string StringNumConverter::getFormat2(string& number1, string& number2) {	// number1 is not an object of class
	int diff = stoi(number1) - (int)number2.length();
	for (int i = 0; i < diff; i++) {
		if (number2[0] == '-') {
			number2[0] = '0';
			for (int i = 0; i < diff-1; i++) {
				number2 = "0" + number2;
			}
			number2 = "-" + number2;
			return number2;
		}
		number2 = "0" + number2;
	}
	return number2;
}

string StringNumConverter::getDec() const {
	string number;
	for (int i = 0; this->data[i] != '.' && i < (int)(this->data).length(); i++) {	// 00000200001
		continue;
		if (this->data[i] != '.') for (i; i < (int)(this->data).length(); i++) {
			number += this->data[i];
		}
	}
	return number;
}

bool StringNumConverter::operator<(const StringNumConverter& str) {
	if (*this == str) return false;
	string number1, number2, number12, number22;	// целые части чисел
	number1 = getInt();	//20
	number2 = str.getInt();	//1000
	if (number1[0] == '-' && number2[0] != '-') return true;
	if (number2[0] == '-' && number1[0] != '-') return false;
	if (number2.length() < number1.length()) number2 = getFormat(number1, number2);
	else number1 = getFormat(number2, number1);
	if (number1[0] == '-' && number2[0] == '-') {
		for (int i = 1; i < (int)number1.length(); i++) {	// -002 <> -100
			if (number1[i] == number2[i]) continue;	// Пропускаем все равные, пока не встретим больше
			if (number1[i] > number2[i]) return true;
			else return false;
		}
	}
	else {
		for (int i = 0; i < (int)number1.length(); i++) {	// 0200 <> 1000
			if (number1[i] == number2[i]) continue;	// Пропускаем все равные, пока не встретим меньше
			if (number1[i] < number2[i]) return true;
			else return false;	// Если встретили больше, то сравнение не верно
		}	// Если целые части оказались равными
	}
	number12 = getDec();	// 00000200001
	number22 = str.getDec();
	if (number1[0] == '-' && number2[0] == '-') {
		for (int i = 0; i < (int)number12.length() && i < (int)number22.length(); i++) {
			if (number12[i] == number22[i]) continue;
			if (number12[i] > number22[i]) return true;
			else return false;
		}
	}
	else {
		for (int i = 0; i < (int)number12.length() && i < (int)number22.length(); i++) {
			if (number12[i] == number22[i]) continue;
			if (number12[i] < number22[i]) return true;
			else return false;
		}
	}
	return false;
}

bool StringNumConverter::operator>(const StringNumConverter& str) {
	if (*this == str || *this < str) return false;
	else return true;
}

string StringNumConverter::printSNC(const char* format, StringNumConverter str) {
	int i = 0;
	if (format[0] == '%' && strlen(format) != 1) {
		if (format[1] == 'f') cout << str.data;
		if (format[1] == 'd') {
			while (i < (int)(str.data).length() && str.data[i] != '.') {
				cout << str.data[i];
				i++;
			}
		}
		if ('0' <= format[1] && format[1] <= '9') {
			string before_point, after_point;
			for (i = 0; i < (int)(str.data).length() && str.data[i] != '.'; i++) {
				before_point += str.data[i];
			}
			for (i; i < (int)(str.data).length(); i++) {
				after_point += str.data[i];
			}
			string number;
			int j;
			for (j = 1; format[j] != '.' && j < (int)strlen(format) && ('0' <= format[j] && format[j] <= '9'); j++) {
				number += format[j];
			}
			if (number == "0") cout << "";
			else {
				if (before_point[0] == '-') {
					int tmp = stoi(number) + 1;
					number = to_string(tmp);
				}
				if (format[j] == '.') {
					if ((int)before_point.length() < stoi(number)) {
						before_point = getFormat2(number, before_point);
						cout << before_point;
					}
					else for (int i = 0; i < stoi(number); i++) cout << before_point[i];
					number = "";
					j++;
					for (j; j < (int)strlen(format) && ('0' <= format[j] && format[j] <= '9'); j++) {
						number += format[j];
					}
					if (number == "0") cout << "";
					else {
						if ((int)after_point.length() < stoi(number) + 1) {
							cout << after_point;
							for (int i = 0; i < (stoi(number) + 1 - (int)after_point.length()); i++) {	// 200
								cout << "0";
							}
						}
						else for (int i = 0; i < stoi(number) + 1; i++) cout << after_point[i];
					}
				}
				else {
					if ((int)before_point.length() < stoi(number)) {
						before_point = getFormat2(number, before_point);
						cout << before_point;
					}
					else for (int i = 0; i < stoi(number); i++) cout << before_point[i];
				}
			}
		}
		if (format[1] == '.') {
			if ('0' <= format[2] && format[2] <= '9') {
				string before_point, after_point;
				for (i = 0; i < (int)((str.data).length()) && str.data[i] != '.'; i++) {
					before_point += str.data[i];
				}
				cout << before_point;
				for (i; i < (int)(str.data).length(); i++) {
					after_point += str.data[i];
				}
				string number;
				for (int i = 2; i < (int)strlen(format) && ('0' <= format[i] && format[i] <= '9'); i++) {
					number += format[i];
				}
				if (number == "0") cout << "";
				else {
					if ((int)after_point.length() < stoi(number) + 1) {
						cout << after_point;
						for (int i = 0; i < (stoi(number) + 1 - (int)after_point.length()); i++) {	// 200
							cout << "0";
						}
					}
					else {
						for (int i = 0; i < stoi(number) + 1; i++) cout << after_point[i];
					}
				}
			}
		}
	}
	else cout << "mistake in command printSNC" << endl;
	return str.data;
}

StringNumConverter::StringNumConverter(StringNumConverter& str) {
	this->data = str.data;
}

StringNumConverter::StringNumConverter(const char* sym) : StringNumConverter (string (sym)){
}

// Проверка полученной строки: должны прийти только цифры
StringNumConverter::StringNumConverter(string sym) {
	int checkPoint = 0;
	if (('0' <= sym[0] && sym[0] <= '9') || sym[0] == '-') {	// Проверили первый символ строки
		for (int i = 1; i < (int)sym.length(); i++) {
			if (!('0' <= sym[i] && sym[i] <= '9')) {	// Если встречается не цифра
				if (sym[i] == '.') checkPoint += 1;	// то проверяем, точка ли. Посчитали точку
				else {
					throw invalid_argument(sym+"->"+"not number");
				}
			}
		}
		if (checkPoint != 0 && checkPoint != 1) throw invalid_argument(sym + "->" +"too many points");	// для c и d сначала обрабатывает c, потом d
		else this->data = sym;
	}
	else throw invalid_argument(sym + "->" + "not number");
}

StringNumConverter::StringNumConverter(double num) {
	this->data = to_string(num);
}

StringNumConverter::StringNumConverter(long double num) {
	this->data = to_string(num);
}

StringNumConverter::StringNumConverter(float num) {
	this->data = to_string(num);
}

StringNumConverter::StringNumConverter(int num) {
	this->data = to_string(num);
}

StringNumConverter::StringNumConverter(short num) {
	this->data = to_string(num);
}

StringNumConverter::StringNumConverter(long long num) {
	this->data = to_string(num);
}

StringNumConverter::StringNumConverter(unsigned short num) {
	this->data = to_string(num);
}

StringNumConverter::StringNumConverter(unsigned int num) {
	this->data = to_string(num);
}

StringNumConverter::StringNumConverter(unsigned long long int num) {
	this->data = to_string(num);
}

int main() {
	StringNumConverter b("-12063959085888582858005028580285808509859590");
	StringNumConverter c(1e-1);
	StringNumConverter d(1.2);
	// StringNumConverter f("abc");
	//StringNumConverter e(f);
	if (d != StringNumConverter((float)c + 1.1)) cout << "Something wrong\n";
	else cout << "As expected\n";
	cout << "b + 9: " << b + "9" << endl << "c + 1: " << c + "1" << endl;
	// cout << "c + d: "; cout << c + d << endl;
	StringNumConverter q("-1000.1000001200002");
	StringNumConverter p("-20.00000200001");
	if (q < p)  cout << "As expected\n";
	else cout << "Something wrong\n";
	p.printSNC("%5.20f", p);
}
