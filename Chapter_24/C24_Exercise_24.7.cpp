/* Exercise 24.7 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include<vector>
#include"../Matrix/Matrix11.h"
#include"../Matrix/MatrixIO11.h"
#include"C24_Exercise_24.7.h"

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
				Matrix A =
				{
				   {1,2,3},
				   {2,3,4},
				   {3,4,1}
				};
				Vector B = { 14,20,14 };

				cout << "Solving A * x = B" << endl;
				cout << "A =\n" << A << endl;
				cout << "B = " << B << endl;

				Vector x = classical_gaussian_elimination(A, B);
				cout << "x = " << x << endl;
				cout << vsp_2;


				Matrix C =
				{
				   {2,1,-1},
				   {-3,-1,2},
				   {-2,1,2}
				};
				Vector D = { 8,-11,-3 };

				cout << "Solving C * y = D" << endl;
				cout << "C =\n" << C << endl;
				cout << "D = " << D << endl;

				Vector y = classical_gaussian_elimination(C, D);
				cout << "y = " << y << endl;
				cout << vsp_2;


				Matrix E =
				{
				   {1,3,5},
				   {1,-2,4},
				   {0,1,3}
				};
				Vector F = { 6,-8,0 };

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
	classical_elimination(A, b);
	return back_substitution(A, b);
}

void classical_elimination(Matrix& A, Vector& b)
{
	const int n = A.size();
	// traverse from 1st column to the next-to-last
	// filling zeros into all elements under the diagonal:
	for (int j = 0; j < n - 1; ++j) {
		const double pivot = A.at(j).at(j);
		if (pivot == 0) throw Elim_failure("Elimination failure in row " + to_string(j));
		// fill zeros into each element under the diagonal of the ith row:
		for (int i = j + 1; i < n; ++i) {
			const double mult = A.at(i).at(j) / pivot;
			if (A.at(j).size() != A.at(i).size()) throw Elim_failure("Sizes are not equal");
			for (int k = j; k < A.at(i).size(); ++k) {
				A.at(i).at(k) = A.at(j).at(k) * -mult + A.at(i).at(k);
			}
			b.at(i) -= mult * b.at(j); // make the corresponding change to b
		}
	}
}

Vector back_substitution(const Matrix& A, const Vector& b)
{
	const int n = A.size();
	Vector x(n);
	for (int i = n - 1; i >= 0; --i) {
		if (A.at(i).size() != x.size()) throw Elim_failure("Sizes are not equal");
		double sum = 0;
		for (int k = i + 1; k < x.size(); ++k) {
			sum += A.at(i).at(k) * x.at(k);
		}
		double s = b.at(i) - sum;
		if (double m = A.at(i).at(i)) x.at(i) = s / m;
		else throw Back_subst_failure("Back substitution failure in row " + to_string(i));
	}
	return x;
}

ostream& operator<<(ostream& os, const Matrix& m)
{
	os << "{\n";
	for (int i = 0; i < m.size(); ++i) {
		os << "  {";
		for (int j = 0; j < m[i].size(); ++j) {
			os << ' ' << m[i][j];
		}
		os << " }\n";
	}
	os << "}";
	return os;
}

ostream& operator<<(ostream& os, const Vector& v)
{
	os << '{';
	for (int i = 0; i < v.size(); ++i) {
		os << "  " << v[i];
	}
	os << " }";
	return os;
}
