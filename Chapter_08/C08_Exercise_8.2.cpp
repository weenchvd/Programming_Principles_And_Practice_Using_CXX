/* Exercise 8.2 */

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

void print(string& label, vector<int>& numbers);

int main()
{
	constexpr int minQuantity = 5;
	constexpr int maxQuantity = 1000;
	constexpr int maxNumber = 100;
	int seed = 0;
	vector<int> numbers;
	cout << "Please enter a number: ";
	cin >> seed;
	srand(seed);
	int nNumbers = randint(minQuantity, maxQuantity);
	for (int i = 0; i < nNumbers; i++) {
		numbers.push_back(randint(maxNumber));
	}
	string label;
	cout << "Please enter the label: ";
	cin >> label;
	print(label, numbers);
	keep_window_open();
	return 0;
}

void print(string& label, vector<int>& numbers)
{
	cout << "Numbers \"" << label << "\" (" << numbers.size() << " ps.):\n";
	for (int x : numbers) {
		cout << x << " ";
	}
	cout << endl;
	return;
}
