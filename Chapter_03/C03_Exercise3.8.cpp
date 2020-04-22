/* Exercise 3.8 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int num, x;
	cout << "Please enter an integer number: ";
	cin >> num;
	cout << '\n';
	x = num % 2;
	if (x == 1) {
		cout << "The number " << num << " is an odd number\n";
	}
	else {
		cout << "The number " << num << " is an even number\n";
	}
	return 0;
}
