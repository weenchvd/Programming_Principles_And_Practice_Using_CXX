/* Exercise 4.7 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int ParseInput(string s);
int GetDigit(string s);

int main()
{
	constexpr int error = -1;
	double temp;
	int digit1, digit2;
	char operation;
	string val1, val2;
	string prompt = "Please enter arguments (spelled-out value or digit (0-9)) as: 'value1 value2 operator'\n";
	cout << "Press Ctrl + Z, then press Enter to exit\n" << prompt;
	while (cin >> val1 >> val2 >> operation) {
		digit1 = ParseInput(val1);
		digit2 = ParseInput(val2);
		if (digit1 != error && digit2 != error) {
			switch (operation) {
			case '+':
				cout << "The sum of " << digit1 << " and " << digit2 << " is " << (digit1 + digit2) << "\n\n";
				break;
			case '-':
				cout << "The difference of " << digit1 << " and " << digit2 << " is " << (digit1 - digit2) << "\n\n";
				break;
			case '*':
				cout << "The product of " << digit1 << " and " << digit2 << " is " << (digit1 * digit2) << "\n\n";
				break;
			case '/':
				if (digit2 == 0) {
					cout << "Error. Cannot be divided by 0\n";
					break;
				}
				temp = digit1;
				cout << "The quotient of " << digit1 << " and " << digit2 << " is " << (temp / digit2) << "\n\n";
				break;
			default:
				cout << "Incorrect input\n";
				break;
			}
		}
		cout << prompt;
	}
	return 0;
}

int ParseInput(string s)
{
	constexpr int error = -1;
	int digit;
	string errorMessage = "\n\t| ERROR | Incorrect input |\n\n";
	vector<string> sdigit = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	if (s.size() == 1) {
		digit = s[0] - '0';
		if (digit < 0 || digit >= sdigit.size()) {
			cout << errorMessage;
			digit = error;
		}
	}
	else {
		digit = GetDigit(s);
		if (digit == error) {
			cout << errorMessage;
		}
	}
	return digit;
}

int GetDigit(string s)
{
	constexpr int error = -1;
	int digit;
	if (s == "zero") {
		digit = 0;
	}
	else if (s == "one") {
		digit = 1;
	}
	else if (s == "two") {
		digit = 2;
	}
	else if (s == "three") {
		digit = 3;
	}
	else if (s == "four") {
		digit = 4;
	}
	else if (s == "five") {
		digit = 5;
	}
	else if (s == "six") {
		digit = 6;
	}
	else if (s == "seven") {
		digit = 7;
	}
	else if (s == "eight") {
		digit = 8;
	}
	else if (s == "nine") {
		digit = 9;
	}
	else {
		digit = error;
	}
	return digit;
}
