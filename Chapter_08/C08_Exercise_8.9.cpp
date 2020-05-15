/* Exercise 8.9 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }
inline int randint(int max) { return rand() % max; }
inline int randint(int min, int max) { return randint(max - min) + min; }

void print(const vector<double>& v1, const vector<double>& v2);
double index(const vector<double>& v1, const vector<double>& v2);


int main()
{
	constexpr int minQuantity = 5;
	constexpr int maxQuantity = 20;
	constexpr int max = 100;
	int seed = 0;
	vector<double> price;
	vector<double> weight;
	cout << "Please enter a number: ";
	cin >> seed;
	srand(seed);
	int nNumbers = randint(minQuantity, maxQuantity);
	for (int i = 0; i < nNumbers; i++) {
		price.push_back((double) randint(max, max * max) / max);
		weight.push_back(randint(5, max / 2));
	}
	cout << "Price Weight:\n";
	print(price, weight);
	cout << "Index: " << index(price, weight) << endl;
	keep_window_open();
	return 0;
}

void print(const vector<double>& v1, const vector<double>& v2)
{
	if (v1.size() != v2.size()) return;
	for (int i = 0; i < v1.size(); i++) {
		cout << v1[i] << " " << v2[i] << endl;
	}
	return;
}

double index(const vector<double>& v1, const vector<double>& v2)
{
	if (v1.size() != v2.size()) return 0;
	double index = 0;
	for (int i = 0; i < v1.size(); i++) {
		index = index + v1[i] * v2[i];
	}
	return index;
}
