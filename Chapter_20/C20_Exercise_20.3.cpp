/* Exercise 20.3 */

#include<iostream>
#include<fstream>
#include<istream>
#include<string>
#include<vector>
#include<iomanip>
#include<sstream>
#include<cstdlib>
#include"C20_Exercise_20.3.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		JACKJILL
	};
	const string actionList = "\tList of actions:\n"
	"  (1) JackJill()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case JACKJILL: {
			fct();

			break;
		}
		case PRINTACTIONLIST:
			cout << actionList;
			break;
		case EXIT:
			cond = false;
			break;
		default:
			error("Error. Incorrect action number");
			break;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Error. Exception\n";
		return 1;
	}
	return 0;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}

double* get_from_jack(int* count)
{
	if (!count) return nullptr;
	string file{ "C20_Exercise_20.2_Jack.txt" };
	ifstream ifs;
	ifs.open(file);
	if (!ifs) error("Error. Can't open input file: ", file);
	constexpr int n = 10;
	double* arr = new double[n];
	if (arr) {
		*count = n;
		for (int i = 0; i < n; i++) {
			double temp;
			if (ifs >> temp) arr[i] = temp;
			else {
				delete[] arr;
				return nullptr;
			}
		}
	}
	return arr;
}

vector<double>* get_from_jill()
{
	string file{ "C20_Exercise_20.2_Jill.txt" };
	ifstream ifs;
	ifs.open(file);
	if (!ifs) error("Error. Can't open input file: ", file);
	constexpr int n = 10;
	vector<double>* arr = new vector<double>(n);
	if (arr) {
		for (int i = 0; i < n; i++) {
			double temp;
			if (ifs >> temp) (*arr)[i] = temp;
			else {
				delete arr;
				return nullptr;
			}
		}
	}
	return arr;
}

const double* high(const double arr[], int n)
{
	if (n <= 0 || arr == nullptr) return nullptr;
	int indexOfHigh = 0;
	for (int i = 0; i < n; i++) {
		if (arr[indexOfHigh] < arr[i]) indexOfHigh = i;
	}
	return &arr[indexOfHigh];
}

const double* high(const vector<double>& v)
{
	if (v.size() == 0) return nullptr;
	int indexOfHigh = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[indexOfHigh] < v[i]) indexOfHigh = i;
	}
	return &v[indexOfHigh];
}

void fct()
{
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	if (jack_data) {
		const double* jack_high = high(jack_data, jack_count);
		if (jack_high) cout << endl << sp_4 << "Jack's max: " << *jack_high;
		delete[] jack_data;
	}
	
	vector<double>* jill_data = get_from_jill();
	if (jill_data) {
		vector<double>& v = *jill_data;
		const double* jill_high = high(v);
		if (jill_high) cout << endl << sp_4 << "Jill's max: " << *jill_high;
		delete jill_data;
	}
}
