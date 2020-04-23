/* Exercise 4.2 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	vector<double> temps;
	for (double temp; cin >> temp; ) {
		temps.push_back(temp);
	}
	double sum = 0;
	for (double x : temps) {
		sum += x;
	}
	cout << "Average temperature: " << sum / temps.size() << '\n';
	sort(temps.begin(), temps.end());
	int remainder = temps.size() % 2;
	if (remainder == 1) {
		cout << "Mediane temperature: " << temps[temps.size() / 2] << '\n';
	}
	else {
		cout << "Mediane temperature: " << ((temps[temps.size() / 2] + temps[temps.size() / 2 - 1]) / 2) << '\n';
	}
	return 0;
}
