/* Exercise 4.10 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int i, input;
	vector<int>number = { 2, 1, 3, 2, 3, 1, 2, 3, 1, 3, 2 };
	vector<string>action = { "Rock", "Paper", "Scissors" };
	cout << "Let's play \"Rock, Paper, Scissors\"\n";
	cout << "Press Ctrl + Z and then press Enter to exit\n";
	cout << "Please enter the number from 1 to 9: ";
	i = 0;
	while (cin >> input) {
		if (input >= 1 && input <= 9) {
			cout << action[((number[i] + input) * 13 + input) % 3] << "\n";
			i++;
			if (i >= number.size()) {
				i = 0;
			}
			cout << "Please enter the number from 1 to 9: ";
		}
		else {
			cout << "Incorrect input\n";
		}
	}
	return 0;
}
