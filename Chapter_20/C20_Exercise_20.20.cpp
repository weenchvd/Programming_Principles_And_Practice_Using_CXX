/* Exercise 20.20 */

#include<iostream>
#include<istream>
#include<sstream>
#include<string>
#include<vector>
#include<list>
#include<chrono>
#include<iomanip>
#include"C20_Exercise_20.20.h"

using namespace std;
using namespace chrono;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }
inline int randint(int max) { return rand() % max; }
inline int randint(int min, int max) { return randint(max - min) + min; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		TIME1, TIME2, TIME3, TIME4
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Time v1 (incorrect), (2) Time v2, (3) Time v2 + output,\n"
		"  (4) Why are the results between (2) and (3) so different?\n"
		"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);

		constexpr int n = numeric_limits<int>::max();
		constexpr int maxCount = 1000;
		constexpr int maxAttempts = 10;
		using timeUnit = nanoseconds;

		switch (action) {
		case TIME1: {
			vector<int> attempt;
			for (int i = 0; i < maxAttempts; i++) {
				list<int> l{ 0 };
				vector<int> v{ 0 };
				int count = 0;
				for (int j = 0; j < n; j++) {
					int number = randint(n);

					list<int>::iterator itList;
					for (itList = l.begin(); itList != l.end(); ++itList) {
						if (*itList >= number) break;
					}
					auto listTime1 = system_clock::now();
					l.insert(itList, number);
					auto listTime2 = system_clock::now();

					vector<int>::iterator itVec;
					for (itVec = v.begin(); itVec != v.end(); ++itVec) {
						if (*itVec >= number) break;
					}
					auto vecTime1 = system_clock::now();
					v.insert(itVec, number);
					auto vecTime2 = system_clock::now();

					auto listTime = duration_cast<timeUnit>(listTime2 - listTime1).count();
					auto vecTime = duration_cast<timeUnit>(vecTime2 - vecTime1).count();
					if (listTime < vecTime) count++;
					if (count > maxCount) {
						attempt.push_back(j - maxCount);
						break;
					}
				}
			}
			cout << "list<int> faster then vector<int> for N > ";
			int i = 0;
			for (int j = 0; j < attempt.size(); j++) i += attempt[j];
			cout << i / attempt.size();
			cout << endl << endl;
			break;
		}
		case TIME2: {
			vector<int> attempt;
			for (int i = 0; i < maxAttempts; i++) {
				list<int> l{ 0 };
				vector<int> v{ 0 };
				int count = 0;
				long long int listTime = 0;
				long long int vecTime = 0;
				for (int j = 0; j < n; j++) {
					int number = randint(n);

					list<int>::iterator itList;
					for (itList = l.begin(); itList != l.end(); ++itList) {
						if (*itList >= number) break;
					}
					auto listTime1 = system_clock::now();
					l.insert(itList, number);
					auto listTime2 = system_clock::now();

					vector<int>::iterator itVec;
					for (itVec = v.begin(); itVec != v.end(); ++itVec) {
						if (*itVec >= number) break;
					}
					auto vecTime1 = system_clock::now();
					v.insert(itVec, number);
					auto vecTime2 = system_clock::now();

					listTime += duration_cast<timeUnit>(listTime2 - listTime1).count();
					vecTime += duration_cast<timeUnit>(vecTime2 - vecTime1).count();
					if (listTime < vecTime) count++;
					else count = 0;
					if (count > maxCount) {
						attempt.push_back(j - count);
						break;
					}
				}
			}
			cout << "list<int> faster then vector<int> for N > ";
			int i = 0;
			for (int j = 0; j < attempt.size(); j++) i += attempt[j];
			cout << i / attempt.size();
			cout << endl << endl;
			break;
		}
		case TIME3: {
			vector<int> attempt;
			for (int i = 0; i < maxAttempts; i++) {
				list<int> l{ 0 };
				vector<int> v{ 0 };
				int count = 0;
				long long int listTime = 0;
				long long int vecTime = 0;
				for (int j = 0; j < n; j++) {
					int number = randint(n);

					list<int>::iterator itList;
					for (itList = l.begin(); itList != l.end(); ++itList) {
						if (*itList >= number) break;
					}
					auto listTime1 = system_clock::now();
					l.insert(itList, number);
					auto listTime2 = system_clock::now();

					vector<int>::iterator itVec;
					for (itVec = v.begin(); itVec != v.end(); ++itVec) {
						if (*itVec >= number) break;
					}
					auto vecTime1 = system_clock::now();
					v.insert(itVec, number);
					auto vecTime2 = system_clock::now();

					listTime += duration_cast<timeUnit>(listTime2 - listTime1).count();
					vecTime += duration_cast<timeUnit>(vecTime2 - vecTime1).count();
					if (listTime < vecTime) count++;
					else count = 0;
					cout << sp_2 << "vecTime: " << setw(20) << left << vecTime << " listTime: " << listTime << endl;
					if (count > maxCount) {
						attempt.push_back(j - count);
						cout << sp_4 << "count: " << count << ", j - count: " << j - count << endl;
						break;
					}
				}
				cout << endl << endl;
			}
			cout << "list<int> faster then vector<int> for N > ";
			int i = 0;
			for (int j = 0; j < attempt.size(); j++) i += attempt[j];
			cout << i / attempt.size();
			cout << endl << endl;
			break;
		}
		case TIME4: {
			cout << sp_8 << "I don't understand..." << endl;
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
