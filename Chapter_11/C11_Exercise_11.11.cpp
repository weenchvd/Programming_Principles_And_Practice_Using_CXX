﻿/* Exercise 11.11 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"C11_Exercise_11.11.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

const string errMessageInputFile = "Error. Can't open input file: ";
const string errMessageOutputFile = "Error. Can't open output file: ";

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		SPLIT
	};
	const string actionList = "\tList of actions:\n"
	"  (1) split()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case SPLIT: {
			//string w = { ".,:;'\"?!/|\\<>(){}[]~`@#$%^&*-_=+" };
			string w = { ".,:;\"?!/|\\<>(){}[]-" };
			string s;
			while (s.size() == 0) getline(cin, s);
			if (!cin) error("Bad input");;
			cout << "\nResult:\n";
			vector<string> substrings = split(s, w);
			for (string& x : substrings) {
				cout << x << endl;
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

vector<string> split(const string& s, const string& w)
{
	vector<string> substrings;
	string word;
	for (int i = 0; i < s.size(); i++) {
		if (isspace(s[i]) || IsPunctuationCharacter(s[i], w)) {
			if (word.size() > 0) {
				substrings.push_back(word);
				word.clear();
			}
		}
		else word += s[i];
	}
	if (word.size() > 0) {
		substrings.push_back(word);
	}
	return substrings;
}

bool IsPunctuationCharacter(const char c, const string& w)
{
	for (char ch : w) {
		if (c == ch) return true;
	}
	return false;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
