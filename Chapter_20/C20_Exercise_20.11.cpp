/* Exercise 20.11 */

#include<iostream>
#include<istream>
#include<sstream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include<iomanip>
#include"C20_Exercise_20.11.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		COPY
	};
	const string actionList = "\tList of actions:\n"
	"  (1) Copy()\n"
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
		case COPY: {
			list<int> li;
			li.push_back(18);
			li.push_back(-34);
			li.push_back(0);
			li.push_back(2);
			li.push_back(111);
			cout << endl << sp_2 << "Initial list<int>:" << endl << sp_4;
			for (list<int>::iterator it = li.begin(); it != li.end(); ++it) cout << *it << " ";

			vector<double>* p = Copy(li);
			if (p == nullptr) cout << "List not copied" << endl;
			else {
				bool isCorrect = true;
				if (li.size() != p->size()) {
					cout << "The copy is incorrect";
					isCorrect = false;
				}
				if (isCorrect) {
					list<int>::iterator itList = li.begin();
					for (vector<double>::iterator itVec = p->begin(); itVec != p->end(); ++itVec) {
						if (*itList != *itVec) {
							cout << "The copy is incorrect";
							isCorrect = false;
							break;
						}
						++itList;
					}
				}
				if (isCorrect) {
					sort(p->begin(), p->end());
					cout << endl << sp_2 << "vector<double>*:" << endl;
					cout << *p << endl << endl;
				}
				delete p;
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

template<class T> ostream& operator<<(ostream& os, const vector<T>& v)
{
	for (int i = 0; i < v.size() && os; i++) os << v[i] << endl;
	return os;
}

vector<double>* Copy(list<int>& listInt)
{
	vector<double>* p = new vector<double>;
	if (p == nullptr) return nullptr;
	for (list<int>::iterator it = listInt.begin(); it != listInt.end(); ++it) p->push_back(*it);
	return p;
}
