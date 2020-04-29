/* Exercise 5.6 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

constexpr double absoluteZeroCel = -273.15;
constexpr double absoluteZeroFahr = 9.0 / 5 * absoluteZeroCel + 32;
constexpr double errorCToF = absoluteZeroCel - 1;
constexpr double errorFToC = absoluteZeroFahr - 1;

using namespace std;

double ctof(double cel);
double ftoc(double fahr);

int main()
{
	double val, cel, fahr;
	char ch;
	val = 0;
	ch = ' ';
	cout << "Please enter a temperature value in Celsius as 'valueC' (example, '24C') or\n"
		"enter a temperature value in Fahrenheit as 'valueF' (example, '-140F'): ";
	cin >> val >> ch;
	if (!cin) {
		cout << "Incorrect input\n";
		return -1;
	}
	if (ch == 'C') {
		if ((fahr = ctof(val)) != errorCToF) {
			cout << "  " << fahr << "F\n";
		}
	}
	else if (ch == 'F') {
		if ((cel = ftoc(val)) != errorFToC) {
			cout << "  " << cel << "C\n";
		}
	}
	else {
		cout << "Unknown unit of measurement\n";
	}
	return 0;
}

double ctof(double cel)
{
	if (cel >= absoluteZeroCel) {
		return 9.0 / 5 * cel + 32;
	}
	else {
		cout << "The temperature value must be greater than or equal to absolute zero (" << absoluteZeroCel << "C)\n";
		return errorCToF;
	}
}

double ftoc(double fahr)
{
	if (fahr >= absoluteZeroFahr) {
		return (fahr - 32) * 5 / 9;
	}
	else {
		cout << "The temperature value must be greater than or equal to absolute zero (" << absoluteZeroFahr << "F)\n";
		return errorFToC;
	}
}