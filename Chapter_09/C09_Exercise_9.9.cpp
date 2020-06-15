/* Exercise 9.9 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>
#include"C09_Exercise_9.9.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }


int main()
{
	enum Action {
		EXIT = -1, PRINTPROMPT, ADDBOOK, ADDPATRON, CHECKOUT, SETFEE, PAYFEE, PRINTDEBTORS, PRINTLIBRARY
	};
	const string prompt = "\tList of actions:\n"
	"  (1) Add a book, (2) Add a patron, (3) Check out a book, (4) Set the fee, (5) Pay the fee\n"
	"  (6) Print out all of debtors, (7) Print out the library\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << prompt;
	Lib::Library lib;
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
		case ADDBOOK:
			lib.AddBook(EnterBook());
			break;
		case ADDPATRON:
			lib.AddPatron(EnterPatron());
			break;
		case CHECKOUT: {
			string isbn;
			cout << "Please enter the isbn for the book:\n";
			cin >> isbn;
			Lib::Book& book = lib.FindBook(isbn);
			long long int card;
			cout << "Please enter the card of the reader:\n";
			if (!(cin >> card)) {
				ClearInput(cin);
				error("Incorrect input");
			}
			Lib::Patron& patron = lib.FindPatron(card);
			lib.AddTransaction(Lib::CheckOut(book, patron, today, lib));
			break;
		}
		case SETFEE: {
			long long int card;
			cout << "Please enter the card of the reader:\n";
			if (!(cin >> card)) {
				ClearInput(cin);
				error("Incorrect input");
			}
			Lib::Patron& patron = lib.FindPatron(card);
			double fee;
			cout << "Please enter the fee:\n";
			if (!(cin >> fee)) {
				ClearInput(cin);
				error("Incorrect input");
			}
			patron.SetFee(fee);
			break;
		}
		case PAYFEE: {
			long long int card;
			cout << "Please enter the card of the reader:\n";
			if (!(cin >> card)) {
				ClearInput(cin);
				error("Incorrect input");
			}
			Lib::Patron& patron = lib.FindPatron(card);
			patron.SetFee(0.0);
			break;
		}
		case PRINTDEBTORS: {
			vector<Lib::Patron> debtors;
			Lib::GetDebtors(lib, debtors);
			cout << "List of debtors:\n";
			Print(debtors);
			break;
		}
		case PRINTLIBRARY:
			Print(lib.GetAllBooks());
			Print(lib.GetAllPatrons());
			Print(lib.GetAllTransactions());
			break;
		case PRINTPROMPT:
			cout << prompt;
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
	catch (Lib::Book::Invalid& e) {
		cerr << "Book is invalid\n";
	}
	catch (Lib::Patron::Invalid& e) {
		cerr << "Patron is invalid\n";
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

namespace Lib {
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

	void Book::CheckedOut()
	{
		isChecked = true;
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
		os << "  Genre:  " << Lib::genre[int(b.GetGenre())] << endl;
		return os;
	}

	ostream& operator<<(ostream& os, Reader r)
	{
		os << r.name << " " << r.surname;
		return os;
	}

	bool IsDebtor(const Patron& p)
	{
		if (p.GetFee() > 0.0) return true;
		return false;
	}

	bool operator==(const Patron& a, const Patron& b)
	{
		if (a.GetCard() == b.GetCard()) return true;
		return false;
	}

	bool operator!=(const Patron& a, const Patron& b)
	{
		return !(a == b);
	}

	bool Library::IsInLibrary(const Book& book) const
	{
		for (int i = 0; i < books.size(); i++) {
			if (book == books[i]) return true;
		}
		return false;
	}

	bool Library::IsInLibrary(const Patron& patron) const
	{
		for (int i = 0; i < patrons.size(); i++) {
			if (patron == patrons[i]) return true;
		}
		return false;
	}

	void Library::AddBook(const Book book)
	{
		bool bookInLibrary{ false };
		for (int i = 0; i < books.size(); i++) {
			if (book == books[i]) bookInLibrary = true;
		}
		if (bookInLibrary == false) books.push_back(book);
	}

	void Library::AddPatron(const Patron patron)
	{
		bool patronInLibrary{ false };
		for (int i = 0; i < patrons.size(); i++) {
			if (patron == patrons[i]) patronInLibrary = true;
		}
		if (patronInLibrary == false) patrons.push_back(patron);
	}

	void Library::AddTransaction(const Library::Transaction tr)
	{
		trans.push_back(tr);
		tr.book.CheckedOut();
	}

	Book& Library::FindBook(const string& isbn)
	{
		for (int i = 0; i < books.size(); i++) {
			if (books[i].GetISBN() == isbn) return books[i];
		}
		error("Book is not found");
	}

	Patron& Library::FindPatron(const long long int card)
	{
		for (int i = 0; i < patrons.size(); i++) {
			if (patrons[i].GetCard() == card) return patrons[i];
		}
		error("Patron is not found");
	}

	Library::Transaction CheckOut(Book& book, const Patron& patron, const Chrono::Date& date, const Library& lib)
	{
		if (!lib.IsInLibrary(book)) error("The book is not in the library");
		if (book.IsCheckedOut()) error("The book has already been checked out");
		if (!lib.IsInLibrary(patron)) error("The reader is not registered in the library");
		if (IsDebtor(patron)) error("The reader is a debtor");
		return Library::Transaction(book, patron, date);
	}

	vector<Patron>& GetDebtors(const Library& lib, vector<Patron>& debtors)
	{
		const vector<Patron>& patrons = lib.GetAllPatrons();
		for (int i = 0; i < patrons.size(); i++) {
			if (IsDebtor(patrons[i])) debtors.push_back(patrons[i]);
		}
		return debtors;
	}
}// Library

Lib::Book EnterBook()
{
	char ch;
	string isbn;
	cout << "Please enter the ISBN for the book:\n";
	cin >> isbn;
	cin.get(ch);
	string title;
	cout << "Please enter the title for the book:\n";
	getline(cin, title);
	Lib::Author a;
	cout << "Please enter the author's name and surname for the book:\n";
	cin >> a.name >> a.surname;
	int temp = 0;
	cout << "Please enter the genre for the book:\n";
	for (int i = 0; i < Lib::genre.size(); i++) {
		cout << i << " == " << Lib::genre[i];
		if (i < Lib::genre.size() - 1) {
			cout << ", ";
		}
	}
	cout << endl;
	cin >> temp;
	if (!cin) {
		ClearInput(cin);
		throw Lib::Book::Invalid{};
	}
	Lib::Genre genre = { Lib::Genre::notSpecified };
	switch (temp) {
		case int(Lib::Genre::notSpecified) :
			genre = { Lib::Genre::notSpecified };
			break;
		case int(Lib::Genre::fiction) :
			genre = { Lib::Genre::fiction };
			break;
		case int(Lib::Genre::nonfiction) :
			genre = { Lib::Genre::nonfiction };
			break;
		case int(Lib::Genre::periodical) :
			genre = { Lib::Genre::periodical };
			break;
		case int(Lib::Genre::biography):
			genre = { Lib::Genre::biography };
			break;
		case int(Lib::Genre::children) :
			genre = { Lib::Genre::children };
			break;
		default:
			throw Lib::Book::Invalid{};
	}
	Chrono::Date copDate;
	cout << "Please enter the copyright date of the form \"(yyyy,mm,dd)\" for the book:\n";
	cin >> copDate;
	bool isCheckedOut = { false };
	cout << "Is the book issued? Please enter \"1\" for true and \"0\" for false:\n";
	cin >> isCheckedOut;
	if (!cin) { 
		ClearInput(cin);
		throw Lib::Book::Invalid{};
	}
	return Lib::Book(isbn, title, a, genre, copDate, isCheckedOut);
}

Lib::Patron EnterPatron()
{
	long long int card;
	cout << "Please enter the card number for the patron:\n";
	cin >> card;
	if (!cin) {
		ClearInput(cin);
		throw Lib::Patron::Invalid{};
	}
	Lib::Reader reader;
	cout << "Please enter the reader's name and surname for the patron:\n";
	cin >> reader.name >> reader.surname;
	double fee;
	cout << "Please enter the fee for the patron:\n";
	cin >> fee;
	if (!cin) {
		ClearInput(cin);
		throw Lib::Patron::Invalid{};
	}
	return Lib::Patron(card, reader, fee);
}

void Print(const vector<Lib::Book>& v)
{
	if (v.size() == 0) return;
	cout << "# | ISBN | Date | Checked out? | Genre | Author | Title" << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << i + 1 << " | ";
		cout << v[i].GetISBN() << " | ";
		cout << v[i].GetDate() << " | ";
		cout << ((v[i].IsCheckedOut()) ? "YES" : "NO") << " | ";
		cout << Lib::genre[int(v[i].GetGenre())] << " | ";
		cout << v[i].GetAuthor() << " | ";
		cout << v[i].GetTitle() << endl;
	}
	cout << endl;
}

void Print(const vector<Lib::Patron>& v)
{
	if (v.size() == 0) return;
	cout << "# | Card Number | Reader | Fee | Owed?" << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << i + 1 << " | ";
		cout << v[i].GetCard() << " | ";
		cout << v[i].GetReader() << " | ";
		cout << v[i].GetFee() << " | ";
		cout << ((Lib::IsDebtor(v[i])) ? "YES" : "NO") << endl;
	}
	cout << endl;
}

void Print(const vector<Lib::Library::Transaction>& v)
{
	if (v.size() == 0) return;
	cout << "# | Book (isbn) | Patron (card) | Date (yyyy,mm,dd)" << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << i + 1 << " | ";
		cout << v[i].book.GetISBN() << " | ";
		cout << v[i].patron.GetCard() << " | ";
		cout << v[i].date << endl;
	}
	cout << endl;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
