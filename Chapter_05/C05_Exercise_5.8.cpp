/* Exercise 5.8 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

void error(string s) { throw runtime_error(s); }

int main()
{
	try {
		int i, n, sum;
		vector<int>number;
		cout << "Please enter the number of values you want to sum: ";
		n = 0;
		if (!(cin >> n)) {
			error("Incorrect input\n");
		}
		if (n <= 0) {
			error("The number of summable values must be greater than 0\n");
		}
		cout << "Please enter some integers (press '|' to stop): ";
		while (cin >> i) {
			number.push_back(i);
		}
		if (n > number.size()) {
			error("The number of summable values is greater than the number of entered values\n");
		}
		else {
			sum = 0;
			cout << "The sum of the first " << n << " numbers ( ";
			for (i = 0; i < n; i++) {
				sum += number[i];
				cout << number[i] << " ";
			}
			cout << ") is " << sum << "\n";
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
