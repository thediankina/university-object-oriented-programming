#include <iostream>

using namespace std;

class Date
{
public:
	// Дата по умолчанию
	static const int default_day = 0;
	static const int default_month = 0;
	static const int default_year = 0;

	static const int jan = 1;
	static const int feb = 2;
	static const int mar = 3;
	static const int apr = 4;
	static const int may = 5;
	static const int jun = 6;
	static const int jul = 7;
	static const int aug = 8;
	static const int sep = 9;
	static const int oct = 10;
	static const int nov = 11;
	static const int dec = 12;

	// Номера месяцев, у которых по 31 дню
	const int extendedMonths[7] = { 1, 3, 5, 7, 8, 10, 12 };

	int current_day, current_month, current_year;
	int days = 0;

	Date();
	Date(int year);
	Date(int year, int month);
	Date(int year, int month, int day);
	~Date();
	Date(const Date&);

	bool leapYear() {
		if (current_year % 4 == 0) {
			if (!(current_year % 100 == 0)) {
				if (current_year % 400 == 0) {
					return true;
				}
			}
		}
		return false;
	}

	int countDays() {
		if (count(extendedMonths, extendedMonths + 7, this->current_month) == 1) {
			days = 31;
		}
		else {
			if (this->current_day == feb) {
				if (leapYear()) {
					days = 29;
				}
				else {
					days = 28;
				}
			}
			else {
				days = 30;
			}
		}
		return days;
	}
	void changeDay(int n, bool sign) {
		if (sign) {
			current_day += n;
			days = countDays();
			while (current_day > days) {
				current_day -= days;
				changeMonth(1, sign);
				days = countDays();
			}
		}
		else {
			current_day -= n;
			days = countDays();
			while (current_day < 1) {
				current_day += days;
				changeMonth(1, sign);
				days = countDays();
			}
		}
	};
	void changeMonth(int n, bool sign) {
		if (sign) {
			current_month += n;
			if (current_month > 12) {
				current_month -= 12;
				changeYear(1, sign);
			}
		}
		else {
			current_month -= n;
			if (current_month < 1) {
				current_month += 12;
				changeYear(1, sign);
			}
		}
	};
	void changeYear(int n, bool sign) {
		if (sign) { current_year += n; }
		else { current_year -= n; }
	};


	Date& operator=(Date& date)
	{
		if (&date == this) return *this;	// Проверка на самоприсваивание
		current_day = date.current_day;
		current_month = date.current_month;
		current_year = date.current_year;

		return *this;	// Возвращение текущего объекта
	};

	Date& operator+=(int n)
	{
		changeDay(n, true);
		return *this;
	};

	Date& operator-=(int n)
	{
		changeDay(n, false);
		return *this;
	};

	Date operator+(int n)
	{
		Date copy(*this);
		copy.changeDay(n, true);
		return copy;
	};

	Date operator-(int n)
	{
		Date copy(*this);
		copy.changeDay(n, false);
		return copy;
	};

	bool operator==(const Date& right)
	{
		return (this->current_day == right.current_day &&
			this->current_month == right.current_month &&
			this->current_year == right.current_year);
	};

	bool operator!=(const Date& right)
	{
		if (*this == right) return false;
		else return true;
	};

	bool operator>(const Date& right)
	{
		if (this->current_year > right.current_year) {
			return true;
		}
		else {
			if (this->current_year == right.current_year &&
				this->current_month > right.current_month) return true;
			else {
				if (this->current_year == right.current_year &&
					this->current_month == right.current_month &&
					this->current_day > right.current_day) return true;
			}
		}
		return false;
	};

	bool operator<(const Date& right)
	{
		if (*this > right) return false;
		else return true;
	};

	Date& operator++()		// Префиксный
	{
		changeDay(1, true);
		return *this;
	};

	Date operator++(int)	// Постфиксный
	{
		Date copy(*this);
		++(*this);
		return copy;
	};

	Date& operator--()
	{
		changeDay(1, false);
		return *this;
	};

	Date operator--(int)
	{
		Date copy(*this);
		--(*this);
		return copy;
	};

	const Date getDay() {
		cout << "Enter day: ";
		cin >> this->current_day;
		while (this->current_day < 1 || this->current_day > 31) {
			cout << "Invalid value, try again" << endl << "Enter day: ";
			cin >> this->current_day;
		}
		return *this;
	};

	const Date getMonth() {
		cout << "Enter month: ";
		cin >> this->current_month;
		while (this->current_month < 1 || this->current_month > 12) {
			cout << "Invalid value, try again" << endl << "Enter month: ";
			cin >> this->current_month;
		}
		if (count(extendedMonths, extendedMonths + 7, this->current_month) != 1 &&
			this->current_day == 31 || this->current_month == feb) {
			if (this->current_month == feb && this->current_day > 28) {
				cout << "This date in that month doesn't exist, try again" << endl;
				getDay();
				getMonth();
			}
			while (this->current_day < 1 || this->current_day > 30) {
				cout << "This date in that month doesn't exist, try again" << endl;
				getDay();
				getMonth();
			}
		}
		return *this;
	};

	const Date getYear() {
		cout << "Enter year: ";
		cin >> this->current_year;
		while (this->current_year < 1) {
			cout << "Invalid value, try again" << endl << "Enter year: ";
			cin >> this->current_year;
		}
		return *this;
	};

	friend ostream& operator<<(ostream& out, const Date& date)
	{
		out << date.current_day << "." << date.current_month << "." << date.current_year;

		return out;
	};

	friend istream& operator>>(istream& in, Date& date)
	{
		date.getDay();
		date.getMonth();
		date.getYear();

		return in;
	};
};

// Конструктор по умолчанию
Date::Date()
{
	this->current_day = default_day;
	this->current_month = default_month;
	this->current_year = default_year;
}
// Конструктор по году
Date::Date(int year)
{
	this->current_day = default_day;
	this->current_month = default_month;
	this->current_year = year;
}
// Конструктор по году и месяцу
Date::Date(int year, int month)
{
	this->current_day = default_day;
	this->current_year = year;
	this->current_month = month;
}
// Конструктор по полной дате
Date::Date(int year, int month, int day)
{
	this->current_year = year;
	this->current_month = month;
	this->current_day = day;
}
// Конструктор копий
Date::Date(const Date& date)
{
	current_year = date.current_year;
	current_month = date.current_month;
	current_day = date.current_day;
}
// Деструктор
Date::~Date()
{

}

int main()
{
	Date date1, date2(1995), date3(1995, Date::mar, 15), date4(1995, Date::may, 14);
	if (date4 > date3) cout << "As expected" << endl;
	else cout << "Something wrong" << endl;
	cout << "Default: " << date1 << endl << "Enter default number: " << endl;
	cin >> date1;
	cout << "date1: " << date1 << endl;
	Date today = Date(1600, Date::dec, 31);
	today += 366;
	cout << "Today: " << today << endl;
	Date now = Date(2018, Date::jan, 1);
	now -= 1;
	cout << "now: " << now << endl;
	Date yesterday = now - 1;
	cout << "Yesterday: " << yesterday << endl;
	cout << "now: " << now << endl;
	Date tomorrow = now + 1;
	cout << "Tomorrow: " << tomorrow << endl;
	cout << "now: " << now << endl;
	now++;
	cout << "now: " << now << endl;
	--now;
	now--;
	cout << "now: " << now << endl;
	now++; // ++now; // ++now;
	cout << "now: " << now << endl;
	if (now < tomorrow) cout << "As expected" << endl;
	else cout << "Something wrong" << endl;

	Date test = now + 4 - 2;
	cout << "test: " << test << endl;

	return 0;
}