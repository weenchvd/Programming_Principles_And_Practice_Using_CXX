/* Exercise 21.3 */

#include<iostream>
#include<istream>
#include<sstream>
#include<vector>
#include<list>
#include<string>
#include<iomanip>
#include"C21_Exercise_21.3.h"

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
		"  (1) Count(),\n"
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
			vector<int> vi{ 2, 56, 2, 65, 4, 6, 22, 2, 99, 0 , -54, -2 };
			cout << sp_2 << "vector<int> vi{ 2, 56, 2, 65, 4, 6, 22, 2, 99, 0 , -54, -2 };" << endl
				<< sp_4 << "Count(vi.begin(), vi.end(), int{ 2 }): "
				<< Count(vi.begin(), vi.end(), int{ 2 }) << endl;
			list<double> ld{ 3.14, 4.44, 2.0, 3.14, 3.15, 65.0, 46.22 };
			cout << sp_2 << "list<double> ld{ 3.14, 4.44, 2.0, 3.14, 3.15, 65.0, 46.22 };" << endl
				<< sp_4 << "Count(ld.begin(), ld.end(), double{ 3.14 }): "
				<< Count(ld.begin(), ld.end(), double{ 3.14 }) << endl;
			string s{ "asd gara rgeh hrth gpeg ag;ar ;raeghear sdfghhadgafg nbbnter.34458" };
			cout << sp_2 << "string s{ \"asd gara rgeh hrth gpeg ag; ar; raeghear sdfghhadgafg nbbnter.34458\" };" << endl
				<< sp_4 << "Count(s.begin(), s.end(), 'h'): "
				<< Count(s.begin(), s.end(), 'h') << endl;

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

template<class InputIterator, class T>
unsigned long long int Count(InputIterator first, InputIterator last, const T& value)
{
	unsigned long long int c = 0;
	while (first != last) {
		if (*first++ == value) c++;
	}
	return c;
}
