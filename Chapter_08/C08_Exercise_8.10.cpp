/* Exercise 8.10 */

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

void print(const vector<int>& v);
int maxv(const vector<int>& v);


int main()
{
	constexpr int minQuantity = 5;
	constexpr int maxQuantity = 20;
	constexpr int max = 100;
	int seed = 0;
	vector<int> numbers;
	cout << "Please enter a number: ";
	cin >> seed;
	srand(seed);
	int nNumbers = randint(minQuantity, maxQuantity);
	for (int i = 0; i < nNumbers; i++) {
		numbers.push_back(randint(max));
	}
	cout << "Numbers:\n";
	print(numbers);
	int element = maxv(numbers);
	if (element >= 0) {
		cout << "Max: " << numbers[element] << endl;
	}
	keep_window_open();
	return 0;
}

void print(const vector<int>& v)
{
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
	return;
}

int maxv(const vector<int>& v)
{
	int max = INT_MIN;
	int element = -1;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] > max) {
			max = v[i];
			element = i;
		}
	}
	return element;
}
