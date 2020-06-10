/* Exercise 9.7 */

using namespace std;

namespace Chrono {
	enum class Month {
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Date {
	public:
		class Invalid { }; // to throw as exception
		Date(int y, Month m, int d); // check for valid date and initialize
		Date(); // default constructor
		// the default copy operations are fine
		// nonmodifying operations:
		int day() const { return d; }
		Month month() const { return m; }
		int year() const { return y; }
	private:
		int y;
		Month m;
		int d;
	};

	bool is_date(int y, Month m, int d); // true for valid date
	bool leapyear(int y); // true if y is a leap year
	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);
	ostream& operator<<(ostream& os, const Date& d);
	istream& operator>>(istream& is, Date& dd);
} // Chrono

namespace Library {
	struct Author {
		string name;
		string surname;
		Author()
			: name{}, surname{} { }
		Author(string name, string surname)
			: name{ name }, surname{ surname } { }
	};

	ostream& operator<<(ostream& os, Author a);

	enum class Genre {
		notSpecified, fiction, nonfiction, periodical, biography, children
	};

	const vector<string> genre = { "Not specified", "Fiction", "Nonfiction", "Periodical", "Biography", "Children" };

	class Book {
	public:
		class Invalid {};
		Book()
			: isbn{}, title{}, author{}, genre{ Genre::notSpecified }, copDate{}, isChecked{ false } { }
		Book(string isbn, string title, Author author, Genre genre, Chrono::Date copyrightDate, bool isCheckedOut);
		// nonmodifying operations:
		string GetISBN() const { return isbn; }
		string GetTitle() const { return title; }
		Author GetAuthor() const { return author; }
		Genre GetGenre() const { return genre; }
		Chrono::Date GetDate() const { return copDate; }
		bool IsCheckedOut() const { return isChecked; }
	private:
		string isbn;
		string title;
		Author author;
		Genre genre;
		Chrono::Date copDate;
		bool isChecked;
	};

	bool IsISBN(string isbn);
	bool operator==(const Book& a, const Book& b);
	bool operator!=(const Book& a, const Book& b);
	ostream& operator<<(ostream& os, const Book& b);
}

void Print(const vector<Library::Book>& v);
Library::Book GetBook();
void ClearInputLine(istream& is);
