/* Exercise 10.8 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<cstdio>
#include"C10_Exercise_10.8.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }


int main()
{
	const string errMessageInputFile = "Error. Can't open input file: ";
	const string errMessageOutputFile = "Error. Can't open output file: ";
	enum Action {
		EXIT = -1, PRINTACTIONLIST, CONCATENATEFILES
	};
	const string actionList = "\tList of actions:\n"
	"  (1) concatenate files and output to \"result.txt\"\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	const string outputFileName = "result.txt";
	bool cond{ true };
	int action;
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case CONCATENATEFILES: {
			string fileName1;
			cout << "Please enter the name of file 1: ";
			if (!(cin >> fileName1)) { ClearInput(cin); error("Error. Incorrect input"); }
			string fileName2;
			cout << "Please enter the name of file 2: ";
			if (!(cin >> fileName2)) { ClearInput(cin); error("Error. Incorrect input"); }
			ifstream ifs1{ fileName1 };
			if (!ifs1) error(errMessageInputFile, fileName1);
			ifstream ifs2{ fileName2 };
			if (!ifs2) error(errMessageInputFile, fileName2);
			ofstream ofs { outputFileName };
			if (!ofs) error(errMessageOutputFile, outputFileName);
			char ch;
			while (ifs1.get(ch)) {
				ofs.put(ch);
			}
			if (!ifs1.eof()) error("ifs1 != eof");
			while (ifs2.get(ch)) {
				ofs.put(ch);
			}
			if (!ifs2.eof()) error("ifs2 != eof");
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

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
