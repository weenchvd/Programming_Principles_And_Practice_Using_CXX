/* Exercise 10.1 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<cstdio>
#include"C10_Exercise_10.1.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }
inline int randint(int max) { return rand() % max; }
inline int randint(int min, int max) { return randint(max - min) + min; }


int main()
{
	constexpr int counter = 100;
	constexpr int min = -10000;
	constexpr int max = 10000;
	const string errMessageInputFile = "Error. Can't open input file: ";
	const string errMessageOutputFile = "Error. Can't open output file: ";
	enum Action {
		EXIT = -1, PRINTACTIONLIST, CREATEFILE, PRINTFILE, SUMMARIZEINTEGERS
	};
	const string actionList = "\tList of actions:\n"
	"  (1) create file \"integers\" with 100 integers, (2) print file \"integers\", (3) summarize integers\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	string fileName = "integers";
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
			WriteRandomIntegers(ofs, counter, min, max);
			break;
		}
		case PRINTFILE: {
			ifstream ifs{ fileName };
			if (!ifs) error(errMessageInputFile, fileName);
			while (true) try {
				cout << ReadIntegerFromFile(ifs) << ' ';
			}
			catch (EndOfFile& e) {
				break;
			}
			cout << endl;
			break;
		}
		case SUMMARIZEINTEGERS: {
			ifstream ifs{ fileName };
			if (!ifs) error(errMessageInputFile, fileName);
			int sum = 0;
			while (true) try {
				sum += ReadIntegerFromFile(ifs);
			}
			catch (EndOfFile& e) {
				break;
			}
			cout << "    Sum: " << sum << endl;
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

void WriteRandomIntegers(ofstream& ofs, const int counter, const int min, const int max)
{
	for (int i = 0; i < counter; i++) {
		ofs << randint(min, max);
		if (i < counter - 1) ofs << ' ';
	}
}

int ReadIntegerFromFile(ifstream& ifs)
{
	int integer;
	ifs >> integer;
	if (!ifs) {
		if (ifs.eof()) throw EndOfFile{};
		error("Error. Reading failed");
	}
	return integer;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
