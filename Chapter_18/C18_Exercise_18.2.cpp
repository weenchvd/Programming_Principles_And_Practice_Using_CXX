/* Exercise 18.2 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C18_Exercise_18.2.h"

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
		FIND
	};
	const string actionList = "\tList of actions:\n"
	"  (1) findx()\n"
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
		case FIND: {
			cout << "\nPlease enter the original string in English (only ASCII): ";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cs = new char[s.size() + 1];
			int i;
			for (i = 0; i < s.size(); i++) cs[i] = s[i];
			cs[i] = '\0';
			cout << "Please enter the search string in English (only ASCII): ";
			string x;
			if (!getline(cin, x)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cx = new char[x.size() + 1];
			for (i = 0; i < x.size(); i++) cx[i] = x[i];
			cx[i] = '\0';
			char* result = find_x(cs, cx);
			if (result == nullptr) cout << indent2 << "The search string was not found" << endl;
			else {
				cout << endl << indent2 << "Address of the origin string: " << static_cast<void*>(cs) << endl
					<< indent2 << "The origin string: " << cs << endl;
				cout << indent2 << "Address of the first occurrence of the search string in the origin string: "
					<< static_cast<void*>(result) << endl
					<< indent2 << "The origin string from the place where the search string occurs: "
					<< result << endl;
			}
			delete[] cs;
			delete[] cx;
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

char* find_x(const char* s, const char* x)
{
	if (s == nullptr || x == nullptr) return nullptr;
	char* p = nullptr;
	char* ps = const_cast<char*>(s);
	char* px = const_cast<char*>(x);
	for (; *ps != '\0'; ps++) {
		if (*ps == *px) {
			if (px == const_cast<char*>(x)) p = ps;
			px++;
		}
		else if (*px == '\0' && px > const_cast<char*>(x)) return p;
		else px = const_cast<char*>(x);
	}
	if (*px == '\0' && px > const_cast<char*>(x)) return p;
	return nullptr;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
