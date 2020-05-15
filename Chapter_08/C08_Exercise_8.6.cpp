/* Exercise 8.6 */

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
vector<string> ReverseNew(const vector<string>& v);
void Reverse(vector<string>& v);

int main()
{
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
	vector<string> r = ReverseNew(passwords);
	print("passwords after ReverseNew", passwords);
	print("r after ReverseNew", r);
	Reverse(passwords);
	print("passwords after Reverse", passwords);
	keep_window_open();
	return 0;
}

void print(const string& label, const vector<string>& s)
{
	cout << "Strings \"" << label << "\" (" << s.size() << " ps.):\n";
	for (string x : s) {
		cout << "  " << x << endl;
	}
	return;
}

vector<string> ReverseNew(const vector<string>& v)
{
	vector<string> n;
	for (int i = v.size() - 1; i >= 0; i--) {
		n.push_back(v[i]);
	}
	return n;
}

void Reverse(vector<string>& v)
{
	for (int i = 0, j = v.size() - 1; i < v.size() / 2; i++, j--) {
		swap(v[i], v[j]);
	}
	return;
}
