/* Exercise 11.13 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"C11_Exercise_11.13.h"

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
		REVERSEORDER
	};
	const string actionList = "\tList of actions:\n"
	"  (1) ReverseOrderOfWords()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case REVERSEORDER: {
			string inFileName;
			cout << "Please enter the name of input file: ";
			if (!(cin >> inFileName)) { ClearInput(cin); error("Error. Incorrect input"); }
			ReverseOrderOfWords(inFileName);
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

void ReverseOrderOfWords(const string& inputFileName)
{
	ifstream ifs;
	ifs.open(inputFileName);
	if (!ifs) error(errMessageInputFile, inputFileName);
	string outFileName = { "temp" };
	ofstream ofs;
	ofs.open(outFileName);
	if (!ofs) error(errMessageOutputFile, outFileName);
	vector<string> lines;
	string s;
	while (getline(ifs, s)) {
		lines.push_back(s);
	}
	if (ifs.eof() && s.size() == 0) lines.push_back(s);
	bool newLine = false;
	for (int i = lines.size() - 1; i >= 0; i--) {
		if (newLine) ofs << endl;
		string& ss = lines[i];
		int j;
		for (j = ss.size() - 1; j >= 0; j--) {
			if (isspace(ss[j])) {
				WriteOneWordSincePosition(ofs, ss, j + 1);
				ofs << ss[j];
			}
		}
		if (ss.size() > 0 && ++j == 0 && !isspace(ss[j])) {
			WriteOneWordSincePosition(ofs, ss, j);
		}
		newLine = true;
	}
	ifs.close();
	ofs.close();
	const char* fi = inputFileName.c_str();
	remove(fi);
	const char* fo = outFileName.c_str();
	rename(fo, fi);
}

void WriteOneWordSincePosition(ofstream& ofs, const string& s, int pos)
{
	for (; pos < s.size(); pos++) {
		if (isspace(s[pos])) return;
		ofs << s[pos];
	}
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
