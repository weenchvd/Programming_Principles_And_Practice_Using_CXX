/* Exercise 23.13 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<regex>
#include"C23_Exercise_23.13.h"

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
		"  (1) Check dot (.)\n"
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
			string sNL{ "1234\n\n\n\n" };
			regex patternNL{ R"(.{8})" };
			cout << sp_2 << "string sNL{ \"1234\\n\\n\\n\\n\" };" << endl;
			cout << sp_2 << "regex patternNL{ R\"(.{8})\" };" << endl;
			cout << sp_2 << "regex_match(sNL, patternNL): ";
			if (regex_match(sNL, patternNL)) {
				cout << "TRUE" << endl;
				cout << sp_4 << "Dot(.) matches '\\n'" << endl;
			}
			else {
				cout << "FALSE" << endl;
				cout << sp_4 << "Dot(.) does not match '\\n'" << endl;
			}
			cout << endl;

			string sTab{ "1234\t\t\t\t" };
			regex patternTab{ R"(.{8})" };
			cout << sp_2 << "string sTab{ \"1234\\t\\t\\t\\t\" };" << endl;
			cout << sp_2 << "regex patternTab{ R\"(.{8})\" };" << endl;
			cout << sp_2 << "regex_match(sTab, patternTab): ";
			if (regex_match(sTab, patternTab)) {
				cout << "TRUE" << endl;
				cout << sp_4 << "Dot(.) matches '\\t'" << endl;
			}
			else {
				cout << "FALSE" << endl;
				cout << sp_4 << "Dot(.) does not match '\\t'" << endl;
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
