/* Exercise 10.3 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<cstdio>
#include"C10_Exercise_10.3.h"

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
		EXIT = -1, PRINTACTIONLIST, READFILE, MEAN, MEDIAN
	};
	const string actionList = "\tList of actions:\n"
	"  (1) read file \"raw_temps.txt\", (2) mean, (3) median\n"
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
		case READFILE: {
			ifstream ifs { fileName };
			if (!ifs) error(errMessageInputFile, fileName);
			size_t currentSize{ tempStats.size() };
			int i = 0;
			while (true) try {
				if (i < currentSize && i >= 0) tempStats[i] = ReadReadingsFromFile(ifs);
				else tempStats.push_back(ReadReadingsFromFile(ifs));
				i++;
			}
			catch (EndOfFile& e) {
				break;
			}
			break;
		}
		case MEAN: {
			if (tempStats.size() == 0) error("Error. No data");
			double mean = 0;
			for (int i = 0; i < tempStats.size(); i++) {
				mean += tempStats[i].tempCelsius;
			}
			mean /= tempStats.size();
			cout << "    Mean: " << mean << endl;
			break;
		}
		case MEDIAN: {
			if (tempStats.size() == 0) error("Error. No data");
			cout << "    Median: ";
			size_t nReadings{ tempStats.size() };
			if (nReadings % 2) cout << tempStats[nReadings / 2].tempCelsius << endl;
			else cout << (tempStats[nReadings / 2].tempCelsius + tempStats[nReadings / 2 - 1].tempCelsius) / 2 << endl;
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
	const char* f = fileName.c_str();
	remove(f); // erase file "integers"
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

Reading ReadReadingsFromFile(ifstream& ifs)
{
	Reading r;
	ifs >> r;
	if (!ifs) {
		if (ifs.eof()) throw EndOfFile{};
		error("Error. Reading failed");
	}
	return r;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
