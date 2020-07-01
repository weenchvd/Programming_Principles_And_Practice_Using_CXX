/* Exercise 11.8 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"C11_Exercise_11.8.h"

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
		MAKEDICTIONARY
	};
	const string actionList = "\tList of actions:\n"
	"  (1) MakeDictionary()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case MAKEDICTIONARY: {
			string inFileName;
			cout << "Please enter the name of input file: ";
			if (!(cin >> inFileName)) { ClearInput(cin); error("Error. Incorrect input"); }
			string outFileName;
			cout << "Please enter the name of output file: ";
			if (!(cin >> outFileName)) { ClearInput(cin); error("Error. Incorrect input"); }
			ifstream ifs;
			ifs.open(inFileName);
			if (!ifs) error(errMessageInputFile, inFileName);
			ofstream ofs;
			ofs.open(outFileName);
			if (!ofs) error(errMessageOutputFile, outFileName);
			MakeDictionary(ifs, ofs);
			ifs.close();
			ofs.close();
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

void MakeDictionary(istream& is, ostream& os)
{
	vector<string> dictionary;
	while (is) {
		string s;
		getline(is, s);
		if (!is) break;
		istringstream iss;
		iss.str(ReplacePunctuation(s));
		for (string word; iss >> word; ) {
			dictionary.push_back(word);
		}
	}
	if (!is.eof()) error("Input failure");
	sort(dictionary.begin(), dictionary.end());
	for (int i = 0; i < dictionary.size(); i++) {
		if (i == 0 || dictionary[i] != dictionary[i - 1]) {
			os << dictionary[i] << endl;
		}
	}
}

string ReplacePunctuation(const string& s)
{
	string ss;
	string word;
	for (int i = 0; i < s.size(); i++) {
		if (isspace(s[i])) {
			if (word.size() > 0) {
				ss += ParseWord(word);
				word.clear();
			}
			ss += s[i];
		}
		else word += tolower(s[i]);
	}
	if (word.size() > 0) {
		ss += ParseWord(word);
	}
	return ss;
}

string ParseWord(const string& w)
{
	string ww;
	for (int i = 0; i < w.size(); i++) {
		if (IsPunctuationCharacter(w[i])) {
			if (w[i] == '-' && i > 0 && isalpha(w[i - 1]) && i + 1 < w.size() && isalpha(w[i + 1])) {
				ww += w[i];
			}
			else if (w[i] == '\'') {
				if (w == "i'm") return "i am";
				if (w == "he's") return "he is";
				if (w == "she's") return "she is";
				if (w == "it's") return "it is";
				if (w == "we're") return "we are";
				if (w == "they're") return "they are";
				if (w == "i've") return "i have";
				if (w == "we've") return "we have";
				if (w == "they've") return "they have";
				if (w == "i'll") return "i will";
				if (w == "we'll") return "we will";
				if (w == "they'll") return "they will";
				if (w == "won't") return "will not";
				if (w == "don't") return "do not";
				if (w == "didn't") return "did not";
				if (w == "can't") return "cannot";
				if (w == "haven't") return "have not";
				if (w == "wouldn't") return "would not";
				ww += ' ';
			}
			else ww += ' ';
		}
		else ww += w[i];
	}
	return ww;
}

bool IsPunctuationCharacter(const char c)
{
	string punctChar = { ".,:;'\"?!/|\\<>(){}[]~`@#$%^&*-_=+" };
	for (char ch : punctChar) {
		if (c == ch) return true;
	}
	return false;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
