/* Exercise 3.4 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int val1, val2;
	double ratio;
	cout << "Please enter Value 1 and Value 2: ";
	cin >> val1 >> val2;
	cout << '\n';
	if (val1 == val2) {
		cout << "Value 1 == Value 2\n";
	}
	else if (val1 < val2) {
		cout << "Value 1 < Value 2\n";
	}
	else {
		cout << "Value 1 > Value 2\n";
	}
	cout << "Value 1 + Value 2 == " << (val1 + val2);
	cout << "\nValue 1 - Value 2 == " << (val1 - val2);
	cout << "\nValue 1 * Value 2 == " << (val1 * val2);
	ratio = val1;
	ratio /= val2;
	cout << "\nValue 1 / Value 2 == " << ratio;
	return 0;
}
