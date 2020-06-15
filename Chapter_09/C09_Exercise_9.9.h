/* Exercise 9.9 */

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

namespace Lib {
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
		// modifying operations:
		void CheckedOut();
	private:
		string isbn;
		string title;
		Author author;
		Genre genre;
		Chrono::Date copDate;
		bool isChecked;
	};

	bool IsISBN(const string isbn);
	bool operator==(const Book& a, const Book& b);
	bool operator!=(const Book& a, const Book& b);
	ostream& operator<<(ostream& os, const Book& b);

	struct Reader {
		string name;
		string surname;
		Reader()
			: name{}, surname{} { }
		Reader(string name, string surname)
			: name{ name }, surname{ surname } { }
	};

	ostream& operator<<(ostream& os, Reader r);

	class Patron {
	public:
		class Invalid{};
		Patron()
			: card{0}, reader{}, fee{0.0} { }
		Patron(long long int card, Reader reader, double fee)
			: card{card}, reader{reader}, fee{fee} { }

		// nonmodifying operations:
		long long int GetCard() const { return card; }
		Reader GetReader() const { return reader; }
		double GetFee() const { return fee; }
		// modifying operations:
		void SetFee(double f) { fee = f; }
	private:
		long long int card;
		Reader reader;
		double fee;
	};

	bool IsDebtor(const Patron& p);
	bool operator==(const Patron& a, const Patron& b);
	bool operator!=(const Patron& a, const Patron& b);

	class Library {
	public:
		struct Transaction {
			Book& book;
			const Patron& patron;
			const Chrono::Date& date;
			Transaction(Book& book, const Patron& patron, const Chrono::Date& date)
				: book{ book }, patron{ patron }, date{ date } { }
		};

		Library()
			: books{}, patrons{}, trans{} { }

		// nonmodifying operations:
		bool IsInLibrary(const Book& book) const;
		bool IsInLibrary(const Patron& patron) const;
		const vector<Book>& GetAllBooks() const { return books; }
		const vector<Patron>& GetAllPatrons() const { return patrons; }
		const vector<Transaction>& GetAllTransactions() const { return trans; }
		// modifying operations:
		void AddBook(const Book book);
		void AddPatron(const Patron patron);
		void AddTransaction(const Transaction tr);
		Book& FindBook(const string& isbn);
		Patron& FindPatron(const long long int card);
	private:
		vector<Book> books;
		vector<Patron> patrons;
		vector<Transaction> trans;
	};

	Library::Transaction CheckOut(Book& book, const Patron& patron, const Chrono::Date& date, const Library& lib);
	vector<Patron>& GetDebtors(const Library& lib, vector<Patron>& debtors);
}

Lib::Book EnterBook();
Lib::Patron EnterPatron();
void Print(const vector<Lib::Book>& v);
void Print(const vector<Lib::Patron>& v);
void Print(const vector<Lib::Library::Transaction>& v);
void ClearInput(istream& is);
