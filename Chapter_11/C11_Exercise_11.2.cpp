/* Exercise 11.2 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"C11_Exercise_11.2.h"

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
		EXIT = -1, PRINTACTIONLIST,
		PRINTLINES
	};
	const string actionList = "\tList of actions:\n"
	"  (1) PrintAllLinesWithWord()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case PRINTLINES: {
			string fn;
			cout << "Please enter the file name: ";
			if (!(cin >> fn)) { ClearInput(cin); error("Error. Incorrect input"); }
			ifstream ifs{ fn };
			if (!ifs) error(errMessageInputFile, fn);
			string word;
			cout << "Please enter the word: ";
			if (!(cin >> word)) { ClearInput(cin); error("Error. Incorrect input"); }
			cout << "\nCase sensetive\n";
			PrintAllLinesWithWord(cout, ifs, word, true);
			cout << "\n\nNo case sensetive\n";
			ifs.clear();
			ifs.seekg(0);
			PrintAllLinesWithWord(cout, ifs, word, false);
			cout << "\n\nDone!\n";
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

void PrintAllLinesWithWord(ostream& os, istream& is, const string word, const bool caseSensetive)
{
	int lineNumber = 0;
	string w;
	if (caseSensetive) w = word;
	else {
		for (char ch : word) {
			if (isalpha(ch)) w += tolower(ch);
		}
	}
	while (true) {
		string line;
		getline(is, line);
		if (!is) {
			if (is.eof()) break;
			error("Input failure");
		}
		lineNumber++;
		string str;
		if (caseSensetive) str = line;
		else StringToLower(line, str);
		istringstream iss;
		iss.str(str);
		string s;
		while (iss >> s) {
			if (s == w) {
				os << "Line " << setw(4) << lineNumber << ": " << line << endl;
				break;
			}
		}
	}
}

void StringToLower(const string& source, string& destination)
{
	for (char ch : source) {
		if (isalpha(ch)) destination += tolower(ch);
		else destination += ch;
	}
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
