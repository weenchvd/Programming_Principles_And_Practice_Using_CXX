﻿/* Exercise 11.15 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"C11_Exercise_11.15.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

const string errMessageInputFile = "Error. Can't open input file: ";
const string errMessageOutputFile = "Error. Can't open output file: ";

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		PRINTSCIENTIFIC
	};
	const string actionList = "\tList of actions:\n"
	"  (1) ReadAndPrintScientific()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case PRINTSCIENTIFIC: {
			string inFileName;
			cout << "Please enter the name of input file: ";
			if (!(cin >> inFileName)) { ClearInput(cin); error("Error. Incorrect input"); }
			string outFileName;
			cout << "Please enter the name of output file: ";
			if (!(cin >> outFileName)) { ClearInput(cin); error("Error. Incorrect input"); }
			ReadAndPrintScientific(inFileName, outFileName);
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

void ReadAndPrintScientific(const string& inputFileName, const string& outputFileName)
{
	ifstream ifs;
	ifs.open(inputFileName);
	if (!ifs) error(errMessageInputFile, inputFileName);
	ofstream ofs;
	ofs.open(outputFileName);
	if (!ofs) error(errMessageOutputFile, outputFileName);
	vector<double> numbers;
	for (double d; ifs >> d; ) {
		numbers.push_back(d);
	}
	if (!ifs.eof()) error("Input failure");
	int fieldNumber = 1;
	ofs << scientific << setprecision(8);
	for (double& d : numbers) {
		if (fieldNumber >= 5) {
			fieldNumber = 1;
			ofs << endl;
		}
		ofs << setw(20) << d;
		fieldNumber++;
	}
	ifs.close();
	ofs.close();
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
