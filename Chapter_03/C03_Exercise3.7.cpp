/* Exercise 3.7 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	string w1, w2, w3, x;
	cout << "Please enter Word 1, Word 2 and Word 3: ";
	cin >> w1 >> w2 >> w3;
	cout << '\n';
	if (w1 > w2) {
		x = w1;
		w1 = w2;
		w2 = x;
	}
	if (w1 > w3) {
		x = w1;
		w1 = w3;
		w3 = x;
	}
	if (w2 > w3) {
		x = w2;
		w2 = w3;
		w3 = x;
	}
	cout << w1 << ", " << w2 << ", " << w3;
	return 0;
}
