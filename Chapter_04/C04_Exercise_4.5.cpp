/* Exercise 4.5 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	double val1, val2;
	char operation;
	string prompt;
	prompt = "Please enter arguments as: 'value1 value2 operator'\n";
	cout << "Press Ctrl + Z, then press Enter to exit\n" << prompt;
	while (cin >> val1 >> val2 >> operation) {
		switch (operation) {
		case '+':
			cout << "The sum of " << val1 << " and " << val2 << " is " << (val1 + val2) << "\n\n";
			break;
		case '-':
			cout << "The difference of " << val1 << " and " << val2 << " is " << (val1 - val2) << "\n\n";
			break;
		case '*':
			cout << "The product of " << val1 << " and " << val2 << " is " << (val1 * val2) << "\n\n";
			break;
		case '/':
			cout << "The quotient of " << val1 << " and " << val2 << " is " << (val1 / val2) << "\n\n";
			break;
		default:
			cout << "Incorrect input\n";
			break;
		}
		cout << prompt;
	}
	return 0;
}
