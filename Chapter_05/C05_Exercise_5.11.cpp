/* Exercise 5.11 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	bool proceed;
	int number, prev, temp;
	long long int numberL;
	number = prev = 1;
	cout << "Fibonacci numbers:\n" << prev << " " << number << " ";
	proceed = true;
	while (proceed == true) {
		temp = number;
		numberL = (long long int)number + prev;
		number += prev;
		prev = temp;
		if (numberL != number) {
			proceed = false;
		}
		else {
			cout << number << " ";
		}
	}
	return 0;
}
