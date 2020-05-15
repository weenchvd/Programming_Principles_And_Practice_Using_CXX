/* Exercise 8.5 */

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

void print(const string& label, const vector<int>& numbers);
vector<int> ReverseNew(const vector<int>& v);
void Reverse(vector<int>& v);

int main()
{
	constexpr int minQuantity = 5;
	constexpr int maxQuantity = 20;
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
	print("numbers", numbers);
	vector<int> r = ReverseNew(numbers);
	print("numbers after ReverseNew", numbers);
	print("r after ReverseNew", r);
	Reverse(numbers);
	print("numbers after Reverse", numbers);
	keep_window_open();
	return 0;
}

void print(const string& label, const vector<int>& numbers)
{
	cout << "Numbers \"" << label << "\" (" << numbers.size() << " ps.):\n";
	for (int x : numbers) {
		cout << x << " ";
	}
	cout << endl;
	return;
}

vector<int> ReverseNew(const vector<int>& v)
{
	vector<int> n;
	for (int i = v.size() - 1; i >= 0; i--) {
		n.push_back(v[i]);
	}
	return n;
}

void Reverse(vector<int>& v)
{
	for (int i = 0, j = v.size() - 1; i < v.size() / 2; i++, j--) {
		swap(v[i], v[j]);
	}
	return;
}
