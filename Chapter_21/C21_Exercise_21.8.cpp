/* Exercise 21.8 */

#include<iostream>
#include<istream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<iomanip>
#include"C21_Exercise_21.8.h"

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
		"  (1) Order of frequency,\n"
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
			map<string, int> words;
			cout << sp_2 << "Please enter a text, than press Control+Z and press Enter" << endl;
			for (string s; cin >> s; ) ++words[s];
			cout << sp_2 << "Words in lexicographical order:" << endl;
			for (const auto& p : words) cout << sp_4 << p.first << ": " << p.second << '\n';
			cout << endl << endl;

			vector<pair<const string, int>*> freq;
			for (map<string, int>::iterator it = words.begin(); it != words.end(); ++it) {
				freq.push_back(&*it);
			}
			sort(freq.begin(), freq.end(),
				[](const pair<const string, int>* a, const pair<const string, int>* b)
				{ return a->second < b->second; });
			cout << sp_2 << "Words in order of frequency:" << endl;
			for (const pair<const string, int>* p : freq) {
				cout << sp_4 << p->second << ": " << p->first << endl;
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

