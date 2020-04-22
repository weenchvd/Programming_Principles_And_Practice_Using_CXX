/* Exercise 3.9 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	string num;
	int x;
	cout << "Please enter a number as a word: ";
	cin >> num;
	cout << '\n';
	x = -1;
	if (num == "zero") {
		x = 0;
	}
	if (num == "one") {
		x = 1;
	}
	if (num == "two") {
		x = 2;
	}
	if (num == "three") {
		x = 3;
	}
	if (num == "four") {
		x = 4;
	}
	if (x == -1) {
		cout << "not a number I know\n";
	}
	else {
		cout << "Digit: " << x << '\n';
	}
	return 0;
}
