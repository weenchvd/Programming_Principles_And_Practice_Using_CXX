/* Exercise 24.9 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include"../Matrix/Matrix11.h"
#include"../Matrix/MatrixIO11.h"
#include"C24_Exercise_24.9.h"

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
		"  (1) MyApply::apply(Function, Matrix)\n"
		"  (2) MyApply::apply(Function, Matrix, Argument)\n"
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
			double a[2][3] =
			{
				{1.1,2.2,3.3},
				{2.5,3.6,4.7},
			};
			Numeric_lib::Matrix<double, 2> A(a);

			cout << "Source data:" << endl;
			cout << "A =\n" << A << endl;
			cout << endl << sp_2 << "auto X = MyApply::apply(Triple<int, double>, A);" << endl;
			auto X = MyApply::apply(Triple<int, double>, A);
			cout << "X =\n" << X << endl;
			cout << vsp_2;

			int b[4][3] =
			{
				{1,2,3},
				{2,3,4},
				{3,4,5},
				{4,5,6},
			};
			Numeric_lib::Matrix<int, 2> B(b);

			cout << "Source data:" << endl;
			cout << "B =\n" << B << endl;
			cout << endl << sp_2 << "auto Y = MyApply::apply(Triple<double, int>, B);" << endl;
			auto Y = MyApply::apply(Triple<double, int>, B);
			cout << "Y =\n" << Y << endl;
			cout << vsp_2;

			int c[2][5] =
			{
				{11,12,13,14,15},
				{20,25,30,35,40},
			};
			Numeric_lib::Matrix<int, 2> C(c);

			cout << "Source data:" << endl;
			cout << "C =\n" << C << endl;
			cout << endl << sp_2 << "auto Z = MyApply::apply(Triple<char, int>, C);" << endl;
			auto Z = MyApply::apply(Triple<char, int>, C);
			cout << "Z =\n" << Z << endl;

			cout << vsp_2;
			break;
		}
		case CASE2: {
			cout << endl;
			double a[2][3] =
			{
				{1.1,2.2,3.3},
				{2.5,3.6,4.7},
			};
			Numeric_lib::Matrix<double, 2> A(a);

			cout << "Source data:" << endl;
			cout << "A =\n" << A << endl;
			cout << endl << sp_2 << "auto X = MyApply::apply(TripleArg<int, double>, A, int{ 9000 });" << endl;
			auto X = MyApply::apply(TripleArg<int, double>, A, int{ 9000 });
			cout << "X =\n" << X << endl;
			cout << vsp_2;

			int b[4][3] =
			{
				{1,2,3},
				{2,3,4},
				{3,4,5},
				{4,5,6},
			};
			Numeric_lib::Matrix<int, 2> B(b);

			cout << "Source data:" << endl;
			cout << "B =\n" << B << endl;
			cout << endl << sp_2 << "auto Y = MyApply::apply(TripleArg<double, int>, B, double{ 0.35 });" << endl;
			auto Y = MyApply::apply(TripleArg<double, int>, B, double{ 0.35 });
			cout << "Y =\n" << Y << endl;
			cout << vsp_2;

			int c[2][5] =
			{
				{17,18,19,20,21},
				{30,31,32,33,34},
			};
			Numeric_lib::Matrix<int, 2> C(c);

			cout << "Source data:" << endl;
			cout << "C =\n" << C << endl;
			cout << endl << sp_2 << "auto Z = MyApply::apply(Multiply<char, int>, C, int{ 2 });" << endl;
			auto Z = MyApply::apply(Multiply<char, int>, C, int{ 2 });
			cout << "Z =\n" << Z << endl;

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

