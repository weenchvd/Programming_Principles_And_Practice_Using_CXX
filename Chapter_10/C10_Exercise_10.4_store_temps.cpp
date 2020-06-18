/* Exercise 10.4 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<cstdio>
#include"C10_Exercise_10.4_store_temps.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }
inline int randint(int max) { return rand() % max; }
inline int randint(int min, int max) { return randint(max - min) + min; }


int main()
{
	constexpr int counter = 24 * 5;
	const string errMessageInputFile = "Error. Can't open input file: ";
	const string errMessageOutputFile = "Error. Can't open output file: ";
	enum Action {
		EXIT = -1, PRINTACTIONLIST, CREATEFILE, PRINTFILE
	};
	const string actionList = "\tList of actions:\n"
	"  (1) create file \"raw_temps.txt\", (2) print file \"raw_temps.txt\"\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	const string fileName = "raw_temps.txt";
	bool cond{ true };
	int action;
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case CREATEFILE: {
			ofstream ofs { fileName };
			if (!ofs) error(errMessageOutputFile, fileName);
			int seed;
			cout << "  Please enter a number: ";
			if (!(cin >> seed)) { ClearInput(cin); error("Error. Incorrect input"); }
			srand(seed);
			WriteRandomReadings(ofs, counter);
			break;
		}
		case PRINTFILE: {
			ifstream ifs{ fileName };
			if (!ifs) error(errMessageInputFile, fileName);
			while (true) try {
				cout << ReadReadingsFromFile(ifs) << endl;
			}
			catch (EndOfFile& e) {
				break;
			}
			cout << endl;
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

ostream& operator<<(ostream& os, const Reading& r)
{
	os << r.hour << ' ' << r.tempCelsius;
	return os;
}

istream& operator>>(istream& is, Reading& r)
{
	is >> r.hour >> r.tempCelsius;
	return is;
}

void WriteRandomReadings(ofstream& ofs, const int counter)
{
	constexpr int lastHourInDay = 23;
	constexpr int minTempCelsius = -10;
	constexpr int maxTempCelsius = 20;
	constexpr int minDelta = 1;				// min delta of temparature in 1 hour * 100;
	constexpr int maxDelta = 100;			// max delta of temparature in 1 hour * 100;
	constexpr char Celsius{ 'c' };
	constexpr char Fahrenheit{ 'f' };
	int hour = 0;
	char ch{ Celsius };
	double tempCelsius = randint(minTempCelsius, maxTempCelsius);
	for (int i = 0; i < counter; i++) {
		if (hour == 0) ch = (randint(-100, 100) <= 0) ? Celsius : Fahrenheit;
		if (hour > 5 && hour < 17) tempCelsius += double(randint(minDelta, maxDelta)) / 100;
		else tempCelsius -= double(randint(minDelta, maxDelta)) / 100;
		double temp;
		if (ch == Celsius) temp = tempCelsius;
		else temp = CelsiusToFahrenheit(tempCelsius);
		ofs << hour++ << ' ' << temp << ch << '\n';
		if (hour > lastHourInDay) hour = 0;
	}
}

Reading ReadReadingsFromFile(ifstream& ifs)
{
	constexpr char Fahrenheit{ 'f' };
	Reading r;
	char ch;
	ifs >> r >> ch;
	if (!ifs) {
		if (ifs.eof()) throw EndOfFile{};
		error("Error. Reading failed");
	}
	if (ch == Fahrenheit) r.tempCelsius = FahrenheitToCelsius(r.tempCelsius);
	return r;
}

double CelsiusToFahrenheit(double tempCels)
{
	constexpr double absoluteZeroCel = -273.15;
	constexpr double absoluteZeroFahr = 9.0 / 5 * absoluteZeroCel + 32;
	if (tempCels >= absoluteZeroCel) {
		return 9.0 / 5 * tempCels + 32;
	}
	else {
		error("The temperature value must be greater than or equal to absolute zero");
	}
}

double FahrenheitToCelsius(double tempFahr)
{
	constexpr double absoluteZeroCel = -273.15;
	constexpr double absoluteZeroFahr = 9.0 / 5 * absoluteZeroCel + 32;
	if (tempFahr >= absoluteZeroFahr) {
		return (tempFahr - 32) * 5 / 9;
	}
	else {
		error("The temperature value must be greater than or equal to absolute zero");
	}
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
