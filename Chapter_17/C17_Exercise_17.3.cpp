/* Exercise 17.3 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C17_Exercise_17.3.h"

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
		TOLOWER
	};
	const string actionList = "\tList of actions:\n"
	"  (1) ToLower()\n"
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
		case TOLOWER: {
			cout << "\nPlease enter the string in English (only ASCII):\n";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cs = new char[s.size() + 1];
			int i;
			for (i = 0; i < s.size(); i++) cs[i] = s[i];
			cs[i] = '\0';
			to_lower(cs);
			for (i = 0; i < s.size() + 1; i++) {
				cout << cs[i];
			}
			cout << endl;
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

void to_lower(char* s)
{
	constexpr char firstUppercaseLetter = 'A';
	constexpr char lastUppercaseLetter = 'Z';
	constexpr int diff = 'a' - 'A';
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] >= firstUppercaseLetter && s[i] <= lastUppercaseLetter) s[i] += diff;
	}
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
