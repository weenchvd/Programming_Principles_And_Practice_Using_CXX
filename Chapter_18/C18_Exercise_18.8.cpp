/* Exercise 18.8 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C18_Exercise_18.8.h"

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
		PALSTRING, PALARRAY, PALPOINTER
	};
	const string actionList = "\tList of actions:\n"
	"  (1) is_palindrome(const string&), (2) is_palindrome(const char[], int), (3) is_palindrome(const char*, const char*)\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	const char* space2 = "  ";
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case PALSTRING: {
			cout << "\nPlease enter a string in English (only ASCII): ";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			cout << s << " is";
			if (!is_palindrome(s)) cout << " not";
			cout << " a palindrome" << endl;
			break;
		}
		case PALARRAY: {
			constexpr int maxSize = 100;
			cout << "\nPlease enter a word in English (only ASCII): ";
			char as[maxSize];
			if (!read_word(cin, as, maxSize)) error("Error. Incorrect input");
			
			cout << as << " is";
			if (!is_palindrome(as, strlen(as))) cout << " not";
			cout << " a palindrome" << endl;
			break;
		}
		case PALPOINTER: {
			cout << "\nPlease enter a string in English (only ASCII): ";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cs = new char[s.size() + 1];
			int i;
			for (i = 0; i < s.size(); i++) cs[i] = s[i];
			cs[i] = '\0';

			cout << s << " is";
			if (!is_palindrome(cs, cs + s.size() - 1)) cout << " not";
			cout << " a palindrome" << endl;
			delete[] cs;
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

bool is_palindrome(const string& s)
{
	int i = s.length() - 1;
	string reverse;
	while (i >= 0) reverse += s[i--];
	for (i = 0; i < s.length(); i++) {
		if (s[i] != reverse[i]) return false;
	}
	return true;
}

bool is_palindrome(const char s[], int n)
// s points to the first character of an array of n characters
{
	int i = n - 1;
	char* reverse = new char[n];
	for (int j = 0; j < n; j++) reverse[j] = s[i--];
	for (i = 0; i < n; i++) {
		if (s[i] != reverse[i]) {
			delete[] reverse;
			return false;
		}
	}
	delete[] reverse;
	return true;
}

istream& read_word(istream& is, char* buffer, int max)
// read at most max–1 characters from is into buffer
{
	is.width(max);		// read at most max–1 characters in the next >>
	is >> buffer;		// read whitespace-terminated word,
						// add zero after the last character read into buffer
	return is;
}

bool is_palindrome(const char* first, const char* last)
// first points to the first letter, last to the last letter
{
	int n = last - first + 1;
	char* reverse = new char[n];
	char* pReverse = reverse;
	for (char* p = const_cast<char*>(last); p >= first; p--) *pReverse++ = *p;
	pReverse = reverse;
	while (first <= last) {
		if (*first != *pReverse) {
			delete[] reverse;
			return false;
		}
		first++;
		pReverse++;
	}
	delete[] reverse;
	return true;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
