/* Exercise 19.1 */

#include<iostream>
#include<istream>
#include<string>
#include<vector>
#include<iomanip>
#include<sstream>
#include"C19_Exercise_19.1.h"

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
		F
	};
	const string actionList = "\tList of actions:\n"
	"  (1) f()\n"
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
		case F: {
			vector<int> vi1 = { -4, -3, -2, -1 };
			vector<int> vi2 = { 5, 6, 7, 8 };
			f(vi1, vi2);
			Print(vi1);
			cout << endl;

			vector<string> vs1 = { "A", "AA", "AAA" };
			vector<string> vs2 = { "BC", "BC", "BC" };
			f(vs1, vs2);
			Print(vs1);
			cout << endl;

			//vector<vector<int>> vvi1 = { {4, 5}, {0, 1} };
			//vector<vector<int>> vvi2 = { {-1, -1}, {0, 1} };
			//f(vvi1, vvi2);
			//Print(vvi1);
			//cout << endl;

			vector<double> vd1 = { 0.99, 0.1, 1.15 };
			vector<double> vd2 = { 0.11, -1.4 };
			f(vd1, vd2);
			Print(vd1);
			cout << endl;
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

template<class T> void f(vector<T>& v1, vector<T>& v2)
{
	if (v1.size() != v2.size()) error("Error. The vector sizes are not equal");
	vector<T> v;
	for (int i = 0; i < v1.size(); i++) v.push_back(v1[i] + v2[i]);
	v1 = v;
}

template<class T> void Print(vector<T>& v)
{
	for (int i = 0; i < v.size(); i++) cout << space_c4 << v[i] << endl;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
