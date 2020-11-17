/* Exercise 24.1 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include"../Matrix/Matrix11.h"
#include"../Matrix/MatrixIO11.h"
#include"C24_Exercise_24.1.h"

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
		"  (1) triple()\n"
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
			Numeric_lib::Matrix<int> mat(5);
			for (int i = 0; i < 5; ++i) mat[i] = i + 1;
			
			Numeric_lib::Matrix<int> mat1(5);
			for (int i = 0; i < 5; ++i) mat1[i] = i + 1;
			Numeric_lib::Matrix<int> mat2(5);
			mat1.apply(triple1);
			mat2 = Numeric_lib::apply(triple2, mat);
			cout << sp_2 << "Source Matrix<int> mat: " << mat << endl;
			cout << sp_2 << "Matrix<int> mat1.apply(triple1): " << mat1 << endl;
			cout << sp_2 << "Matrix<int> mat2 = Numeric_lib::apply(triple2, mat): " << mat2 << endl;
			cout << sp_2 << "Source Matrix<int> mat: " << mat << endl;

			Numeric_lib::Matrix<int> mat3(5);
			for (int i = 0; i < 5; ++i) mat3[i] = i + 1;
			Numeric_lib::Matrix<int> mat4(5);
			mat3.apply(triple);
			mat4 = Numeric_lib::apply(triple, mat);
			cout << endl;
			cout << sp_2 << "Source Matrix<int> mat: " << mat << endl;
			cout << sp_2 << "Matrix<int> mat3.apply(triple): " << mat3 << endl;
			cout << sp_2 << "Matrix<int> mat4 = Numeric_lib::apply(triple, mat): " << mat4 << endl;
			cout << sp_2 << "Source Matrix<int> mat: " << mat << endl;

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
