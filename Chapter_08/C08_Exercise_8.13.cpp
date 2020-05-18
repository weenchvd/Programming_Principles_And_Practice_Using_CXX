/* Exercise 8.13 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }
inline int randint(int max) { return rand() % max; }
inline int randint(int min, int max) { return randint(max - min) + min; }

void print(const string& label, const vector<string>& numbers);
vector<int>& Size(const vector<string>& v, vector<int>& size);
int Longest(const vector<string>& v);
int Shortest(const vector<string>& v);
int FirstLexicographically(const vector<string>& v);
int LastLexicographically(const vector<string>& v);


int main()
try {
	constexpr int minQuantity = 4;
	constexpr int maxQuantity = 9;
	constexpr int firstLetter = 'a';
	constexpr int lastLetter = 'z';
	int seed = 0;
	vector<string> passwords;
	cout << "Please enter a number: ";
	cin >> seed;
	srand(seed);
	int nPasswords = randint(minQuantity, maxQuantity);
	for (int i = 0; i < nPasswords; i++) {
		int nLetters = randint(minQuantity, maxQuantity);
		string s;
		char ch;
		for (int j = 0; j < nLetters; j++) {
			ch = randint(firstLetter, lastLetter);
			s += ch;
		}
		passwords.push_back(s);
	}
	print("passwords", passwords);
	vector<int> size;
	size = Size(passwords, size);
	cout << "Sizes:";
	for (int i = 0; i < size.size(); i++) {
		cout << " " << size[i];
	}
	cout << endl;
	cout << "Longest: " << passwords[Longest(passwords)] << endl;
	cout << "Shortest: " << passwords[Shortest(passwords)] << endl;
	cout << "Lexicographically first: " << passwords[FirstLexicographically(passwords)] << endl;
	cout << "Lexicographically last: " << passwords[LastLexicographically(passwords)] << endl;
	keep_window_open();
	return 0;
}
catch (runtime_error& e) {
	cerr << "\n\t| RUNTIME ERROR | " << e.what() << "\n";
	return -1;
}
catch (...) {
	cerr << "\n\t| UNKNOWN EXCEPTION |\n";
	return -2;
}

void print(const string& label, const vector<string>& v)
{
	cout << "Strings \"" << label << "\" (" << v.size() << " ps.):\n";
	for (int i = 0; i < v.size(); i++) {
		cout << "  " << v[i] << endl;
	}
	return;
}

vector<int>& Size(const vector<string>& v, vector<int>& size)
{
	for (int i = 0; i < v.size(); i++) {
		size.push_back(v[i].size());
	}
	return size;
}

int Longest(const vector<string>& v)
{
	if (v.size() == 0) {
		error("Longest(): vector is empty");
	}
	int longest = 0;
	int element = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].size() > longest) {
			longest = v[i].size();
			element = i;
		}
	}
	return element;
}

int Shortest(const vector<string>& v)
{
	if (v.size() == 0) {
		error("Shortest(): vector is empty");
	}
	int shortest = INT_MAX;
	int element = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].size() < shortest) {
			shortest = v[i].size();
			element = i;
		}
	}
	return element;
}

int FirstLexicographically(const vector<string>& v)
{
	if (v.size() == 0) {
		error("FirstLexicographically(): vector is empty");
	}
	int element = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < v[element]) {
			element = i;
		}
	}
	return element;
}

int LastLexicographically(const vector<string>& v)
{
	if (v.size() == 0) {
		error("LastLexicographically(): vector is empty");
	}
	int element = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] > v[element]) {
			element = i;
		}
	}
	return element;
}
