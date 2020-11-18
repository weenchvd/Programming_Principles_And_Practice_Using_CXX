/* Exercise 24.5 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include"../Matrix/Matrix11.h"
#include"../Matrix/MatrixIO11.h"
#include"C24_Exercise_24.5.h"

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
		"  (1) classical_gaussian_elimination(), (2) pivotal_elimination()\n"
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
				double a[2][2] =
				{
				   {0,1},
				   {1,0},
				};
				double b[2] = { 5,6 };

				Matrix A(a);
				Vector B(b);

				cout << "Solving A * x = B" << endl;
				cout << "A =\n" << A << endl;
				cout << "B = " << B << endl;

				Vector x = classical_gaussian_elimination(A, B);
				cout << "x = " << x << endl;

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
		case CASE2: {
			try {
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


				double a[2][2] =
				{
				   {0,1},
				   {1,0},
				};
				double b[2] = { 5,6 };

				Matrix A(a);
				Vector B(b);

				cout << "Solving A * x = B" << endl;
				cout << "A =\n" << A << endl;
				cout << "B = " << B << endl;

				Vector x = pivotal_elimination(A, B);
				cout << "x = " << x << endl;

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
	classical_elimination(A, b);
	return back_substitution(A, b);
}

void classical_elimination(Matrix& A, Vector& b)
{
	const Numeric_lib::Index n = A.dim1();
	// traverse from 1st column to the next-to-last
	// filling zeros into all elements under the diagonal:
	for (Numeric_lib::Index j = 0; j < n - 1; ++j) {
		const double pivot = A(j, j);
		if (pivot == 0) throw Elim_failure("Elimination failure in row " + to_string(j));
		// fill zeros into each element under the diagonal of the ith row:
		for (Numeric_lib::Index i = j + 1; i < n; ++i) {
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = Numeric_lib::scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j); // make the corresponding change to b
		}
	}
}

Vector back_substitution(const Matrix& A, const Vector& b)
{
	const Numeric_lib::Index n = A.dim1();
	Vector x(n);
	for (Numeric_lib::Index i = n - 1; i >= 0; --i) {
		double s = b(i) - Numeric_lib::dot_product(A[i].slice(i + 1), x.slice(i + 1));
		if (double m = A(i, i)) x(i) = s / m;
		else throw Back_subst_failure("Back substitution failure in row " + to_string(i));
	}
	return x;
}

Vector pivotal_elimination(Matrix A, Vector b)
{
	elim_with_partial_pivot(A, b);
	return back_substitution(A, b);
}

void elim_with_partial_pivot(Matrix& A, Vector& b)
{
	const Numeric_lib::Index n = A.dim1();
	for (Numeric_lib::Index j = 0; j < n; ++j) {
		Numeric_lib::Index pivot_row = j;
		// look for a suitable pivot:
		for (Numeric_lib::Index k = j + 1; k < n; ++k)
			if (abs(A(k, j)) > abs(A(pivot_row, j))) pivot_row = j;
		// swap the rows if we found a better pivot:
		if (pivot_row != j) {
			A.swap_rows(j, pivot_row);
			swap(b(j), b(pivot_row));
		}
		// elimination:
		for (Numeric_lib::Index i = j + 1; i < n; ++i) {
			const double pivot = A(j, j);
			if (pivot == 0) throw Elim_failure("can't solve: pivot == 0");
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = Numeric_lib::scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j);
		}
	}
}
