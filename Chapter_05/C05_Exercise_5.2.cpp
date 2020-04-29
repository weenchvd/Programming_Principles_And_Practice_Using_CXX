/* Exercise 5.2 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

double ctok(double c);

int main()
{
	double c, k;
	c = 0;
	cout << "Please enter a temperature value in Celsius: ";
	cin >> c;
	k = ctok(c);
	cout << k << "\n";
	return 0;
}

double ctok(double c)
{
	return c + 273.15;
}