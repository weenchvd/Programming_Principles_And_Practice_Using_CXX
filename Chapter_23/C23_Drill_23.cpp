/* Drill 23 */

#include<iostream>
#include<istream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<string>
#include<regex>
#include"C23_Drill_23.h"

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
		"  (1) Drill,\n"
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
			ifstream ifs{ "C23_Drill_23_input.txt" };			// input file
			if (!ifs) cerr << "no file\n";
			regex pat{ R"(\w{2}\s*\d{5}(-\d{4})?)" };			// postal code pattern
			int lineno = 0;
			for (string line; getline(ifs, line); ) {
				++lineno;
				smatch matches;
				if (regex_search(line, matches, pat)) {
					cout << lineno << ": " << matches[0] << '\n';					// whole match
					if (matches.size() > 1 && matches[1].matched) {
						cout << "\t: " << matches[1] << '\n';						// sub-match
					}
				}
			}

			cout << endl << endl;
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
