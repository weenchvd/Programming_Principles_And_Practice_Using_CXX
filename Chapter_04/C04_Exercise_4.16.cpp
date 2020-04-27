/* Exercise 4.16 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int i, temp, modeNumber, modeCount, currentNumber, currentCount;
	vector<int> number;
	string message = "Please enter a number or enter \"|\" to end the input: ";
	cout << message;
	while (cin >> temp) {
		number.push_back(temp);
		cout << message;
	}
	sort(number.begin(), number.end());
	modeNumber = 0;
	modeCount = 0;
	currentNumber = 0;
	currentCount = 0;
	for (i = 0; i < number.size() && number[i] <= 0; i++);
	for ( ; i < number.size(); i++) {
		if (number[i] == currentNumber) {
			currentCount++;
		}
		else {
			currentNumber = number[i];
			currentCount = 1;
		}
		if (currentCount > modeCount) {
			modeNumber = currentNumber;
			modeCount = currentCount;
		}
	}
	if (number.size() > 0) {
		if (modeCount > 0) {
			cout << "Min number: " << number[0] << "\nMax number: " << number[number.size() - 1] << "\n";
			cout << "Mode (" << modeCount << " time(s)): " << modeNumber << "\n";
		}
		else {
			cout << "You didn't enter positive numbers\n";
		}
	}
	else {
		cout << "You didn't enter anything\n";
	}
	return 0;
}
