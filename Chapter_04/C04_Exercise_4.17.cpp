/* Exercise 4.17 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int i, modeCount, currentCount;
	vector<string> word;
	string temp, modeWord, currentWord;
	string message = "Please enter a word or press Ctrl + Z, then press Enter to end the input: ";
	cout << message;
	while (cin >> temp) {
		word.push_back(temp);
		cout << message;
	}
	sort(word.begin(), word.end());
	modeWord = currentWord = " ";
	modeCount = currentCount = 0;
	for (i = 0; i < word.size(); i++) {
		if (word[i] == currentWord) {
			currentCount++;
		}
		else {
			currentWord = word[i];
			currentCount = 1;
		}
		if (currentCount > modeCount) {
			modeWord = currentWord;
			modeCount = currentCount;
		}
	}
	if (word.size() > 0) {
		cout << "Min word: " << word[0] << "\nMax word: " << word[word.size() - 1] << "\n";
		cout << "Mode (" << modeCount << " time(s)): " << modeWord << "\n";
	}
	else {
		cout << "You didn't enter anything\n";
	}
	return 0;
}
