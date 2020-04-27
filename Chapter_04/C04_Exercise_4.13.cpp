/* Exercise 4.13 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int i, j, x, y, lastNumber;
	vector<bool> primes;
	lastNumber = 100;
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
	cout << "Prime numbers from 1 to " << lastNumber << ":\n  ";
	for (i = 2; i <= lastNumber; i++) {
		if (primes[i] == true) {
			cout << i << " ";
		}
	}
	return 0;
}
