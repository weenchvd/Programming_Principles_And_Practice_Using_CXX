/* Exercise 4.18 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	double a, b, c, d, dRoot, solution1, solution2;
	cout << "ax^2 + bx + c = 0\n";
	cout << "Please enter the 'a': ";
	cin >> a;
	cout << "Please enter the 'b': ";
	cin >> b;
	cout << "Please enter the 'c': ";
	cin >> c;
	d = b * b - 4 * a * c;
	if (d > 0) {
		dRoot = sqrt(d);
		solution1 = (0 - b + dRoot) / 2 * a;
		solution2 = (0 - b - dRoot) / 2 * a;
		cout << "  Root #1: " << solution1 << "\n  Root #2: " << solution2 << "\n";
	}
	else if (d == 0) {
		solution1 = solution2 = 0 - b / 2 * a;
		cout << "  Root #1: " << solution1 << "\n  Root #2: " << solution2 << "\n";
	}
	else {
		cout << "  Equality has no roots\n";
	}
	return 0;
}
