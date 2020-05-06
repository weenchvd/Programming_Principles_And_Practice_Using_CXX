/* Exercise 6.8 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

void error(string s) { throw runtime_error(s); }
inline int randint(int max) { return rand() % max; }
inline int randint(int min, int max) { return randint(max - min) + min; }

int main()
{
	try {
		constexpr char firstChar = 'a';
		constexpr char lastChar = 'z';
		constexpr int nLetters = 4;
		bool play, answer, cond, incInput;
		char ch;
		int i, j, bull, cow, seed;
		vector<char>letters(nLetters);
		vector<char>input(nLetters);
		cout << "Please enter '~' to exit\n";
		cout << "Please enter a number to start the game: ";
		cin >> seed;
		srand(seed);
		play = true;
		while (play) {
			cout << "\n\nThe new game\n";
			for (i = 0; i < letters.size(); i++) {
				cond = true;
				while (cond == true) {
					cond = false;
					ch = randint(firstChar, lastChar);
					for (j = 0; j < i; j++) {
						if (ch == letters[j]) {
							cond = true;
						}
					}
				}
				letters[i] = ch;
			}
			answer = false;
			while (answer == false) {
				cond = true;
				while (cond == true) {
					cond = false;
					cout << "Please enter 4 different letters from 'a' to 'z': ";
					for (i = 0; i < input.size(); i++) {
						ch = '\0';
						cin >> ch;
						if (ch == '~') {
							cond = false;
							play = false;
							break;
						}
						incInput = false;
						if (ch == '\0' || ch < 'a' || ch > 'z') {
							incInput = true;
						}
						if (incInput == false) {
							for (j = 0; j < i; j++) {
								if (ch == input[j]) {
									incInput = true;
									break;
								}
							}
						}
						if (incInput == true) {
							cond = true;
							cout << "Incorrect input\n";
							break;
						}
						input[i] = ch;
					}
				}
				if (play == false) {
					break;
				}
				answer = true;
				bull = cow = 0;
				for (i = 0; i < letters.size(); i++) {
					if (letters[i] == input[i]) {
						bull++;
					}
					else {
						answer = false;
						for (j = 0; j < letters.size(); j++) {
							if (letters[j] == input[i]) {
								cow++;
							}
						}
					}
				}
				if (answer == true) {
					cout << "Yes! '";
					for (char x : letters) {
						cout << x;
					}
					cout << "'is the correct answer\n";
				}
				else {
					cout << bull << " bull(s), " << cow << " cow(s)\n";
				}
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
