/* Exercise 18.1 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C18_Exercise_18.1.h"

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
		STRINGDUPLICATE
	};
	const string actionList = "\tList of actions:\n"
	"  (1) strdup()\n"
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
		case STRINGDUPLICATE: {
			cout << "\nPlease enter the string in English (only ASCII): ";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cs = new char[s.size() + 1];
			int i;
			for (i = 0; i < s.size(); i++) cs[i] = s[i];
			cs[i] = '\0';
			char* duplicate = str_dup(cs);
			cout << "Address " << static_cast<void*>(cs) << ": " << static_cast<char*>(cs) << endl;
			cout << "Address " << static_cast<void*>(duplicate) << ": " << static_cast<char*>(duplicate) << endl;
			delete[] cs;
			delete[] duplicate;
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

char* str_dup(const char* s)
{
	if (s == nullptr) return nullptr;
	char* ss;
	int size;
	for (ss = const_cast<char*>(s), size = 0; *ss != '\0'; ss++, size++);
	char* duplicate = new char[++size];
	ss = const_cast<char*>(s);
	for (char* dd = duplicate; (*dd = *ss) != '\0'; ss++, dd++);
	return duplicate;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
