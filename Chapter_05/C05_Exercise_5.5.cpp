/* Exercise 5.5 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

constexpr double absoluteZeroCel = -273.15;
constexpr double absoluteZeroKel = 0;
constexpr double errorCToK = -300;
constexpr double errorKToC = -1;

using namespace std;

double ctok(double cel);
double ktoc(double kel);

int main()
{
	double val, cel, kel;
	char ch;
	val = 0;
	ch = ' ';
	cout << "Please enter a temperature value in Celsius as 'valueC' (example, '24C') or\n"
		"enter a temperature value in Kelvin as 'valueK' (example, '-245K'): ";
	cin >> val >> ch;
	if (!cin) {
		cout << "Incorrect input\n";
		return -1;
	}
	if (ch == 'C') {
		if ((kel = ctok(val)) != errorCToK) {
			cout << "  " << kel << "K\n";
		}
	}
	else if (ch == 'K') {
		if ((cel = ktoc(val)) != errorKToC) {
			cout << "  " << cel << "C\n";
		}
	}
	else {
		cout << "Unknown unit of measurement\n";
	}
	return 0;
}

double ctok(double cel)
{
	if (cel >= absoluteZeroCel) {
		return cel + 273.15;
	}
	else {
		cout << "The temperature value must be greater than or equal to absolute zero (" << absoluteZeroCel << "C)\n";
		return errorCToK;
	}
}

double ktoc(double kel)
{
	if (kel >= absoluteZeroKel) {
		return kel - 273.15;
	}
	else {
		cout << "The temperature value must be greater than or equal to absolute zero (" << absoluteZeroKel << "K)\n";
		return errorKToC;
	}
}
