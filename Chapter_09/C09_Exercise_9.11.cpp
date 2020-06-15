/* Exercise 9.11 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>
#include"C09_Exercise_9.11.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST, LEAPYEAR, NEXTWORKDAY, WEEKOFYEAR, DAYOFWEEK, DAYOFYEAR
	};
	const string actionList = "\tList of actions:\n"
	"  (1) leapyear(), (2) next_workday(), (3) week_of_year(), (4) day_of_week(), (5) day_of_year()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	bool cond{ true };
	int action{ -2 };
	Chrono::Date today(2020, Chrono::Month::jun, 11);
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) {
			ClearInput(cin);
			error("Incorrect input");
		}
		switch (action) {
		case LEAPYEAR: {
			int year;
			cout << "Please enter a year: ";
			if (!(cin >> year)) { ClearInput(cin); error("Incorrect input"); }
			if (Chrono::leapyear(year)) cout << "  " << year << " is leap year\n";
			else cout << "  " << year << " is not leap year\n";
			break;
		}
		case NEXTWORKDAY: {
			Chrono::Date d;
			cout << "Please enter a date of the form \"(yyyy,mm,dd)\": ";
			if (!(cin >> d)) { ClearInput(cin); error("Incorrect input"); }
			cout << "The next workday: " << Chrono::next_workday(d) << endl;
			break;
		}
		case WEEKOFYEAR: {
			Chrono::Date d;
			cout << "Please enter a date of the form \"(yyyy,mm,dd)\": ";
			if (!(cin >> d)) { ClearInput(cin); error("Incorrect input"); }
			cout << "The date " << d << " is the week of the year #" << Chrono::week_of_year(d) << endl;
			break;
		}
		case DAYOFWEEK: {
			Chrono::Date d;
			cout << "Please enter a date of the form \"(yyyy,mm,dd)\": ";
			if (!(cin >> d)) { ClearInput(cin); error("Incorrect input"); }
			cout << "The date " << d << " is ";
			switch (Chrono::day_of_week(d)) {
			case Chrono::Day::sun:
				cout << "Sunday";
				break;
			case Chrono::Day::mon:
				cout << "Monday";
				break;
			case Chrono::Day::tue:
				cout << "Tuesday";
				break;
			case Chrono::Day::wed:
				cout << "Wednesday";
				break;
			case Chrono::Day::thu:
				cout << "Thursday";
				break;
			case Chrono::Day::fri:
				cout << "Friday";
				break;
			case Chrono::Day::sat:
				cout << "Saturday";
				break;
			}
			cout << endl;
			break;
		}
		case DAYOFYEAR: {
			Chrono::Date d;
			cout << "Please enter a date of the form \"(yyyy,mm,dd)\": ";
			if (!(cin >> d)) { ClearInput(cin); error("Incorrect input"); }
			cout << "The date " << d << " is the day of the year #" << Chrono::day_of_year(d) << endl;
			break;
		}
		case PRINTACTIONLIST:
			cout << actionList;
			break;
		case EXIT:
			cond = false;
			break;
		default:
			error("Incorrect action number");
			break;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	catch (Chrono::Date::Invalid& e) {
		cerr << "Date is invalid\n";
	}
	catch (...) {
		cerr << "exception\n";
		return 1;
	}
}

namespace Chrono {
	Month operator++(Month& m) // prefix increment operator
	{
		m = (m == Month::dec) ? Month::jan : Month(int(m) + 1); // “wrap around”
		return m;
	}

	Day operator++(Day& dw) // prefix increment operator
	{
		dw = (dw == Day::sat) ? Day::sun : Day(int(dw) + 1); // “wrap around”
		return dw;
	}

	// member function definitions:
	Date::Date(int yy, Month mm, int dd)
		: y{ yy }, m{ mm }, d{ dd }
	{
		if (!is_date(yy, mm, dd)) throw Invalid{};
	}

	const Date& default_date()
	{
		static Date dd{ 2001,Month::jan,1 }; // start of 21st century
		return dd;
	}

	Date::Date()
		:y{ default_date().year() },
		m{ default_date().month() },
		d{ default_date().day() }
	{}

	void Date::add_day(int n)
	{
		if (n <= 0) error("The number of days must be greater than 0");
		while (n > 0) {
			int daysInMonth = 31;
			switch (m) {
			case Month::feb:
				daysInMonth = (leapyear(y)) ? 29 : 28;
				break;
			case Month::apr: case Month::jun: case Month::sep: case Month::nov:
				daysInMonth = 30;
				break;
			}
			if (d + n > daysInMonth) {
				int x = daysInMonth - d + 1;
				d = 1;
				++m;
				if (m == Month::jan) {
					y++;
				}
				n -= x;
			}
			else {
				d += n;
				n = 0;
			}	
		}
	}

	void Date::add_month(int n)
	{
		constexpr int monthsInYear = 12;
		if (n <= 0) error("The number of months must be greater than 0");
		if (n / monthsInYear) {
			int nYears = n / monthsInYear;
			y += nYears;
			n -= nYears * monthsInYear;
		}
		while (n > 0) {
			++m;
			n--;
		}
		int daysInMonth = 31;
		switch (m) {
		case Month::feb:
			daysInMonth = (leapyear(y)) ? 29 : 28;
			break;
		case Month::apr: case Month::jun: case Month::sep: case Month::nov:
			daysInMonth = 30;
			break;
		}
		if (d > daysInMonth) d = daysInMonth;
	}

	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leapyear(y + n)) { // beware of leap years!
			d = 28; // use February 28 instead of February 29
		}
		y += n;
	}

	//helper functions :
	bool is_date(int y, Month m, int d)
	{
		// assume that y is valid
		if (d <= 0) return false; // d must be positive
		if (m < Month::jan || Month::dec < m) return false;
		int days_in_month = 31; // most months have 31 days
		switch (m) {
		case Month::feb: // the length of February varies
			days_in_month = (leapyear(y)) ? 29 : 28;
			break;
		case Month::apr: case Month::jun: case Month::sep: case Month::nov:
			days_in_month = 30; // the rest have 30 days
			break;
		}
		if (days_in_month < d) return false;
		return true;
	}

	bool leapyear(int y)
	{
		if (!(y % 400)) return true;
		if (!(y % 100)) return false;
		if (!(y % 4)) return true;
		return false;
	}

	bool operator==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a == b);
	}

	bool operator<(const Date& a, const Date& b)
	{
		if (a.year() < b.year()) return true;
		else if (a.year() > b.year()) return false;
		else {
			if (a.month() < b.month()) return true;
			else if (a.month() > b.month()) return false;
			else {
				if (a.day() < b.day()) return true;
				else return false;
			}
		}
	}

	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.year()
			<< ',' << int(d.month())
			<< ',' << d.day() << ')';
	}

	istream& operator>>(istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') { // oops: format error
			is.clear(ios_base::failbit); // set the fail bit
			return is;
		} dd = Date(y, Month(m), d); // update dd
		return is;
	}

	Date next_workday(const Date& d)
	{
		Day weekDay = day_of_week(d);
		Date nextWorkday{ d };
		if (weekDay == Day::fri) {
			nextWorkday.add_day(3);
			return nextWorkday;
		}
		if (weekDay == Day::sat) {
			nextWorkday.add_day(2);
			return nextWorkday;
		}
		nextWorkday.add_day(1);
		return nextWorkday;
	}

	int week_of_year(const Date& d)
	{
		constexpr int daysInWeek = 7;
		constexpr Day firstDayOfWeek = Day::sun;
		const Date dateJan1(d.year(), Month::jan, 1);
		Day dayJan1 = day_of_week(dateJan1);
		int nDays = day_of_year(d);
		int nWeeks = nDays / daysInWeek;
		int remainder = nDays % daysInWeek;
		if (dayJan1 != firstDayOfWeek) nWeeks++;
		Day day = dayJan1;
		for (int i = 0; i < remainder; i++) {
			if (day == firstDayOfWeek) {
				nWeeks++;
				break;
			}
			++day;
		}
		return nWeeks;
	}

	Day day_of_week(const Date& d)
	{
		constexpr int daysInWeek = 7;
		static const Date startDate(1970, Month::jan, 1); // POSIX time
		static const Day startDay{ Day::thu }; // POSIX time
		if (d < startDate) error("The date must be later than (1970,01,01)");
		int daysFromStart{ 0 };
		for (int y = startDate.year(); y < d.year(); y++) {
			int daysInYear = (leapyear(y)) ? 366 : 365;
			daysFromStart += daysInYear;
		}
		for (Month m = Month::jan; m < d.month(); ++m) {
			int daysInMonth = 31;
			switch (m) {
			case Month::feb:
				daysInMonth = (leapyear(d.year())) ? 29 : 28;
				break;
			case Month::apr: case Month::jun: case Month::sep: case Month::nov:
				daysInMonth = 30;
				break;
			}
			daysFromStart += daysInMonth;
		}
		daysFromStart += d.day();
		daysFromStart %= daysInWeek;
		Day r{ Day::wed };
		for (int i = 0; i < daysFromStart; i++) ++r;
		return r;
	}

	int day_of_year(const Date& d)
	{
		int nDays{ 0 };
		for (Month m = Month::jan; m < d.month(); ++m) {
			int daysInMonth = 31;
			switch (m) {
			case Month::feb:
				daysInMonth = (leapyear(d.year())) ? 29 : 28;
				break;
			case Month::apr: case Month::jun: case Month::sep: case Month::nov:
				daysInMonth = 30;
				break;
			}
			nDays += daysInMonth;
		}
		nDays += d.day();
		return nDays;
	}
	
	/*Date next_Sunday(const Date& d)
	{
		// ...
	}*/
}// Chrono

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
