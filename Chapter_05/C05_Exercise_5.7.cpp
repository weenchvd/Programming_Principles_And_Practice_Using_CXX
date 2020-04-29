/* Exercise 5.7 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

void PrintRoot(double root1, double root2);

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
		PrintRoot(solution1, solution2);
	}
	else if (d == 0) {
		solution1 = solution2 = 0 - b / 2 * a;
		PrintRoot(solution1, solution2);
	}
	else {
		cout << "  The quadratic equation has no roots\n";
	}
	return 0;
}

void PrintRoot(double root1, double root2)
{
	if (root1 != root2) {
		cout << "  Root #1: " << root1 << "\n  Root #2: " << root2 << "\n";
	}
	else {
		cout << "  Root #1 = Root #2: " << root1 << "\n";
	}
	return;
}
