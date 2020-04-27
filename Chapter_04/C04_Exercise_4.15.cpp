/* Exercise 4.15 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	constexpr int averageNumberPrimesInTen = 2;
	constexpr int ratio = 10 / averageNumberPrimesInTen;
	int i, j, x, y, nPrimes, lastNumber, count;
	bool proceed;
	vector<bool> primes;
	cout << "Please enter the number of first Prime numbers: ";
	cin >> nPrimes;
	count = 0;
	lastNumber = 0;
	while (count < nPrimes) {
		lastNumber = lastNumber + (nPrimes - count) * ratio;
		for (i = 0; i <= lastNumber; i++) {
			primes.push_back(true);
		}
		x = sqrt(lastNumber);
		for (i = 2; i <= x; i++) {
			if (primes[i] == true) {
				for (j = i * i, y = 0; j <= lastNumber; j = i * i + ++y * i) {
					primes[j] = false;
				}
			}
		}
		count = 0;
		for (i = 2; i <= lastNumber; i++) {
			if (primes[i] == true) {
				count++;
			}
		}
	}
	cout << "The first Prime numbers:\n  ";
	count = 0;
	for (i = 2; count < nPrimes && i <= lastNumber; i++) {
		if (primes[i] == true) {
			cout << i << " ";
			count++;
		}
	}
	return 0;
}
