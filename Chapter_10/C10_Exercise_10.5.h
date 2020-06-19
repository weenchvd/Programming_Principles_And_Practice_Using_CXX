/* Exercise 10.5 */

using namespace std;

class EndOfFile{};

const int not_a_reading = -7777;	// less than absolute zero
const int not_a_month = -1;

const string indentForMonth = "\t";
const string indentForDay = indentForMonth + "\t";
const string indentForHour = indentForDay + "\t";

vector<string> month_input_tbl = {
	"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"
};

vector<string> month_print_tbl = {
	"January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December"
};

struct Day {
	vector<double> hour{ vector<double>(24, not_a_reading) };
};

struct Month {						// a month of temperature readings
	int month{ not_a_month };		// [0:11] January is 0
	vector<Day> day{ 32 };			// [1:31] one vector of readings per day
};

struct Year {						// a year of temperature readings, organized by month
	int year;						// positive == A.D.
	vector<Month> month{ 12 };		// [0:11] January is 0
};

struct Reading {
	int day;
	int hour;
	double temperature;
};

istream& operator>>(istream& is, Reading& r);
istream& operator>>(istream& is, Month& m);
bool is_valid(const Reading& r);
istream& operator>>(istream& is, Year& y);
int month_to_int(string s);
string int_to_month(int i);
void end_of_loop(istream& ist, char term, const string& message);
void print_year(ofstream& ofs, const Year& y);
void print_month(ofstream& ofs, const Month& m);
void print_day(ofstream& ofs, const Day& d, const int number);
void ClearInput(istream& is);
