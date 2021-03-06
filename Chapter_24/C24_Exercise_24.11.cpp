﻿/* Exercise 24.11 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include"../Matrix/Matrix11.h"
#include"../Matrix/MatrixIO11.h"
#include"C24_Exercise_24.11.h"

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
		"  (1) swap_columns()\n"
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
			int a[3][3] =
			{
				{1,2,3},
				{4,5,6},
				{7,8,9}
			};

			Numeric_lib::Matrix<int, 2> A(a);
			cout << "A =\n" << A << endl;
			A.swap_columns(1, 2);
			cout << endl << "A.swap_columns(2, 3);" << endl;
			cout << "A =\n" << A << endl;
			A.swap_columns(0, 2);
			cout << endl << "A.swap_columns(0, 2);" << endl;
			cout << "A =\n" << A << endl;

			cout << endl << endl;
			int b[3][5] =
			{
				{1,2,3,4,5},
				{11,12,13,14,15},
				{55,66,77,88,99}
			};

			Numeric_lib::Matrix<int, 2> B(b);
			cout << "B =\n" << B << endl;
			B.swap_columns(0, 4);
			cout << endl << "B.swap_columns(0, 4);" << endl;
			cout << "B =\n" << B << endl;
			B.swap_columns(2, 3);
			cout << endl << "B.swap_columns(2, 3);" << endl;
			cout << "B =\n" << B << endl;


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
