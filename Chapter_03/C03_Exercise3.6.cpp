/* Exercise 3.6 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int val1, val2, val3, x;
	cout << "Please enter the integer Value 1, the integer Value 2 and the integer Value 3: ";
	cin >> val1 >> val2 >> val3;
	cout << '\n';
	if (val1 > val2) {
		x = val1;
		val1 = val2;
		val2 = x;
	}
	if (val1 > val3) {
		x = val1;
		val1 = val3;
		val3 = x;
	}
	if (val2 > val3) {
		x = val2;
		val2 = val3;
		val3 = x;
	}
	cout << val1 << ", " << val2 << ", " << val3;
	return 0;
}
