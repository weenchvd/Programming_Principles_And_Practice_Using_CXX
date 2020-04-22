/* Exercise 3.5 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	double val1, val2;
	cout << "Please enter the floating-point Value 1 and the floating-point Value 2: ";
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
	cout << "\nValue 1 / Value 2 == " << (val1 / val2);
	return 0;
}
