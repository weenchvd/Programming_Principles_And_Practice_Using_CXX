/* Exercise 8.11 */

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

struct MeanMedianVectorInt {
	int smallest;		// element number, not value
	int largest;		// element number, not value
	double median;		// value
	double mean;		// value
};

void print(const vector<int>& v);
MeanMedianVectorInt MeanMedian(const vector<int>& v);


int main()
try {
	constexpr int minQuantity = 5;
	constexpr int maxQuantity = 20;
	constexpr int max = 100;
	int seed = 0;
	vector<int> numbers;
	cout << "Please enter a number: ";
	cin >> seed;
	srand(seed);
	int nNumbers = randint(minQuantity, maxQuantity);
	for (int i = 0; i < nNumbers; i++) {
		numbers.push_back(randint(max));
	}
	cout << "Numbers (" << numbers.size() << " ps.):\n";
	print(numbers);
	MeanMedianVectorInt meanMedian = MeanMedian(numbers);
	cout << "  Largest: " << numbers[meanMedian.largest] << endl;
	cout << "  Smallest: " << numbers[meanMedian.smallest] << endl;
	cout << "  Mean: " << meanMedian.mean << endl;
	cout << "  Median: " << meanMedian.median << endl;
	keep_window_open();
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

void print(const vector<int>& v)
{
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
	return;
}

MeanMedianVectorInt MeanMedian(const vector<int>& v)
{
	MeanMedianVectorInt r;
	if (v.size() == 0) {
		error("MeanMedian(): vector is empty");
	}
	r.largest = 0;
	r.smallest = 0;
	r.mean = 0;
	int largest = INT_MIN;
	int smallest = INT_MAX;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < smallest) {
			r.smallest = i;
			smallest = v[i];
		}
		if (v[i] > largest) {
			r.largest = i;
			largest = v[i];
		}
		r.mean += v[i];
	}
	r.mean /= v.size();
	int median = v.size() / 2;
	if (v.size() % 2) {
		r.median = v[median];
	}
	else {
		r.median = ((double) v[median] + v[median + 1]) / 2;
	}
	return r;
}
