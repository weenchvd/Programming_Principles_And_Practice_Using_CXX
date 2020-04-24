/* Exercise 4.9 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int nSquares, currentSquare, currentGrain;
	double currentGrain2;
	cout << "Please enter the number of squares: ";
	cin >> nSquares;
	cout << "\n";
	if (nSquares < 0) {
		cout << "Incorrect input\n";
		return -1;
	}
	if (nSquares == 0) {
		currentGrain2 = 0;
	}
	else {
		currentGrain2 = pow(2, nSquares) - 1;
	}
	// max 1023 squares
	cout << "You will get " << currentGrain2;
	if (currentGrain2 == 1) {
		cout << " grain (double)\n";
	}
	else {
		cout << " grains (double)\n";
	}
	if (nSquares == 0) {
		currentGrain = 0;
	}
	else {
		currentSquare = 1;
		currentGrain = 1;
		while (currentSquare <= nSquares) {
			currentGrain *= 2;
			++currentSquare;
		}
		currentGrain -= 1;
	}
	// max 31 square
	cout << "You will get " << currentGrain;
	if (currentGrain == 1) {
		cout << " grain (integer)\n";
	}
	else {
		cout << " grains (integer)\n";
	}
	return 0;
}
