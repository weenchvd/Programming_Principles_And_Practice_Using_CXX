/* Exercise 21.6 */

#include<iostream>
#include<istream>
#include<sstream>
#include<string>
#include<set>
#include<iomanip>
#include"C21_Exercise_21.6.h"

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
		"  (1) set<Fruit*>,\n"
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
			set<Fruit*, FruitComparison> setF;
			setF.insert(new Fruit{ "Apple" });
			setF.insert(new Fruit{ "Kiwi" });
			setF.insert(new Fruit{ "Orange" });
			setF.insert(new Fruit{ "Plum", 5, 0.35 });
			setF.insert(new Fruit{ "Grape", 10, 2.20 });
			setF.insert(new Fruit{ "Mango", 20, 4.0 });
			cout << sp_2 << "Fruits:" << endl;
			for (auto it = setF.begin(); it != setF.end(); ++it) cout << **it << endl;
			for (auto it = setF.begin(); it != setF.end(); ++it) delete *it;

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

ostream& operator<<(ostream& os, const Fruit& f)
{
	return os << "Name: " << setw(16) << left << f.name << "Count: " << setw(6) << left << f.count
		<< "Unit price: " << f.unitPrice;
}
