/* Exercise 4.8 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int nSquares, targetGrain, currentGrain, currentSquare;
	cout << "Please enter the number of grains: ";
	cin >> targetGrain;
	cout << "\n";
	nSquares = 0;
	currentGrain = 0;
	if (currentGrain < targetGrain) {
		++nSquares;
		currentSquare = 1;
		currentGrain = currentSquare;
	}
	while (currentGrain < targetGrain) {
		++nSquares;
		currentSquare *= 2;
		currentGrain = currentGrain + currentSquare;
	}
	cout << "You will need " << nSquares;
	if (nSquares == 1) {
		cout << " square\n";
	}
	else {
		cout << " squares\n";
	}
	return 0;
}
