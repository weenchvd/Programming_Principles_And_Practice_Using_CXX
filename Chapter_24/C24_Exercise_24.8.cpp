/* Exercise 24.8 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include"../Matrix/Matrix11.h"
#include"../Matrix/MatrixIO11.h"
#include"C24_Exercise_24.8.h"

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
		"  (1) Gaussian ilimination\n"
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
			try {
				cout << endl;
				double a[3][3] =
				{
				   {1,2,3},
				   {2,3,4},
				   {3,4,1}
				};
				double b[3] = { 14,20,14 };

				Matrix A(a);
				Vector B(b);

				cout << "Source data:" << endl;
				cout << "Solving A * x = B" << endl;
				cout << "A =\n" << A << endl;
				cout << "B = " << B << endl;
				Vector x = classical_gaussian_elimination(A, B);
				cout << "Vector x = " << x << endl;
				cout << vsp_2;


				double c[3][3] =
				{
				   {2,1,-1},
				   {-3,-1,2},
				   {-2,1,2}
				};
				double d[3] = { 8,-11,-3 };

				Matrix C(c);
				Vector D(d);

				cout << "Solving C * y = D" << endl;
				cout << "C =\n" << C << endl;
				cout << "D = " << D << endl;

				Vector y = classical_gaussian_elimination(C, D);
				cout << "y = " << y << endl;
				cout << vsp_2;


				double e[3][3] =
				{
				   {1,3,5},
				   {1,-2,4},
				   {0,1,3}
				};
				double f[3] = { 6,-8,0 };

				Matrix E(e);
				Vector F(f);

				cout << "Solving E * z = F" << endl;
				cout << "E =\n" << E << endl;
				cout << "F = " << F << endl;

				Vector z = classical_gaussian_elimination(E, F);
				cout << "z = " << z << endl;


				cout << vsp_2;
			}
			catch (Elim_failure& e) {
				cerr << e.what() << endl;
			}
			catch (Back_subst_failure& e) {
				cerr << e.what() << endl;
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

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}

Vector classical_gaussian_elimination(Matrix A, Vector b)
{
	cout << sp_2 << "Classical Gaussian elimination:" << endl;
	classical_elimination(A, b);
	return back_substitution(A, b);
}

void classical_elimination(Matrix& A, Vector& b)
{
	cout << sp_4 << "Classical elimination:" << endl;
	cout << sp_6 << "Matrix A = " << endl;
	cout << sp_6 << "{" << endl;
	for (Numeric_lib::Index i = 0; i < A.dim1(); ++i) {
		cout << sp_6 << "  " << A[i] << endl;
	}
	cout << sp_6 << "}" << endl;
	cout << sp_6 << "Vector b = " << b << endl;

	const Numeric_lib::Index n = A.dim1();
	// traverse from 1st column to the next-to-last
	// filling zeros into all elements under the diagonal:
	for (Numeric_lib::Index j = 0; j < n - 1; ++j) {
		const double pivot = A(j, j);
		if (pivot == 0) throw Elim_failure("Elimination failure in row " + to_string(j));
		cout << sp_6 << "Pivot: A(" << j << "," << j << ") = " << pivot << endl;
		// fill zeros into each element under the diagonal of the ith row:
		for (Numeric_lib::Index i = j + 1; i < n; ++i) {
			const double mult = A(i, j) / pivot;
			cout << sp_8 << "Multiplier: A(" << i << "," << j << ") / Pivot = "
				<< A(i, j) << " / " << pivot << " = " << mult << endl;
			if (A[j].size() != A[i].size()) throw Elim_failure("Sizes are not equal");
			for (Numeric_lib::Index k = j; k < A[i].size(); ++k) {
				cout << sp_8 << sp_2 << "A(" << i << "," << k << ") = "
					<< "A(" << j << "," << k << ") * -Multiplier + A(" << i << "," << k << ")"
					<< " = " << A(j, k) <<  " * " << -mult << " + " << A(i, k) << " = ";
				A(i, k) = A(j, k) * -mult + A(i, k);
				cout << A(i, k) << endl;
			}
			cout << sp_8 << sp_2 << "b(" << i << ") = b(" << i << ") - Multiplier * b(" << j << ")"
				<< " = " << b(i) << " - " << mult << " * " << b(j) << " = ";
			b(i) -= mult * b(j); // make the corresponding change to b
			cout << b(i) << endl;
		}
	}

	cout << sp_6 << "Matrix A = " << endl;
	cout << sp_6 << "{" << endl;
	for (Numeric_lib::Index i = 0; i < A.dim1(); ++i) {
		cout << sp_6 << "  " << A[i] << endl;
	}
	cout << sp_6 << "}" << endl;
	cout << sp_6 << "Vector b = " << b << endl;
}

Vector back_substitution(const Matrix& A, const Vector& b)
{
	cout << sp_4 << "Back substitution:" << endl;
	cout << sp_6 << "Matrix A = " << endl;
	cout << sp_6 << "{" << endl;
	for (Numeric_lib::Index i = 0; i < A.dim1(); ++i) {
		cout << sp_6 << "  " << A[i] << endl;
	}
	cout << sp_6 << "}" << endl;
	cout << sp_6 << "Vector b = " << b << endl;

	const Numeric_lib::Index n = A.dim1();
	Vector x(n);
	cout << sp_6 << "Vector x = " << x << endl;
	for (Numeric_lib::Index i = n - 1; i >= 0; --i) {
		if (A[i].size() != x.size()) throw Elim_failure("Sizes are not equal");
		double sum = 0;
		cout << sp_8 << "Sum = 0" << endl;
		for (Numeric_lib::Index k = i + 1; k < x.size(); ++k) {
			cout << sp_8 << "Sum = Sum + A(" << i << "," << k << ") * " << "x(" << k << ") = "
				<< sum << " + " << A(i, k) << " * " << x(k) << " = ";
			sum += A(i, k) * x(k);
			cout << sum << endl;
		}
		double s = b(i) - sum;
		if (double m = A(i, i)) {
			cout << sp_8 << sp_2 << "x(" << i << ") = (b(" << i << ") - Sum) / A(" << i << "," << i << ") = "
				<< "(" << b(i) << " - " << sum << ") / " << A(i, i) << " = ";
			x(i) = s / m;
			cout << x(i) << endl;
		}
		else throw Back_subst_failure("Back substitution failure in row " + to_string(i));
	}
	cout << sp_6 << "Vector x = " << x << endl;
	return x;
}
