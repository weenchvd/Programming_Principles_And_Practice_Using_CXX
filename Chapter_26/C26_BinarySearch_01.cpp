﻿/* Binary Search */

#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include"C26_BinarySearch_01.h"

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
		"  (1) BinarySearch()\n"
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
			cout << sp_2 << "Enter list of ints:" << endl;
			string s;
			getline(cin, s);
			istringstream iss{ s };
			vector<int> v;
			for (int num; iss >> num; ) {
				v.push_back(num);
			}
			sort(v.begin(), v.end());
			for (int x : v) {
				cout << x << ' ';
			}
			cout << endl;
			cout << sp_2 << "Enter a number to search for: ";
			getline(cin, s);
			iss.clear();
			iss.str(s);
			int x;
			iss >> x;
			pair<bool, size_t> result = BinarySearch(v, x);
			if (result.first == true) {
				cout << sp_4 << "The number found, position = " << result.second + 1 << endl;
			}
			else cout << "The number not found" << endl;

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

pair<bool, size_t> BinarySearch(vector<int>& v, int x)
{
	if (v.size() == 0) return { false, 0 };
	size_t first = 0;
	size_t last = v.size() - 1;
	while (first <= last) {
		size_t middle = (last - first) / 2 + first;
		if (v[middle] == x) return { true, middle };
		else if (v[middle] > x) last = middle - 1;
		else first = middle + 1;								// v[middle] < x
	}
	return { false, 0 };
}
