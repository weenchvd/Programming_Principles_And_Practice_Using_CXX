/* Exercise 3.10 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	string operation;
	double val1, val2, result;
	bool x;
	cout << "Please enter an operation followed by two operands: ";
	cin >> operation >> val1 >> val2;
	x = false;
	if (operation == "+") {
		result = val1 + val2;
		x = true;
	}
	if (operation == "plus") {
		result = val1 + val2;
		x = true;
	}
	if (operation == "-") {
		result = val1 - val2;
		x = true;
	}
	if (operation == "minus") {
		result = val1 - val2;
		x = true;
	}
	if (operation == "*") {
		result = val1 * val2;
		x = true;
	}
	if (operation == "mul") {
		result = val1 * val2;
		x = true;
	}
	if (operation == "/") {
		result = val1 / val2;
		x = true;
	}
	if (operation == "div") {
		result = val1 / val2;
		x = true;
	}
	if (x == true) {
		cout << "Result: " << result << '\n';
	}
	else {
		cout << "Unknown operation\n";
	}
	return 0;
}
