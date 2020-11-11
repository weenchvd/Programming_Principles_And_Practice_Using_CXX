/* Exercise 23.8 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<vector>
#include<regex>
#include"C23_Exercise_23.8.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Search\n"
		"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case CASE1: {
			cout << endl;
			cout << sp_2 << "Please enter a file name: ";
			string fileName;
			getline(cin, fileName);
			if (!cin) error("Error. Incorrect input");
			ifstream ifs{ fileName };
			if(!ifs) error("Error. File opening error");

			string s;
			cout << sp_2 << "Please enter a pattern: ";
			getline(cin, s);
			if (!cin) error("Error. Incorrect input");

			regex pattern;
			try {
				pattern = s; // this checks pat
				cout << sp_4 << "Pattern: " << s << endl;
			}
			catch (regex_error) {
				error(s + " is not a valid regular expression\n");
			}

			size_t lineNum = 0;
			cout << sp_4 << "[Format] Line number: line" << endl;
			while (true) {
				++lineNum;
				string s;
				getline(ifs, s);
				if (!ifs) {
					if (ifs.eof()) break;
					else error("Error. Read error");
				}
				smatch matches;
				if (regex_search(s, matches, pattern)) {
					cout << sp_4 << lineNum << ": " << s << endl;
					for (int i = 0; i < matches.size(); ++i) {
						cout << sp_6 << "matches[" << i << "]: " << matches[i] << endl;
					}
				}
			}

			cout << vsp_2;
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
