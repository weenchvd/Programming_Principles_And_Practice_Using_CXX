/* Exercise 3.11 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int penny, nickel, dime, quarter, halfDollar, oneDollar, cent, x;
	cout << "How many pennies do you have? Please enter the number: ";
	cin >> penny;
	cout << "How many nickels do you have? Please enter the number: ";
	cin >> nickel;
	cout << "How many dimes do you have? Please enter the number: ";
	cin >> dime;
	cout << "How many quarters do you have? Please enter the number: ";
	cin >> quarter;
	cout << "How many half dollar coins do you have? Please enter the number: ";
	cin >> halfDollar;
	cout << "How many one-dollar coins do you have? Please enter the number: ";
	cin >> oneDollar;
	cent = 0;
	if (penny > 0) {
		cent += penny;
		cout << "You have " << penny << " penn";
		if (penny == 1) {
			cout << "y\n";
		}
		else {
			cout << "ies\n";
		}
	}
	if (nickel > 0) {
		cent += nickel * 5;
		cout << "You have " << nickel << " nickel";
		if (nickel == 1) {
			cout << '\n';
		}
		else {
			cout << "s\n";
		}
	}
	if (dime > 0) {
		cent += dime * 10;
		cout << "You have " << dime << " dime";
		if (dime == 1) {
			cout << '\n';
		}
		else {
			cout << "s\n";
		}
	}
	if (quarter > 0) {
		cent += quarter * 25;
		cout << "You have " << quarter << " quarter";
		if (quarter == 1) {
			cout << '\n';
		}
		else {
			cout << "s\n";
		}
	}
	if (halfDollar > 0) {
		cent += halfDollar * 50;
		cout << "You have " << halfDollar << " half dollar coin";
		if (halfDollar == 1) {
			cout << '\n';
		}
		else {
			cout << "s\n";
		}
	}
	if (oneDollar > 0) {
		cent += oneDollar * 100;
		cout << "You have " << oneDollar << " one-dollar coin";
		if (oneDollar == 1) {
			cout << '\n';
		}
		else {
			cout << "s\n";
		}
	}
	x = cent % 100;
	cout << "The value of all of your coins is $" << (cent / 100) << '.' << (x / 10) << (x % 10) << '\n';
	return 0;
}
