/* Exercise 3.2 | Miles To Kilometers */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	double miles;
	cout << "Please enter the number of miles: ";
	cin >> miles;
	cout << miles << " mile(s) equals " << (miles * 1.609) << " kilometer(s)\n";
	return 0;
}
