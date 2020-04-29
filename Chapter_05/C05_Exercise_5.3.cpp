/* Exercise 5.3 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

double ctok(double c);

int main()
{
	constexpr double absoluteZeroCel = -273.15;
	double c, k;
	c = 0;
	cout << "Please enter a temperature value in Celsius: ";
	cin >> c;
	if (c >= absoluteZeroCel) {
		k = ctok(c);
		cout << k << "\n";
	}
	else {
		cout << "The temperature value must be greater or equal than " << absoluteZeroCel << "\n";
	}
	return 0;
}

double ctok(double c)
{
	return c + 273.15;
}