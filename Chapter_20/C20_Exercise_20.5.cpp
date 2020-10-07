/* Exercise 20.5 */

#include<iostream>
#include<fstream>
#include<istream>
#include<string>
#include<vector>
#include<iomanip>
#include<sstream>
#include<cstdlib>
#include"C20_Exercise_20.5.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		VECTOR
	};
	const string actionList = "\tList of actions:\n"
	"  (1) vector<<>>()\n"
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
		case VECTOR: {
			istringstream iss;
			iss.str("ASD BFG SST tty qwerty");
			vector<string> vs;
			iss >> vs;
			cout << endl << sp_2 << "vs:" << endl << sp_4;
			for (int i = 0; i < vs.size(); i++) cout << vs[i] << " ";

			vector<double> vd = { 3.14, 43.22, 666.6, 0.155, -345.0 };
			cout << endl << sp_2 << "vd:" << endl;
			cout << vd;

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

template<class T> istream& operator>>(istream& is, vector<T>& v)
{
	T temp;
	while (is >> temp) v.push_back(temp);
	return is;
}

template<class T> ostream& operator<<(ostream& os, const vector<T>& v)
{
	for (int i = 0; i < v.size() && os; i++) os << v[i] << endl;
	return os;
}
