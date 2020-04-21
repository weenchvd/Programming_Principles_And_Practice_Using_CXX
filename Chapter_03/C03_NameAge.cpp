/* Chapter 3.3 | Name and age */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	cout << "Please enter your first name and age\n";
	string firstName = "???";
	int age = -1;
	cin >> firstName >> age;
	age = age * 12;
	cout << "Hello, " << firstName << " (age " << age << " month(s))\n";
	return 0;
}
