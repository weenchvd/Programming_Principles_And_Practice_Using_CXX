/* Exercise 6.9 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>

using namespace std;

void error(string s) { throw runtime_error(s); }

constexpr int minNumberDigits = 1;
constexpr int maxNumberDigits = 4;

class Number {
public:
	Number()
		: isNumber(false), integer(0), str("") { }
	bool ReadNumber();
	void PrintNumber();
private:
	bool isNumber;
	int integer;
	string str;
};

int main()
{
	try {
		Number number;
		number.ReadNumber();
		number.PrintNumber();
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

bool Number::ReadNumber()
{
	char ch;
	int i;
	string errorMessage = "Incorrect input\n";
	isNumber = false;
	cout << "Please enter a positive integer number that consists of a maximum of " << maxNumberDigits << " digits: ";
	getline(cin, str);
	if (str.size() < minNumberDigits || str.size() > maxNumberDigits) {
		cout << errorMessage;
		return isNumber;
	}
	integer = 0;
	for (i = 0; i < str.size(); i++) {
		if (str[i] < '0' || str[i] > '9') {
			cout << errorMessage;
			return isNumber;
		}
		integer = integer * 10 + str[i] - '0';
	}
	isNumber = true;
	return isNumber;
}

void Number::PrintNumber()
{
	int i, j;
	vector<string>category = { "thousand(s)", "hundred(s)", "ten(s)", "one(s)" };
	if (isNumber == false) {
		return;
	}
	if (category.size() < str.size()) {
		error("Number::PrintNumber: category.size < str.size");
	}
	cout << "  " << integer << " is ";
	j = category.size() - str.size();
	for (i = 0; i < str.size(); i++) {
		if (i == 0) {
			cout << str[i] << " " << category[j++] << " ";
		}
		else {
			cout << "and " << str[i] << " " << category[j++] << " ";
		}
	}
	cout << "\n";
	return;
}
