/* Exercise 4.4 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int first, last, median;
	string answer;
	cout << "Guess a number from 1 to 100\n";
	first = 1;
	last = 100;
	for (int i = 0; i < 7; ++i) {
		if ((first + last) % 2 == 0) {
			median = (first + last) / 2;
		}
		else {
			median = (first + last) / 2 + 1;
		}
		cout << "Is the number you are thinking of less than " << median << "? 'yes' or 'no'\n";
		cin >> answer;
		if (answer == "yes") {
			last = median - 1;
		}
		else if (answer == "no") {
			first = median;
		}
		else {
			cout << "Please use only 'yes' or 'no'\n";
			--i;
		}
	}
	cout << "The number you guessed is " << first << '\n';
	return 0;
}
