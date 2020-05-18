/* Exercise 8.12 */

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
void print_until_s(const vector<string>& v, const string& quit);
void print_until_ss(const vector<string>& v, const string& quit);

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
	passwords.push_back(passwords[1]);
	print("passwords", passwords);
	cout << "print_until_s(): quit == " << passwords[passwords.size() - 2] << endl;
	print_until_s(passwords, passwords[passwords.size() - 2]);
	cout << "print_until_s(): quit == xyzXYZ" << endl;
	print_until_s(passwords, "xyzXYZ");
	cout << "print_until_ss(): quit == " << passwords[1] << endl;
	print_until_ss(passwords, passwords[1]);
	cout << "print_until_ss(): quit == " << passwords[0] << endl;
	print_until_ss(passwords, passwords[0]);
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

void print_until_s(const vector<string>& v, const string& quit)
{
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == quit) return;
		cout << "    " << v[i] << '\n';
	}
}

void print_until_ss(const vector<string>& v, const string& quit)
{
	int counter = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == quit) {
			if (counter > 0) {
				return;
			}
			counter++;
		}
		cout << "      " << v[i] << '\n';
	}
}
