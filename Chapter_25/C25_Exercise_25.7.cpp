﻿/* Exercise 25.7 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include"C25_Exercise_25.7.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Hexadecimal values\n"
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
			constexpr int decimal400 = 400;
			cout << "Hexadecimal values from 0 to " << decimal400 << " (decimal):" << hex << showbase << endl;
			for (int i = 0; i <= decimal400; ++i) {
				cout << i << ' ';
			}
			cout << dec << vsp_2;
			
			constexpr int decimalMinus200 = -200;
			constexpr int decimal200 = 200;
			cout << "Hexadecimal values from " << decimalMinus200 << " to "
				<< decimal200 << " (decimal):" << hex << endl;
			for (int i = decimalMinus200; i <= decimal200; ++i) {
				cout << i << ' ';
			}
			cout << dec << endl;

			cout << vsp_2;
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
