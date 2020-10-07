/* Exercise 20.7 */

#include<iostream>
#include<istream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
#include<iomanip>
#include"C20_Exercise_20.7.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		FINDLEXLAST
	};
	const string actionList = "\tList of actions:\n"
	"  (1) Find the lexicographical last string\n"
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
		case FINDLEXLAST: {
			vector<string> vs;
			vs.push_back("List of actions:");
			vs.push_back("Print the list of actions");
			vs.push_back("Exit");
			vs.push_back("Error. Incorrect input");
			vs.push_back("Error. Incorrect action number");
			vs.push_back("Error. Exception");
			vs.push_back("Please enter the action");
			cout << endl << sp_2 << "Initial vector<string>:";
			cout << endl << vs;

			sort(vs.begin(), vs.end());
			cout << endl << endl << sp_2 << "The lexicographical last string in the vector<string>:";
			cout << endl << sp_4 << vs[vs.size() - 1];

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

template<class T> ostream& operator<<(ostream& os, const vector<T>& v)
{
	for (int i = 0; i < v.size() && os; i++) os << v[i] << endl;
	return os;
}
