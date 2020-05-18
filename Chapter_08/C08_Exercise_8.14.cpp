/* Exercise 8.14 */

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
bool IsGreater(const vector<int>& v, const int value);
int Largest(const vector<int>& v);


int main()
{
	constexpr int minQuantity = 5;
	constexpr int maxQuantity = 20;
	constexpr int max = 100;
	constexpr int value1 = 57;
	constexpr int value2 = max + 1;
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
	cout << value1 << " is greater than each element in 'numbers': ";
	cout << ((IsGreater(numbers, value1)) ? "true" : "false") << endl;
	cout << value2 << " is greater than each element in 'numbers': ";
	cout << ((IsGreater(numbers, value2)) ? "true" : "false") << endl;
	int largest = Largest(numbers);
	cout << numbers[largest] << " is greater than each element in 'numbers': ";
	cout << ((IsGreater(numbers, numbers[largest])) ? "true" : "false") << endl;
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

/* whether is the 'value' greater than each element in 'v' */
bool IsGreater(const vector<int>& v, const int value)
{
	for (int i = 0; i < v.size(); i++) {
		if (v[i] >= value) return false;
	}
	return true;
}

int Largest(const vector<int>& v)
{
	int element = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] > v[element]) element = i;
	}
	return element;
}
