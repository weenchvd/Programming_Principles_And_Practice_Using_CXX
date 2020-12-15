/* Exercise 26.12 */

#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<random>
#include<chrono>
#include"C26_Exercise_26.12.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Sorting random floating-point numbers\n"
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
		case CASE1: {
			cout << endl;
			default_random_engine generator;
			uniform_real_distribution<double> distribution(-1000.0, 1000);
			using timeUnit = chrono::microseconds;
			constexpr int nElements1 = 500000;
			constexpr int nElements2 = 5000000;

			vector<double> v1(nElements1);
			vector<double> v2(nElements2);

			for (int i = 0; i < v1.size(); ++i) v1[i] = distribution(generator);
			for (int i = 0; i < v2.size(); ++i) v2[i] = distribution(generator);

			auto t1 = chrono::system_clock::now();
			sort(v1.begin(), v1.end());
			auto t2 = chrono::system_clock::now();
			long long int v1time = chrono::duration_cast<timeUnit>(t2 - t1).count();

			t1 = chrono::system_clock::now();
			sort(v2.begin(), v2.end());
			t2 = chrono::system_clock::now();
			long long int v2time = chrono::duration_cast<timeUnit>(t2 - t1).count();

			cout << "Time to sort " << nElements1 << " random floating-point numbers: "
				<< v1time << " microsecond(s)" << endl;
			cout << "Time to sort " << nElements2 << " random floating-point numbers: "
				<< v2time << " microsecond(s)" << endl;


			cout << vsp_2;
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
