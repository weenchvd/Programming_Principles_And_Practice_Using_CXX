/* Exercise 24.12 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include"../Matrix/Matrix11.h"
#include"../Matrix/MatrixIO11.h"
#include"C24_Exercise_24.12.h"

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
		"  (1) operator*, (2) operator+\n"
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
				{1,2,3},
				{2,3,4},
			};
			double b[3] = { 4,0,1 };

			Numeric_lib::Matrix<double, 2> A(a);
			Numeric_lib::Matrix<double> B(b);

			cout << "Source data:" << endl;
			cout << "A =\n" << A << endl;
			cout << "B = " << B << endl;
			cout << endl << "A * B = X" << endl;
			Numeric_lib::Matrix<double> X = A * B;
			cout << "X = " << X << endl;
			cout << endl;

			// invalid case
			double c[2][2] =
			{
				{1,2},
				{2,3},
			};
			double d[3] = { 4,0,1 };

			Numeric_lib::Matrix<double, 2> C(c);
			Numeric_lib::Matrix<double> D(d);

			cout << "Source data:" << endl;
			cout << "C =\n" << C << endl;
			cout << "D = " << D << endl;
			cout << endl << "C * D = Y" << endl;
			Numeric_lib::Matrix<double> Y = C * D;
			cout << "Y = " << Y << endl;

			cout << vsp_2;
			break;
		}
		case CASE2: {
			cout << endl;
			double a[2][3] =
			{
				{1,2,3},
				{2,3,4},
			};
			double b[2][3] =
			{
				{1,2,3},
				{2,3,4},
			};

			Numeric_lib::Matrix<double, 2> A(a);
			Numeric_lib::Matrix<double, 2> B(b);

			cout << "Source data:" << endl;
			cout << "A =\n" << A << endl;
			cout << "B =\n" << B << endl;
			cout << endl << "A + B = X" << endl;
			Numeric_lib::Matrix<double, 2> X = A + B;
			cout << "X =\n" << X << endl;
			cout << endl;

			double c[3] = { 4,0,1 };
			double d[3] = { 2,3,6 };

			Numeric_lib::Matrix<double> C(c);
			Numeric_lib::Matrix<double> D(d);

			cout << "Source data:" << endl;
			cout << "C = " << C << endl;
			cout << "D = " << D << endl;
			cout << endl << "C + D = Y" << endl;
			Numeric_lib::Matrix<double> Y = C + D;
			cout << "Y = " << Y << endl;
			cout << endl;

			double e[2][2] =
			{
				{1,2},
				{2,3},
			};
			double f[2][3] =
			{
				{1,2,3},
				{2,3,4},
			};

			Numeric_lib::Matrix<double, 2> E(e);
			Numeric_lib::Matrix<double, 2> F(f);

			cout << "Source data:" << endl;
			cout << "E =\n" << E << endl;
			cout << "F =\n" << F << endl;
			cout << endl << "E + F = Z" << endl;
			Numeric_lib::Matrix<double, 2> Z = E + F;
			cout << "Z =\n" << Z << endl;
			cout << endl;


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

Numeric_lib::Matrix<double> operator*(Numeric_lib::Matrix<double, 2>& A, Numeric_lib::Matrix<double>& B)
{
	if (A.dim2() != B.dim1()) error("Error. The number of columns in the first matrix"
		" must be equal to the number of rows in the second matrix");
	Numeric_lib::Matrix<double> result(A.dim1());
	for (Numeric_lib::Index i = 0; i < A.dim1(); ++i) {
		double sum = 0;
		for (Numeric_lib::Index j = 0; j < B.dim1(); ++j) sum += A(i, j) * B(j);
		result(i) = sum;
	}
	return result;
}

Numeric_lib::Matrix<double, 1> operator+(Numeric_lib::Matrix<double, 1>& A, Numeric_lib::Matrix<double, 1>& B)
{
	if (A.dim1() != B.dim1()) {
		error("Error. The matrices must have an equal number of rows to be added");
	}
	Numeric_lib::Matrix<double> result(A.dim1());
	for (Numeric_lib::Index i = 0; i < A.dim1(); ++i) result(i) = A(i) + B(i);
	return result;
}

Numeric_lib::Matrix<double, 2> operator+(Numeric_lib::Matrix<double, 2>& A, Numeric_lib::Matrix<double, 2>& B)
{
	if (A.dim1() != B.dim1() || A.dim2() != B.dim2()) {
		error("Error. The matrices must have an equal number of rows and columns to be added");
	}
	Numeric_lib::Matrix<double, 2> result(A.dim1(), A.dim2());
	for (Numeric_lib::Index i = 0; i < A.dim1(); ++i) {
		for (Numeric_lib::Index j = 0; j < A.dim2(); ++j) {
			result(i, j) = A(i, j) + B(i, j);
		}
	}
	return result;
}
