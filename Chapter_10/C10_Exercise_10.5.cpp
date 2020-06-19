/* Exercise 10.5 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<cstdio>
#include"C10_Exercise_10.5.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }
inline int randint(int max) { return rand() % max; }
inline int randint(int min, int max) { return randint(max - min) + min; }


int main()
{
	const string errMessageInputFile = "Error. Can't open input file: ";
	const string errMessageOutputFile = "Error. Can't open output file: ";
	enum Action {
		EXIT = -1, PRINTACTIONLIST, READANDPRINT
	};
	const string actionList = "\tList of actions:\n"
	"  (1) read file and print\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	const string fileName = "raw_temps.txt";
	vector<Reading> tempStats;
	bool cond{ true };
	int action;
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case READANDPRINT: {
			// open an input file:
			cout << "Please enter input file name\n";
			string iname;
			cin >> iname;
			ifstream ifs{ iname };
			if (!ifs) error(errMessageInputFile, iname);
			ifs.exceptions(ifs.exceptions() | ios_base::badbit); // throw for bad()
			// open an output file:
			cout << "Please enter output file name\n";
			string oname;
			cin >> oname;
			ofstream ofs{ oname };
			if (!ofs) error(errMessageOutputFile, oname);
			// read an arbitrary number of years:
			vector<Year> ys;
			while (true) {
				Year y; // get a freshly initialized Year each time around
				if (!(ifs >> y)) break;
				ys.push_back(y);
			}
			cout << "read " << ys.size() << " years of readings\n";
			for (Year& y : ys) print_year(ofs, y);
			break;
		}
		case PRINTACTIONLIST:
			cout << actionList;
			break;
		case EXIT:
			cond = false;
			break;
		default:
			error("Error. Incorrect action number");
			break;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Error. Exception\n";
		return 1;
	}
	return 0;
}

istream& operator>>(istream& is, Reading& r)
// read a temperature reading from is into r
// format: ( 3 4 9.7 )
// check format, but don’t bother with data validity
{
	char ch1;
	if (is >> ch1 && ch1 != '(') { // could it be a Reading?
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}
	char ch2;
	int d;
	int h;
	double t;
	is >> d >> h >> t >> ch2;
	if (!is || ch2 != ')') error("bad reading"); // messed-up reading
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}

istream& operator>>(istream& is, Month& m)
// read a month from is into m
// format: { month feb . . . }
{
	char ch = 0;
	if (is >> ch && ch != '{') {
		is.unget();
		is.clear(ios_base::failbit); // we failed to read a Month
		return is;
	}
	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month") error("bad start of month");
	m.month = month_to_int(mm);
	int duplicates = 0;
	int invalids = 0;
	for (Reading r; is >> r; ) {
		if (is_valid(r)) {
			if (m.day[r.day].hour[r.hour] != not_a_reading) ++duplicates;
			m.day[r.day].hour[r.hour] = r.temperature;
		}
		else ++invalids;
	}
	if (invalids) error("invalid readings in month", invalids);
	if (duplicates) error("duplicate readings in month", duplicates);
	end_of_loop(is, '}', "bad end of month");
	return is;
}

constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

bool is_valid(const Reading& r)
// a rough test
{
	if (r.day < 1 || 31 < r.day) return false;
	if (r.hour < 0 || 23 < r.hour) return false;
	if (r.temperature < implausible_min || implausible_max < r.temperature)
		return false;
	return true;
}

istream& operator>>(istream& is, Year& y)
// read a year from is into y
// format: { year 1972 . . . }
{
	char ch;
	is >> ch;
	if (ch != '{') {
		is.unget();
		is.clear(ios::failbit);
		return is;
	}
	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is || year_marker != "year") error("bad start of year");
	y.year = yy;
	while (true) {
		Month m; // get a clean m each time around
		if (!(is >> m)) break;
		y.month[m.month] = m;
	}
	end_of_loop(is, '}', "bad end of year");
	return is;
}

int month_to_int(string s)
// is s the name of a month? If so return its index [0:11] otherwise –1
{
	for (int i = 0; i < 12; ++i) if (month_input_tbl[i] == s) return i;
	return not_a_month;
}

string int_to_month(int i)
// months [0:11]
{
	if (i < 0 || 12 <= i) error("bad month index");
	return month_print_tbl[i];
}

void end_of_loop(istream& is, char term, const string& message)
{
	if (is.fail()) { // use term as terminator and/or separator
		is.clear();
		char ch;
		if (is >> ch && ch == term) return; // all is fine
		error(message);
	}
}

void print_year(ofstream& ofs, const Year& y)
{
	constexpr int monthsInYear = 12;
	ofs << "Year: " << y.year << '\n';
	for (int i = 0; i < monthsInYear; i++) {
		if (y.month[i].month != not_a_month) print_month(ofs, y.month[i]);
	}
}

void print_month(ofstream& ofs, const Month& m)
{
	constexpr int firstDayInMonth = 1;
	constexpr int daysInMonth = 31;
	constexpr int hoursInDay = 24;
	ofs << indentForMonth << "Month: " << month_print_tbl[m.month] << '\n';
	for (int i = firstDayInMonth; i <= daysInMonth; i++) {
		for (int j = 0; j < hoursInDay; j++) {
			if (m.day[i].hour[j] != not_a_reading) {
				print_day(ofs, m.day[i], i);
				break;
			}
		}
	}
}

void print_day(ofstream& ofs, const Day& d, const int number)
{
	constexpr int hoursInDay = 24;
	ofs << indentForDay << "Day: " << number << '\n';
	for (int i = 0; i < hoursInDay; i++) {
		if (d.hour[i] != not_a_reading) {
			ofs << indentForHour << "h " << i << ", t " << d.hour[i] << " C" << '\n';
		}
	}
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
