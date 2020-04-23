/* Exercise 4.3 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	vector<double> distances;
	double sum;
	for (double temp; cin >> temp; ) {
		distances.push_back(temp);
	}
	sort(distances.begin(), distances.end());
	sum = 0;
	for (double temp : distances) {
		sum += temp;
	}
	cout << "Total distance: " << sum << '\n';
	cout << "The smallest distance between two neighboring cities: " << distances[0] << '\n';
	cout << "The greatest distance between two neighboring cities: " << distances[distances.size() - 1] << '\n';
	cout << "The mean distance between two neighboring cities: " << sum / distances.size() << '\n';
	return 0;
}
