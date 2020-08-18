/* Exercise 18.3 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C18_Exercise_18.3.h"

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
		STRINGCOMPARE
	};
	const string actionList = "\tList of actions:\n"
	"  (1) strcmp()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	const char* indent2 = "  ";
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case STRINGCOMPARE: {
			cout << "\nPlease enter the first string in English (only ASCII): ";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* s1 = new char[s.size() + 1];
			int i;
			for (i = 0; i < s.size(); i++) s1[i] = s[i];
			s1[i] = '\0';
			cout << "Please enter the second string in English (only ASCII): ";
			string x;
			if (!getline(cin, x)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* s2 = new char[x.size() + 1];
			for (i = 0; i < x.size(); i++) s2[i] = x[i];
			s2[i] = '\0';
			int result = str_cmp(s1, s2);
			if (result == 0) cout << indent2 << "The strings are equal" << endl;
			else if (result < 0) cout << "The first string is lexicographically before the second string" << endl;
			else cout << "The first string is lexicographically after the second string" << endl;
			delete[] s1;
			delete[] s2;
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

int str_cmp(const char* s1, const char* s2)
{
	char* ps1 = const_cast<char*>(s1);
	char* ps2 = const_cast<char*>(s2);
	while (*ps1 == *ps2 && *ps1 != '\0') {
		ps1++;
		ps2++;
	}
	return *ps1 - *ps2;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
