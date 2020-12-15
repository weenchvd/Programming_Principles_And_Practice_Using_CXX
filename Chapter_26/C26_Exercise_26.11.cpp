/* Exercise 26.11 */

#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<random>
#include<chrono>
#include"../Matrix/Matrix11.h"
#include"../Matrix/MatrixIO11.h"
#include"C26_Exercise_26.11.h"

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
		"  (1) Time\n"
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
			default_random_engine generator;
			uniform_int_distribution<int> dist(-10, 9);
			using timeUnit = chrono::nanoseconds;
			constexpr int dimension1 = 10;
			constexpr int dimension2 = 100;
			constexpr int dimension3 = 1000;
			constexpr int dimension4 = 10000;
			
			{
				Numeric_lib::Matrix<double, 2> m1(dimension1, dimension1);
				for (int i = 0; i < m1.dim1(); ++i) {
					for (int j = 0; j < m1.dim2(); ++j) {
						m1[i][j] = dist(generator);
					}
				}
				vector<double> v1(dimension1);
				long long int v1time = 0;
				for (int i = 0; i < v1.size(); ++i) {
					auto t1 = chrono::system_clock::now();
					double sum = row_accum(m1, i + 1);
					auto t2 = chrono::system_clock::now();
					v1time += chrono::duration_cast<timeUnit>(t2 - t1).count();
					v1[i] = sum;
				}
				cout << "Time of row_accum(Matrix<double,2>(" << dimension1 << "," << dimension1 << ")): "
					<< v1time << " nanosecond(s)" << endl;

				Numeric_lib::Matrix<double, 2> m2(dimension2, dimension2);
				for (int i = 0; i < m2.dim1(); ++i) {
					for (int j = 0; j < m2.dim2(); ++j) {
						m2[i][j] = dist(generator);
					}
				}
				vector<double> v2(dimension2);
				long long int v2time = 0;
				for (int i = 0; i < v2.size(); ++i) {
					auto t1 = chrono::system_clock::now();
					double sum = row_accum(m2, i + 1);
					auto t2 = chrono::system_clock::now();
					v2time += chrono::duration_cast<timeUnit>(t2 - t1).count();
					v2[i] = sum;
				}
				cout << "Time of row_accum(Matrix<double,2>(" << dimension2 << "," << dimension2 << ")): "
					<< v2time / 1000 << " microsecond(s)" << endl;

				Numeric_lib::Matrix<double, 2> m3(dimension3, dimension3);
				for (int i = 0; i < m3.dim1(); ++i) {
					for (int j = 0; j < m3.dim2(); ++j) {
						m3[i][j] = dist(generator);
					}
				}
				vector<double> v3(dimension3);
				long long int v3time = 0;
				for (int i = 0; i < v3.size(); ++i) {
					auto t1 = chrono::system_clock::now();
					double sum = row_accum(m3, i + 1);
					auto t2 = chrono::system_clock::now();
					v3time += chrono::duration_cast<timeUnit>(t2 - t1).count();
					v3[i] = sum;
				}
				cout << "Time of row_accum(Matrix<double,2>(" << dimension3 << "," << dimension3 << ")): "
					<< v3time / 1000000 << " millisecond(s)" << endl;

				Numeric_lib::Matrix<double, 2> m4(dimension4, dimension4);
				for (int i = 0; i < m4.dim1(); ++i) {
					for (int j = 0; j < m4.dim2(); ++j) {
						m4[i][j] = dist(generator);
					}
				}
				vector<double> v4(dimension4);
				long long int v4time = 0;
				for (int i = 0; i < v4.size(); ++i) {
					auto t1 = chrono::system_clock::now();
					double sum = row_accum(m4, i + 1);
					auto t2 = chrono::system_clock::now();
					v4time += chrono::duration_cast<timeUnit>(t2 - t1).count();
					v4[i] = sum;
				}
				cout << "Time of row_accum(Matrix<double,2>(" << dimension4 << "," << dimension4 << ")): "
					<< v4time / 1000000000 << " second(s)" << endl;
			}
			cout << endl;
			{
				Numeric_lib::Matrix<double, 2> m1(dimension1, dimension1);
				for (int i = 0; i < m1.dim1(); ++i) {
					for (int j = 0; j < m1.dim2(); ++j) {
						m1[i][j] = dist(generator);
					}
				}
				vector<double> v1(dimension1);
				long long int v1time = 0;
				for (int i = 0; i < v1.size(); ++i) {
					auto t1 = chrono::system_clock::now();
					double sum = row_sum(m1, i);
					if (i > 0) sum += v1[i - 1];
					auto t2 = chrono::system_clock::now();
					v1time += chrono::duration_cast<timeUnit>(t2 - t1).count();
					v1[i] = sum;
				}
				cout << "Time of more efficient algorithm, Matrix<double,2>(" << dimension1 << ","
					<< dimension1 << "): " << v1time << " nanosecond(s)" << endl;

				Numeric_lib::Matrix<double, 2> m2(dimension2, dimension2);
				for (int i = 0; i < m2.dim1(); ++i) {
					for (int j = 0; j < m2.dim2(); ++j) {
						m2[i][j] = dist(generator);
					}
				}
				vector<double> v2(dimension2);
				long long int v2time = 0;
				for (int i = 0; i < v2.size(); ++i) {
					auto t1 = chrono::system_clock::now();
					double sum = row_sum(m2, i);
					if (i > 0) sum += v2[i - 1];
					auto t2 = chrono::system_clock::now();
					v2time += chrono::duration_cast<timeUnit>(t2 - t1).count();
					v2[i] = sum;
				}
				cout << "Time of more efficient algorithm, Matrix<double,2>(" << dimension2 << ","
					<< dimension2 << "): " << v2time / 1000 << " microsecond(s)" << endl;

				Numeric_lib::Matrix<double, 2> m3(dimension3, dimension3);
				for (int i = 0; i < m3.dim1(); ++i) {
					for (int j = 0; j < m3.dim2(); ++j) {
						m3[i][j] = dist(generator);
					}
				}
				vector<double> v3(dimension3);
				long long int v3time = 0;
				for (int i = 0; i < v3.size(); ++i) {
					auto t1 = chrono::system_clock::now();
					double sum = row_sum(m3, i);
					if (i > 0) sum += v3[i - 1];
					auto t2 = chrono::system_clock::now();
					v3time += chrono::duration_cast<timeUnit>(t2 - t1).count();
					v3[i] = sum;
				}
				cout << "Time of more efficient algorithm, Matrix<double,2>(" << dimension3 << ","
					<< dimension3 << "): " << v3time / 1000 << " microsecond(s)" << endl;

				Numeric_lib::Matrix<double, 2> m4(dimension4, dimension4);
				for (int i = 0; i < m4.dim1(); ++i) {
					for (int j = 0; j < m4.dim2(); ++j) {
						m4[i][j] = dist(generator);
					}
				}
				vector<double> v4(dimension4);
				long long int v4time = 0;
				for (int i = 0; i < v4.size(); ++i) {
					auto t1 = chrono::system_clock::now();
					double sum = row_sum(m4, i);
					if (i > 0) sum += v4[i - 1];
					auto t2 = chrono::system_clock::now();
					v4time += chrono::duration_cast<timeUnit>(t2 - t1).count();
					v4[i] = sum;
				}
				cout << "Time of more efficient algorithm, Matrix<double,2>(" << dimension4 << ","
					<< dimension4 << "): " << v4time / 1000000 << " millisecond(s)" << endl;
			}


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

double row_sum(const Numeric_lib::Matrix<double, 2>& m, int n)
{
	double sum = 0;
	for (int i = 0; i < m.dim2(); ++i) sum += m[n][i];
	return sum;
}

double row_accum(const Numeric_lib::Matrix<double, 2>& m, int n) // sum of elements in m[0:n)
{
	double s = 0;
	for (int i = 0; i < n; ++i) s += row_sum(m, i);
	return s;
}
