#include <iostream>

#include "ap_error.h"

enum class Months : unsigned int {January=1, February, March, April, May, June, July, August, September, October, November, December};

std::string month_str(const Months month) {
	switch (month) {
		case Months::January:
			return "January";
		case Months::February:
			return "February";
		case Months::March:
			return "March";
		case Months::April:
			return "April";
		case Months::May:
			return "May";
		case Months::June:
			return "June";
		case Months::July:
			return "July";
		case Months::August:
			return "August";
		case Months::September:
			return "September";
		case Months::October:
			return "October";
		case Months::November:
			return "November";
		case Months::December:
			return "December";
		default:
			AP_ASSERT(false) << "unknown month";
	}

	return "";
}

bool operator<(Months const lhs, Months const rhs) {
	return static_cast<unsigned int>(lhs) < static_cast<unsigned int>(rhs);
}

bool operator>(Months const lhs, Months const rhs) {
	return rhs < lhs;
}

bool operator<=(Months const lhs, Months const rhs) {
	return !(lhs > rhs);
}

bool operator>=(Months const lhs, Months const rhs) {
	return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& os, const Months m) {
	return os << month_str(m);
}

bool is_leap(const unsigned int year) {
	if (year % 400 == 0) {
		return true;
	} else if (year % 100 == 0) {
		return false;
	}
			
	return year % 4 == 0;
}

class Date {
		unsigned int _year;
		Months _month;
		unsigned int _day;
	public:
		Date(const unsigned int year, const Months month, const unsigned int day) : _year(year), _month(month), _day(day) {
			//AP_ERROR_RANGE(month, 1, 12) << "Month must be between 1 and 12";
			AP_ERROR_IN_RANGE(_day, 1, month_days(_month, year)) << "Month " << _month << "'s day in year " << _year << "  must be between 1 and " << month_days(_month, _year);
		}

		unsigned int year() const {
			return _year;
		}

		Months month() const {
			return _month;
		}
	
		unsigned int day() const {
			return _day;
		}

		void add_days(const unsigned int n);

		static unsigned int month_days(const Months month, const unsigned int year);
};

void Date::add_days(const unsigned int n) {
	unsigned int remain{n};

	while (remain) {
		unsigned int to_end{Date::month_days(_month, _year) - _day};
		if (remain <= to_end) {
			_day += remain;
			remain = 0;
		} else {
			_day = 1;
			if (_month == Months::December) {
				_month = Months::January;
				_year++;
			} else {
				_month = static_cast<Months>(static_cast<unsigned int>(_month) + 1);
			}

			remain -= to_end + 1;
		}
	}
};


unsigned int Date::month_days(const Months month, const unsigned int year) {
	switch (month) {
		case Months::February:
			return 28 + is_leap(year);
		case Months::April:
		case Months::June:
		case Months::September:
		case Months::November:
			return 30;
		case Months::January:
		case Months::March:
		case Months::May:
		case Months::July:
		case Months::August:
		case Months::October:
		case Months::December:
		default:
			return 31;
	}
	
	exit(1);
	return 0;
};

bool operator==(const Date& lhs, const Date& rhs) {
	return lhs.year() == rhs.year() && lhs.month() == rhs.month() && lhs.day() == rhs.day();
}
		
bool operator!=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.year() < rhs.year()) {
		return true;
	} else if (lhs.year() == rhs.year()) {
		if (lhs.month() < rhs.month()) {
			return true;
		} else if (lhs.month() == rhs.month()) {
			return lhs.day() < rhs.day();
		}
	}
	return false;
}

bool operator>(const Date& lhs, const Date& rhs) {
	return rhs < lhs;
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return !(lhs > rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
	return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
	return os << d.day() << " " << d.month() << " " << d.year();
}

void test_leap_add(const unsigned int year) {
	Date d{year, Months::February, 24};
	std::cout << "starting at " << d;
	d.add_days(5);
	std::cout << "; 5 days later: " << d << "\n";
}

int main(int argc, char** argv) {
	std::cout << "Feb < Jan: " << (Months::February < Months::January) << std::endl;

	Date d{1989, Months::February, 24};
	std::cout << "bday: " << d << "\n";
	
	test_leap_add(1992);
	test_leap_add(2000);
	test_leap_add(2100);

	Date d2{1999, Months::December, 30};
	std::cout << d2 << " + 2 days = ";
	d2.add_days(2);
	std::cout << d2 << std::endl;

	std::cout << "d{" << d << "} < d2{" << d2 << "}: " << (d < d2) << std::endl;
	std::cout << "d{" << d << "} > d2{" << d2 << "}: " << (d > d2) << std::endl;
	std::cout << "d{" << d << "} == d2{" << d2 << "}: " << (d == d2) << std::endl;

	Date dError(2001, Months::February, 29);
}

