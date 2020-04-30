/* Exercise 5.12 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

void error(string s) { throw runtime_error(s); }

int main()
{
	try {
		constexpr int maxNumber = 9999;
		constexpr int minNumber = 0;
		bool answer;
		int i, j, bull, cow, number, temp;
		vector<int>digits = { 3, 6, 1, 8 };
		vector<int>input;
		for (i = 0; i < digits.size(); i++) {
			input.push_back(0);
		}
		answer = false;
		while (answer == false) {
			cout << "Please enter enter a positive 4-digit number: ";
			cin >> number;
			if (!cin || number > maxNumber || number < minNumber) {
				error("Incorrect input\n");
			}
			for (i = 0; i < input.size(); i++) {
				temp = 1;
				for (j = input.size() - i - 1; j > 0; j--) {
					temp *= 10;
				}
				input[i] = (number % (temp * 10)) / temp;
			}
			answer = true;
			bull = cow = 0;
			for (i = 0; i < digits.size(); i++) {
				if (digits[i] == input[i]) {
					bull++;
				}
				else {
					answer = false;
					for (j = 0; j < digits.size(); j++) {
						if (digits[j] == input[i]) {
							cow++;
						}
					}
				}
			}
			if (answer == true) {
				cout << "Yes! This number is ";
				for (int x : digits) {
					cout << x;
				}
				cout << "\n";
			}
			else {
				cout << bull << " bull(s), " << cow << " cow(s)\n";
			}
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
