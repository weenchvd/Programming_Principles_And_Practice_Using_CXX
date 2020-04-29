/* Exercise 5.10 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

void error(string s) { throw runtime_error(s); }

template<class R, class A> R narrow_cast(const A& a)
{
	R r = R(a);
	if (A(r) != a) error(string("info loss"));
	return r;
}

int main()
{
	try {
		int i, n;
		double d, sum;
		vector<double>number;
		vector<double>differences;
		cout << "Please enter the number of values you want to sum: ";
		n = 0;
		if (!(cin >> n)) {
			error("Incorrect input\n");
		}
		if (n <= 0) {
			error("The number of summable values must be greater than 0\n");
		}
		cout << "Please enter some floating-point numbers (press '|' to stop): ";
		while (cin >> d) {
			number.push_back(d);
		}
		if (n > number.size()) {
			error("The number of summable values is greater than the number of entered values\n");
		}
		else {
			sum = 0;
			cout << "The sum of the first " << n << " numbers ( ";
			for (i = 0; i < n; i++) {
				sum = narrow_cast<double>((long double)sum + number[i]);
				cout << number[i] << " ";
			}
			cout << ") is " << sum << "\n";
			for (i = 1; i < number.size(); i++) {
				differences.push_back(narrow_cast<double>((long double)number[i - 1] - number[i]));
			}
			cout << "Differences between adjacent values:\n";
			for (i = 0; i < differences.size(); i++) {
				cout << differences[i] << "\n";
			}
		}
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
}
