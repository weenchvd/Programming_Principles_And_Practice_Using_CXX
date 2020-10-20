/* Exercise 21.4 */

#include<iostream>
#include<istream>
#include<sstream>
#include<vector>
#include<list>
#include<string>
#include<iomanip>
#include"C21_Exercise_21.4.h"

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
		"  (1) CountIf(),\n"
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
				<< sp_4 << "CountIf(vi.begin(), vi.end(), GreaterThan<int>{ 56 }): "
				<< CountIf(vi.begin(), vi.end(), GreaterThan<int>{ 56 }) << endl
				<< sp_4 << "CountIf(vi.begin(), vi.end(), [](int x) { return x < 6; }): "
				<< CountIf(vi.begin(), vi.end(), [](int x) { return x < 6; }) << endl
				<< sp_4 << "CountIf(vi.begin(), vi.end(), [](int x) { return x != 2; }): "
				<< CountIf(vi.begin(), vi.end(), [](int x) { return x != 2; }) << endl << endl;
			
			list<double> ld{ 3.14, 4.44, 2.0, 3.14, 3.15, 65.0, 46.22 };
			cout << sp_2 << "list<double> ld{ 3.14, 4.44, 2.0, 3.14, 3.15, 65.0, 46.22 };" << endl
				<< sp_4 << "CountIf(ld.begin(), ld.end(), [](double x) { return x > 10.0; }): "
				<< CountIf(ld.begin(), ld.end(), [](double x) { return x > 10.0; }) << endl
				<< sp_4 << "CountIf(ld.begin(), ld.end(), LowerThan<double>{ 3.2 }): "
				<< CountIf(ld.begin(), ld.end(), LowerThan<double>{ 3.2 }) << endl
				<< sp_4 << "CountIf(ld.begin(), ld.end(), NotEqual<double>{ 3.15 }): "
				<< CountIf(ld.begin(), ld.end(), NotEqual<double>{ 3.15 }) << endl << endl;
			
			string s{ "asd gara rgeh hrth gpeg ag;ar ;raeghear sdfghhadgafg nbbnter.34458" };
			cout << sp_2 << "string s{ \"asd gara rgeh hrth gpeg ag; ar; raeghear sdfghhadgafg nbbnter.34458\" };" << endl
				<< sp_4 << "CountIf(s.begin(), s.end(), [](char x) { return x > 's'; }): "
				<< CountIf(s.begin(), s.end(), [](char x) { return x > 's'; }) << endl
				<< sp_4 << "CountIf(s.begin(), s.end(), [](char x) { return x < 'a'; }): "
				<< CountIf(s.begin(), s.end(), [](char x) { return x < 'a'; }) << endl
				<< sp_4 << "CountIf(s.begin(), s.end(), NotEqual<char>{ 'a' }): "
				<< CountIf(s.begin(), s.end(), NotEqual<char>{ 'a' }) << endl << endl;

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

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}

template<class InputIterator, class UnaryPredicate>
unsigned long long int CountIf(InputIterator first, InputIterator last, UnaryPredicate pred)
{
	unsigned long long int c = 0;
	while (first != last) {
		if (pred(*first++)) c++;
	}
	return c;
}
