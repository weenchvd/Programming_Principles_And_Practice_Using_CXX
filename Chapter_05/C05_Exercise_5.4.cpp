/* Exercise 5.4 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

constexpr double absoluteZeroCel = -273.15;
constexpr double errorCToK = -300;

using namespace std;

double ctok(double c);

int main()
{
	double c, k;
	c = 0;
	cout << "Please enter a temperature value in Celsius: ";
	cin >> c;
	if ((k = ctok(c)) != errorCToK) {
		cout << k << "\n";
	}
	return 0;
}

double ctok(double c)
{
	
	if (c >= absoluteZeroCel) {
		return c + 273.15;
	}
	else {
		cout << "The temperature value must be greater or equal than " << absoluteZeroCel << "\n";
		return errorCToK;
	}
}