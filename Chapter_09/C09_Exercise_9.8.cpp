/* Exercise 9.8 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>
#include"C09_Exercise_9.8.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }


int main()
{
	const int exit = { -1 };
	vector<Library::Book> lib;
	int number = { 0 };
	while (number < 1) try {
		cout << "Please enter the number of books to add: ";
		cin >> number;
		if (!cin) {
			ClearInputLine(cin);
			error("Incorrect input");
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	for (int i = 1; i <= number; i++) try {
		cout << "Book #" << i << endl;
		lib.push_back(GetBook());
		cout << endl;
	}
	catch (Chrono::Date::Invalid& e) {
		cerr << "Date is invalid\n";
		i--;
	}
	catch (Library::Book::Invalid& e) {
		cerr << "Book is invalid\n";
		i--;
	}
	catch (...) {
		cerr << "exception\n";
		return 1;
	}
	Print(lib);
	bool cond = { true };
	int book1 = { 0 };
	while (cond) try {
		cout << "Please enter the book number to print out (enter " << exit << " to exit): ";
		cin >> book1;
		if (!cin) {
			ClearInputLine(cin);
			error("Incorrect input");
		}
		if (book1 == exit) {
			cond = { false };
			continue;
		}
		if (book1 > lib.size() || book1 < 1) error("Incorrect number");
		cout << lib[book1 - 1];
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	cond = { true };
	int book2 = { 0 };
	while (cond) try {
		cout << "Please enter the number of book #1 to compare (enter " << exit << " to exit): ";
		cin >> book1;
		if (!cin) {
			ClearInputLine(cin);
			error("Incorrect input");
		}
		if (book1 == exit) {
			cond = { false };
			continue;
		}
		cout << "Please enter the number of book #2 to compare: ";
		cin >> book2;
		if (!cin) {
			ClearInputLine(cin);
			error("Incorrect input");
		}
		if (book1 > lib.size() || book1 < 1 || book2 > lib.size() || book2 < 1) error("Incorrect number");
		if (lib[book1 - 1] == lib[book2 - 1]) {
			cout << "  The books are identical: " << lib[book1 - 1].GetISBN() << " == " << lib[book2 - 1].GetISBN() << endl;
		}
		else {
			cout << "  The books are not identical: " << lib[book1 - 1].GetISBN() << " != " << lib[book2 - 1].GetISBN() << endl;
		}
		if (lib[book1 - 1] != lib[book2 - 1]) {
			cout << "  The books are not identical: " << lib[book1 - 1].GetISBN() << " != " << lib[book2 - 1].GetISBN() << endl;
		}
		else {
			cout << "  The books are identical: " << lib[book1 - 1].GetISBN() << " == " << lib[book2 - 1].GetISBN() << endl;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}

	vector<Library::Patron> pat;
	number = { 0 };
	while (number < 1) {
		cout << "Please enter the number of patrons to add: ";
		cin >> number;
		if (!cin) {
			ClearInputLine(cin);
			error("Incorrect input");
		}
	}
	for (int i = 1; i <= number; i++) try {
		cout << "Patron #" << i << endl;
		pat.push_back(GetPatron());
		cout << endl;
	}
	catch (Library::Patron::Invalid& e) {
		cerr << "Patron is invalid\n";
		i--;
	}
	catch (...) {
		cerr << "exception\n";
		return 1;
	}
	Print(pat);
	cond = { true };
	int patron = { 0 };
	while (cond) try {
		cout << "Please enter the patron number to set the fee (enter " << exit << " to exit): ";
		cin >> patron;
		if (!cin) {
			ClearInputLine(cin);
			error("Incorrect input");
		}
		if (patron == exit) {
			cond = { false };
			continue;
		}
		if (patron > pat.size() || patron < 1) error("Incorrect number");
		double fee;
		cout << "Please enter the fee for the patron: ";
		cin >> fee;
		if (!cin) {
			ClearInputLine(cin);
			error("Incorrect input");
		}
		pat[patron - 1].SetFee(fee);
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	Print(pat);
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
	ostream& operator<<(ostream& os, Author a)
	{
		os << a.name << " " << a.surname;
		return os;
	}

	Book::Book(string isbn, string title, Author author, Genre genre, Chrono::Date copyrightDate, bool isCheckedOut)
		: isbn{ isbn }, title{ title }, author{ author }, genre{ genre }, copDate{ copyrightDate }, isChecked{ isCheckedOut }
	{
		if (!IsISBN(isbn)) throw Invalid{};
	}

	bool IsISBN(const string s)
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
	
	bool operator==(const Book& a, const Book& b)
	{
		if (a.GetISBN() == b.GetISBN()) return true;
		return false;
	}

	bool operator!=(const Book& a, const Book& b)
	{
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Book& b)
	{
		os << "  ISBN:   " << b.GetISBN() << endl;
		os << "  Title:  " << b.GetTitle() << endl;
		os << "  Author: " << b.GetAuthor() << endl;
		os << "  Genre:  " << Library::genre[int(b.GetGenre())] << endl;
		return os;
	}

	ostream& operator<<(ostream& os, Reader r)
	{
		os << r.name << " " << r.surname;
		return os;
	}

	bool IsFee(const Patron& p)
	{
		if (p.GetFee() > 0.0) return true;
		return false;
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
	int temp = 0;
	cout << "Please enter the genre for the book:\n";
	for (int i = 0; i < Library::genre.size(); i++) {
		cout << i << " == " << Library::genre[i];
		if (i < Library::genre.size() - 1) {
			cout << ", ";
		}
	}
	cout << endl;
	cin >> temp;
	if (!cin) {
		ClearInputLine(cin);
		throw Library::Book::Invalid{};
	}
	Library::Genre genre = { Library::Genre::notSpecified };
	switch (temp) {
		case int(Library::Genre::notSpecified) :
			genre = { Library::Genre::notSpecified };
			break;
		case int(Library::Genre::fiction) :
			genre = { Library::Genre::fiction };
			break;
		case int(Library::Genre::nonfiction) :
			genre = { Library::Genre::nonfiction };
			break;
		case int(Library::Genre::periodical) :
			genre = { Library::Genre::periodical };
			break;
		case int(Library::Genre::biography):
			genre = { Library::Genre::biography };
			break;
		case int(Library::Genre::children) :
			genre = { Library::Genre::children };
			break;
		default:
			throw Library::Book::Invalid{};
	}
	Chrono::Date copDate;
	cout << "Please enter the copyright date of the form \"(yyyy,mm,dd)\" for the book:\n";
	cin >> copDate;
	bool isCheckedOut = { false };
	cout << "Is the book issued? Please enter \"1\" for true and \"0\" for false:\n";
	cin >> isCheckedOut;
	if (!cin) { 
		ClearInputLine(cin);
		throw Library::Book::Invalid{};
	}
	return Library::Book(isbn, title, a, genre, copDate, isCheckedOut);
}

Library::Patron GetPatron()
{
	long long int card;
	cout << "Please enter the card number for the patron:\n";
	cin >> card;
	if (!cin) {
		ClearInputLine(cin);
		throw Library::Patron::Invalid{};
	}
	Library::Reader reader;
	cout << "Please enter the reader's name and surname for the patron:\n";
	cin >> reader.name >> reader.surname;
	double fee;
	cout << "Please enter the fee for the patron:\n";
	cin >> fee;
	if (!cin) {
		ClearInputLine(cin);
		throw Library::Patron::Invalid{};
	}
	return Library::Patron(card, reader, fee);
}

void Print(const vector<Library::Book>& v)
{
	if (v.size() == 0) return;
	cout << "# | ISBN | Date | Checked out? | Genre | Author | Title" << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << i + 1 << " | ";
		cout << v[i].GetISBN() << " | ";
		cout << v[i].GetDate() << " | ";
		cout << ((v[i].IsCheckedOut()) ? "YES" : "NO") << " | ";
		cout << Library::genre[int(v[i].GetGenre())] << " | ";
		cout << v[i].GetAuthor() << " | ";
		cout << v[i].GetTitle() << endl;
	}
	cout << endl;
}

void Print(const vector<Library::Patron>& v)
{
	if (v.size() == 0) return;
	cout << "# | Card Number | Reader | Fee | Owed?" << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << i + 1 << " | ";
		cout << v[i].GetCard() << " | ";
		cout << v[i].GetReader() << " | ";
		cout << v[i].GetFee() << " | ";
		cout << ((Library::IsFee(v[i])) ? "YES" : "NO") << endl;
	}
	cout << endl;
}

void ClearInputLine(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
