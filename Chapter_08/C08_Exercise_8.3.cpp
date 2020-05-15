/* Exercise 8.3 */

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

void print(const string& label, const vector<int>& numbers);
void fibonacci(int x, int y, vector<int>& v, int n);

template<class R, class A> R narrow_cast(const A& a)
{
	R r = R(a);
	if (A(r) != a) error(string("info loss"));
	return r;
}


int main()
try {
	vector<int> fib;
	cout << "Please enter the first number of the Fibonacci sequence: ";
	int firstNumber = 0;
	cin >> firstNumber;
	cout << "Please enter the second number of the Fibonacci sequence: ";
	int secondNumber = 0;
	cin >> secondNumber;
	cout << "Please enter the quantity of numbers of the Fibonacci sequence: ";
	int n = 0;
	cin >> n;
	fibonacci(firstNumber, secondNumber, fib, n);
	print("Fibonacci", fib);
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

void print(const string& label, const vector<int>& numbers)
{
	cout << "Numbers \"" << label << "\" (" << numbers.size() << " ps.):\n";
	for (int x : numbers) {
		cout << x << " ";
	}
	cout << endl;
	return;
}

void fibonacci(int x, int y, vector<int>& v, int n)
{
	if (x < 0) error("The first number must be greater than or equal to 0");
	if (y <= x) error("The second number must be greater than the first number");
	if (n <= 2) error("The quantity of numbers must be greater than 2");
	v.push_back(x);
	v.push_back(y);
	for (int i = 2; i < n; i++) {
		v.push_back(narrow_cast<int>((long long int) v[i - 2] + v[i - 1]));
	}
	return;
}
