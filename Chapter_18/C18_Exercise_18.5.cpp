/* Exercise 18.5 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C18_Exercise_18.5.h"

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
		CONCATENATE
	};
	const string actionList = "\tList of actions:\n"
	"  (1) cat_dot()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	const char* space2 = "  ";
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case CONCATENATE: {
			cout << "\nPlease enter the first string in English (only ASCII): ";
			string s1;
			if (!getline(cin, s1)) { ClearInput(cin); error("Error. Incorrect input"); }
			cout << "Please enter the second string in English (only ASCII): ";
			string s2;
			if (!getline(cin, s2)) { ClearInput(cin); error("Error. Incorrect input"); }
			string result = cat_dot(s1, s2);
			cout << space2 << "Result: " << result << endl;
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

string cat_dot(const string& s1, const string& s2)
{
	string ret = s1 + '.' + s2;
	return ret;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
