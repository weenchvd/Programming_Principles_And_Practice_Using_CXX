/* Exercise 6.10 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

void error(string s) { throw runtime_error(s); }

long double CalculatePermutation(int possible, int different);
long double CalculateCombination(int possible, int different);
long double Factorial(int val);

int main()
{
	try {
		int action, possible, different;
		string errorMessage = "Incorrect input\n";
		action = 0;
		cout << "Please enter the action:\n(1) to calculate the permutation\n(2) to calculate the combination\n";
		cin >> action;
		possible = different = 0;
		switch (action) {
		case 1:
			cout << "Please enter quantity of possible numbers for the permutation: ";
			cin >> possible;
			cout << "Please enter quantity of different numbers for the permutation: ";
			cin >> different;
			if (possible == 0 || different == 0) {
				error(errorMessage);
			}
			cout << "  Number of permutation P(" << possible << "," << different << "): ";
			cout << CalculatePermutation(possible, different);
			break;
		case 2:
			cout << "Please enter quantity of possible numbers for the combination: ";
			cin >> possible;
			cout << "Please enter quantity of different numbers for the combination: ";
			cin >> different;
			if (possible == 0 || different == 0) {
				error(errorMessage);
			}
			cout << "  Number of combination C(" << possible << "," << different << "): ";
			cout << CalculateCombination(possible, different);
			break;
		default:
			error(errorMessage);
			break;
		}
		return 0;
	}
	catch (runtime_error& e) {
		cerr << "\n\t| RUNTIME ERROR | " << e.what() << "\n";
		return -1;
	}
	catch (...) {
		cerr << "\n\t| UNKNOWN EXCEPTION |\n";
		return -2;
	}
}

/*	'possible' - quantity of possible numbers for the permutation;
	'different' - quantity of different numbers for the permutation */
long double CalculatePermutation(int possible, int different)
{
	if (different < 1) {
		error("CalculatePermutation(): quantity of different numbers for the permutation must be"
			" greater than 0");
	}
	else if (possible < different) {
		error("CalculatePermutation(): quantity of possible numbers for the permutation must be"
			" greater than or equal to quantity of different numbers for the permutation");
	}
	else {
		return Factorial(possible) / Factorial(possible - different);
	}
}

/*	'possible' - quantity of possible numbers for the combination;
	'different' - quantity of different numbers for the combination */
long double CalculateCombination(int possible, int different)
{
	return CalculatePermutation(possible, different) / Factorial(different);
}

long double Factorial(int val)
{
	if (val < 0) {
		error("Factorial(): the value must be a positive integer");
	}
	else if (val == 0) {
		return 1;
	}
	else {
		long double number = val;
		for (int i = val - 1; i > 1; i--) {
			number *= i;
		}
		return number;
	}
}
