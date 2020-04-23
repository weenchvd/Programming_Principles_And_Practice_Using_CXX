/* Exercise 4.6 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int GetDigit(string s);

int main()
{
	int digit;
	vector<string> sdigit = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	string input, prompt, error;
	error = "\n\t| ERROR | Incorrect input |\n\n";
	prompt = "Please enter spelled-out value or digit (0-9): ";
	cout << "Press Ctrl + Z, then press Enter to exit\n" << prompt;
	while (cin >> input) {
		if (input.size() == 1) {
			digit = input[0] - '0';
			if (digit >= 0 && digit < sdigit.size()) {
				cout << sdigit[digit] << "\n\n";
			}
			else {
				cout << error;
			}
		}
		else {
			digit = GetDigit(input);
			if (digit != -1) {
				cout << digit << "\n\n";
			}
			else {
				cout << error;
			}
		}
		cout << prompt;
	}
	return 0;
}

int GetDigit(string s)
{
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
		digit = -1;
	}
	return digit;
}
