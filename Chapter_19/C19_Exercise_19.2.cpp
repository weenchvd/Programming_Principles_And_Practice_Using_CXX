/* Exercise 19.2 */

#include<iostream>
#include<istream>
#include<string>
#include<vector>
#include<iomanip>
#include<sstream>
#include"C19_Exercise_19.2.h"

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
		SUM
	};
	const string actionList = "\tList of actions:\n"
	"  (1) Sum()\n"
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
		case SUM: {
			vector<int> vi1 = { -4, -3, -2, -1 };
			vector<double> vd1 = { 0.11, -1.4, 9.99, 100 };
			cout << space_c2 << "Sum(vi1, vd1) == " << Sum(vi1, vd1) << endl;
			
			vector<int> vi2 = { -4, -3, -2, -1 };
			vector<int> vi3 = { 5, 5, 5, 5 };
			cout << space_c2 << "Sum(vi2, vi3) == " << Sum(vi2, vi3) << endl;

			//vector<string> vs1 = { "asd", "ref", "ffff" };
			//vector<char> vc1 = { 'X', 'Y', 'Z' };
			//cout << space_c2 << "Sum(vs1, vc1) == " << Sum(vs1, vc1) << endl;

			vector<double> vd2 = { -4, -3, -2, -1 };
			vector<double> vd3 = { 0.11, -1.4 };
			cout << space_c2 << "Sum(vd2, vd3) == " << Sum(vd2, vd3) << endl;
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

template<class T, class U> long double Sum(const vector<T>& vt, const vector<U>& vu)
{
	if (vt.size() != vu.size()) error("Error. The vector sizes are not equal");
	long double sum = 0;
	for (int i = 0; i < vt.size(); i++) sum += double(vt[i]) * vu[i];
	return sum;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
