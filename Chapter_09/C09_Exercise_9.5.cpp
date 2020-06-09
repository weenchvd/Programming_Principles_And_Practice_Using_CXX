/* Exercise 9.5 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>
#include"C09_Exercise_9.5.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }


int main()
{
	vector<Library::Book> lib;
	int number = { 0 };
	while (number < 1) {
		cout << "Please enter the number of books to add: ";
		cin >> number;
	}
	for (int i = 1; i <= number; i++) try {
		cout << "Book #" << i << endl;
		lib.push_back(GetBook());
		cout << endl;
	}
	catch (Chrono::Date::Invalid& e) {
		cerr << "Date is invalid\n";
		continue;
	}
	catch (Library::Book::Invalid& e) {
		cerr << "Book is invalid\n";
		continue;
	}
	catch (...) {
		cerr << "exception\n";
		return 1;
	}
	Print(lib);
	keep_window_open();
	return 0;
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
		// see exercise 10
		return true;
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
}// Chrono

namespace Library {
	Book::Book(string isbn, string title, Author author, Chrono::Date copyrightDate, bool isCheckedOut)
		: isbn{ isbn }, title{ title }, author{ author }, copDate{ copyrightDate }, isChecked{ isCheckedOut }
	{
		if (!IsISBN(isbn)) throw Invalid{};
	}

	bool IsISBN(string s)
	{
		istringstream iss;
		iss.str(s);
		int n1, n2, n3;
		char ch1, ch2, ch3, ch4;
		iss >> n1 >> ch1 >> n2 >> ch2 >> n3 >> ch3 >> ch4;
		if (!iss) return false;
		if (ch1 != '-' || ch2 != '-' || ch3 != '-') return false;
		if (!(isdigit(ch4) || isalpha(ch4))) return false;
		return true;
	}
}// Library

Library::Book GetBook()
{
	char ch;
	string isbn;
	cout << "Please enter the ISBN for the book:\n";
	cin >> isbn;
	cin.get(ch);
	string title;
	cout << "Please enter the title for the book:\n";
	getline(cin, title);
	Library::Author a;
	cout << "Please enter the author's name and surname for the book:\n";
	cin >> a.name >> a.surname;
	Chrono::Date copDate;
	cout << "Please enter the copyright date of the form \"(yyyy,mm,dd)\" for the book:\n";
	cin >> copDate;
	bool isCheckedOut = { false };
	cout << "Is the book issued? Please enter \"1\" for true and \"0\" for false:\n";
	cin >> isCheckedOut;
	if (!cin) throw Library::Book::Invalid{};
	return Library::Book(isbn, title, a, copDate, isCheckedOut);
}

void Print(const vector<Library::Book>& v)
{
	if (v.size() == 0) {
		return;
	}
	cout << "# | ISBN | Date | Checked out? | Author | Title" << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << i + 1 << " | ";
		cout << v[i].GetISBN() << " | ";
		cout << v[i].GetDate() << " | ";
		cout << ((v[i].IsCheckedOut()) ? "YES" : "NO") << " | ";
		cout << v[i].GetAuthor().name << ' ' << v[i].GetAuthor().surname << " | ";
		cout << v[i].GetTitle() << endl;
	}
	cout << endl;
}
