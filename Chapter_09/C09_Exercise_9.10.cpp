/* Exercise 9.10 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>
#include"C09_Exercise_9.10.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST, LEAPYEAR
	};
	const string actionList = "\tList of actions:\n"
	"  (1) leapyear()\n"
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
		// . . .
	}

	void Date::add_month(int n)
	{
		// . . .
	}

	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leapyear(y + n)) { // beware of leap years!
			m = Month::mar; // use March 1 instead of February 29
			d = 1;
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

	/*Day day_of_week(const Date& d)
	{
		// . . .
	}
	
	Date next_Sunday(const Date& d)
	{
		// ...
	}
	
	Date next_weekday(const Date& d)
	{
		// . . .
	}*/
}// Chrono

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
