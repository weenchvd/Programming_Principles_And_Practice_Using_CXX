/* Exercise 14.15 */

#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include"C14_Exercise_14.15.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		VECTORITERATOR, LISTITERATOR
	};
	const string actionList = "\tList of actions:\n"
	"  (1) print(Vector_iterator&), 2 print(List_iterator&)\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	vector<double> v;
	v.push_back(3.14);
	v.push_back(0.12);
	v.push_back(555);
	v.push_back(111.999);
	v.push_back(-90.90);
	Vector_iterator vi{ v };
	list<double> l;
	l.push_back(1.255);
	l.push_back(0.9994);
	l.push_back(999);
	l.push_back(222.111);
	l.push_back(-10.77);
	List_iterator li{ l };
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case VECTORITERATOR: {
			print(vi);
			cout << '\n';
			break;
		}
		case LISTITERATOR: {
			print(li);
			cout << '\n';
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

void print(Iterator& it)
{
	for (double* p = it.next(); p != nullptr; p = it.next()) {
		cout << *p << '\n';
	}
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
