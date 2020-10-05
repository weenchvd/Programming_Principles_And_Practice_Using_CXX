/* Drill 20 */

#include<iostream>
#include<istream>
#include<string>
#include<vector>
#include<list>
#include<array>
#include<iomanip>
#include<sstream>
#include"C20_Drill_20.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		DRILL
	};
	const string actionList = "\tList of actions:\n"
	"  (1) Drill\n"
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
		case DRILL: {
			constexpr int n = 10;
			array<int, n> ai = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			vector<int> vi = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			list<int> li = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			cout << sp_2 << "ai:" << endl << sp_4;
			for (int i = 0; i < ai.size(); i++) cout << ai[i] << ", ";
			cout << endl << sp_2 << "vi:" << endl << sp_4;
			for (int i = 0; i < vi.size(); i++) cout << vi[i] << ", ";
			cout << endl << sp_2 << "li:" << endl << sp_4;
			for (list<int>::iterator it = li.begin(); it != li.end(); it++) cout << *it << ", ";

			array<int, n> ai2{ ai };
			vector<int> vi2{ vi };
			list<int> li2{ li };
			cout << endl << endl << sp_2 << "ai2:" << endl << sp_4;
			for (int i = 0; i < ai2.size(); i++) cout << ai2[i] << ", ";
			cout << endl << sp_2 << "vi2:" << endl << sp_4;
			for (int i = 0; i < vi2.size(); i++) cout << vi2[i] << ", ";
			cout << endl << sp_2 << "li2:" << endl << sp_4;
			for (list<int>::iterator it = li2.begin(); it != li2.end(); it++) cout << *it << ", ";

			for (int i = 0; i < ai.size(); i++) ai2[i] += 2;
			for (int i = 0; i < vi2.size(); i++) vi2[i] += 3;
			for (list<int>::iterator it = li2.begin(); it != li2.end(); it++) *it += 5;
			cout << endl << endl << sp_2 << "ai2 + 2:" << endl << sp_4;
			for (int i = 0; i < n; i++) cout << ai2[i] << ", ";
			cout << endl << sp_2 << "vi2 + 3:" << endl << sp_4;
			for (int i = 0; i < vi2.size(); i++) cout << vi2[i] << ", ";
			cout << endl << sp_2 << "li2 + 5:" << endl << sp_4;
			for (list<int>::iterator it = li2.begin(); it != li2.end(); it++) cout << *it << ", ";

			Copy(ai2.begin(), ai2.end(), vi2.begin());
			Copy(li2.begin(), li2.end(), ai2.begin());
			cout << endl << endl << sp_2 << "ai2 after Copy():" << endl << sp_4;
			for (int i = 0; i < n; i++) cout << ai2[i] << ", ";
			cout << endl << sp_2 << "vi2 after Copy():" << endl << sp_4;
			for (int i = 0; i < vi2.size(); i++) cout << vi2[i] << ", ";
			cout << endl << sp_2 << "li2 after Copy():" << endl << sp_4;
			for (list<int>::iterator it = li2.begin(); it != li2.end(); it++) cout << *it << ", ";

			vector<int>::iterator itPosVec = find(vi2.begin(), vi2.end(), 3);
			list<int>::iterator itPosList = find(li2.begin(), li2.end(), 27);
			cout << endl << endl << "find(vi2.begin(), vi2.end(), 3):" << endl;
			if (itPosVec == vi2.end()) cout << sp_4 << "Value was not found";
			else cout << sp_4 << "Position: " << itPosVec - vi2.begin();
			cout << endl << "find(li2.begin(), li2.end(), 27):" << endl;
			if (itPosList == li2.end()) cout << sp_4 << "Value was not found";
			else {
				int i = 0;
				for (list<int>::iterator it = li.begin(); it != itPosList; it++, i++);
				i++;
				cout << sp_4 << "Position: " << i;
			}

			cout << endl << endl;
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

template<class Iter1, class Iter2>
Iter2 Copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
	while (f1 != e1) *f2++ = *f1++;
	return f2;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
