/* Exercise 15.1 */

#include<iostream>
#include<string>
#include<sstream>
#include"C15_Exercise_15.1.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		FACTORIAL
	};
	const string actionList = "\tList of actions:\n"
	"  (1) fac(),\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case FACTORIAL: {
			for (int i = 0; i <= 20; i++) {
				long long int result = FactorialIterative(i);
				if (result != FactorialRecursive(i)) {
					ostringstream oss;
					oss << "FactorialIterative(" << i << ") != FactorialRecursive(" << i << ")";
					error(oss.str());
				}
				cout << "fac(" << i << ") == " << result << "\n";
			}
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

long long int FactorialIterative(int n)
{
	long long int r = 1;
	while (n > 1) {
		r *= n;
		n--;
	}
	return r;
}

long long int FactorialRecursive(int n)
{
	return (n > 1) ? n * FactorialRecursive(n - 1) : 1;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
