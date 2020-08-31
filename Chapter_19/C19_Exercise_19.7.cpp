/* Exercise 19.7 */

#include<iostream>
#include<istream>
#include<string>
#include<vector>
#include<iomanip>
#include<sstream>
#include"C19_Exercise_19.7.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

const char* space_c2 = "  ";
const char* space_c4 = "    ";
//const char* errMessageInputFile = "Error. Can't open input file: ";
//const char* errMessageOutputFile = "Error. Can't open output file: ";

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		NUMBER
	};
	const string actionList = "\tList of actions:\n"
	"  (1) Number()\n"
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
		case NUMBER: {
			vector<Number<int>> vni1 = { 5, 8, 1, 4, 0 };
			vector<Number<int>> vni2 = { 0, 0, 2, 1, 4 };
			long double svni = Sum(vni1, vni2);
			cout << space_c2 << "vector<Number<int>> vni1 = { 5, 8, 1, 4, 0 };" << endl
				<< space_c2 << "vector<Number<int>> vni2 = { 0, 0, 2, 1, 4 };" << endl
				<< space_c2 << "long double svni = Sum(vni1, vni2);" << endl;
			cout << space_c4 << "svni == " << svni << endl << endl;

			vector<Number<double>> vnd1 = { 1.11, 4.67, 9.22, 2.0 };
			vector<Number<double>> vnd2 = { 0.4, 9.9, 4.2, 8.0 };
			long double svnd = Sum(vnd1, vnd2);
			cout << space_c2 << "vector<Number<double>> vnd1 = { 1.11, 4.67, 9.22, 2.0 };" << endl
				<< space_c2 << "vector<Number<double>> vnd2 = { 0.4, 9.9, 4.2, 8.0 };" << endl
				<< space_c2 << "long double svnd = Sum(vnd1, vnd2);" << endl;
			cout << space_c4 << "svnd == " << svnd << endl;

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

template<class T> istream& operator>>(istream& is, Number<T>& n)
{
	T temp;
	if (!(is >> temp)) return is;
	n.v = temp;
	return is;
}

template<class T> ostream& operator<<(ostream& os, Number<T> n)
{
	os << n.v;
	return os;
}

template<class T, class U> long double Sum(const vector<T>& vt, const vector<U>& vu)
{
	if (vt.size() != vu.size()) error("Error. The vector sizes are not equal");
	long double sum = 0;
	for (int i = 0; i < vt.size(); i++) sum += double(vt[i]) * double(vu[i]);
	return sum;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
