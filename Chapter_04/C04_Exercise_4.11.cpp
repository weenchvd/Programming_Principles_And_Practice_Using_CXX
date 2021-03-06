﻿/* Exercise 4.11 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int i, number, lastNumber;
	bool isPrime;
	vector<int> primes = { 2 };
	lastNumber = 100;
	for (number = 3; number <= lastNumber; number++) {
		isPrime = true;
		for (i = 0; i < primes.size(); i++) {
			if (number % primes[i] == 0) {
				isPrime = false;
			}
		}
		if (isPrime == true) {
			primes.push_back(number);
		}
	}
	cout << "Prime numbers from 1 to " << lastNumber << ":\n  ";
	for (i = 0; i < primes.size(); i++) {
		cout << primes[i] << " ";
	}
	return 0;
}
