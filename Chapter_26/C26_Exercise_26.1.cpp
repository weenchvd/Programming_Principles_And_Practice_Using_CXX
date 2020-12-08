/* Exercise 26.1 */

#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<vector>
#include"C26_Exercise_26.1.h"

using namespace std;

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
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const string actionList = "\tList of actions:\n"
		"  (1) BinarySearch()\n"
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
			string failed = "failed";
			string succeed = "succeed";
			
			// Test 1 "The empty set"
			{
				vector<int> v;
				int x = 15;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 1 \"The empty set\": " << ((result) ? failed : succeed) << endl;
			}
			
			// Test 2.1 "Small sets"
			{
				vector<int> v{ 2,15,16 };
				int x = 15;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 2.1 \"Small sets\": " << ((result) ? succeed : failed) << endl;
			}
			
			// Test 2.2 "Small sets"
			{
				vector<int> v{ -2,15 };
				int x = 15;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 2.2 \"Small sets\": " << ((result) ? succeed : failed) << endl;
			}
			
			// Test 2.3 "Small sets"
			{
				vector<int> v{ 15,17,30 };
				int x = 15;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 2.3 \"Small sets\": " << ((result) ? succeed : failed) << endl;
			}
			
			// Test 3.1 "Large sets"
			{
				vector<int> v{ -43,-42,-39,-35,-30,-28,-26,-20,-15,-14,-12,-10,-8,-6,-3,-1,0,
							1,3,5,6,8,10,11,15,18,19,22,28,30,34,39,41,49,58,59,61,93 };
				int x = 15;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 3.1 \"Large sets\": " << ((result) ? succeed : failed) << endl;
			}
			
			// Test 3.2 "Large sets"
			{
				vector<int> v{ -434,-431,-420,-410,-400,-399,-390,-380,-371,-340,-320,-315,-309,-301,
							-300,-290,-289,-271,-270,-260,-222,-211,-199,-100,-43,-12,-8,-4,-1,0,
							1,2,4,5,6,8,9,11,15,35,94,124,165,244,564,933,1145,1255,1599,2222,3445,9325,
							35553,44554,99949,134412,255355,459999,699455,999999 };
				int x = 15;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 3.2 \"Large sets\": " << ((result) ? succeed : failed) << endl;
			}
			
			// Test 4.1 "Sets with extreme distributions"
			{
				vector<int> v{ -2345455346,-333444666,-1000,0,543534,324565345,1999888777 };
				int x = -1000;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 4.1 \"Sets with extreme distributions\": "
					<< ((result) ? succeed : failed) << endl;
			}
			
			// Test 4.2 "Sets with extreme distributions"
			{
				vector<int> v{ -1000000000,-500000,-100,44444,222333444,200000000 };
				int x = 222333444;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 4.2 \"Sets with extreme distributions\": "
					<< ((result) ? succeed : failed) << endl;
			}
			
			// Test 5.1 "Sets where 'what is of interest' happens near the end"
			{
				vector<int> v{ -43,-42,-39,-35,-30,-28,-26,-20,-15,-14,-12,-10,-8,-6,-3,-1,0,
							1,3,5,6,8,10,11,15,18,19,22,28,30,34,39,41,49,58,59,61,93 };
				int x = 61;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 5.1 \"Sets where \"what is of interest\" happens near the end\": "
					<< ((result) ? succeed : failed) << endl;
			}
			
			// Test 5.2 "Sets where 'what is of interest' happens near the end"
			{
				vector<int> v{ -43,-42,-39,-35,-30,-28,-26,-20,-15,-14,-12,-10,-8,-6,-3,-1,0,
							1,3,5,6,8,10,11,15,18,19,22,28,30,34,39,41,49,58,59,61,93 };
				int x = -39;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 5.2 \"Sets where \"what is of interest\" happens near the end\": "
					<< ((result) ? succeed : failed) << endl;
			}
			
			// Test 5.3 "Sets where 'what is of interest' happens near the end"
			{
				vector<int> v{ -43,-42,-39,-35,-30,-28,-26,-20,-15,-14,-12,-10,-8,-6,-3,-1,0,
							1,3,5,6,8,10,11,15,18,19,22,28,30,34,39,41,49,58,59,61,93 };
				int x = 93;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 5.3 \"Sets where \"what is of interest\" happens near the end\": "
					<< ((result) ? succeed : failed) << endl;
			}
			
			// Test 5.4 "Sets where "what is of interest" happens near the end"
			{
				vector<int> v{ -43,-42,-39,-35,-30,-28,-26,-20,-15,-14,-12,-10,-8,-6,-3,-1,0,
							1,3,5,6,8,10,11,15,18,19,22,28,30,34,39,41,49,58,59,61,93 };
				int x = -43;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 5.4 \"Sets where \"what is of interest\" happens near the end\": "
					<< ((result) ? succeed : failed) << endl;
			}
			
			// Test 6.1 "Sets with duplicate elements"
			{
				vector<int> v{ -43,-43,-39,-35,-30,-28,-28,-28,-15,-14,-12,-10,-10,-10,-10,-1,0,
							1,1,5,6,8,8,8,8,8,19,22,28,30,34,34,34,34,58,59,59,93 };
				int x = 30;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 6.1 \"Sets with duplicate elements\": "
					<< ((result) ? succeed : failed) << endl;
			}
			
			// Test 6.2 "Sets with duplicate elements"
			{
				vector<int> v{ -43,-43,-39,-35,-30,-28,-28,-28,-15,-14,-12,-10,-10,-10,-10,-1,0,
							1,1,5,6,8,8,8,8,8,19,22,28,30,34,34,34,34,58,59,59,93 };
				int x = -43;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 6.2 \"Sets with duplicate elements\": "
					<< ((result) ? succeed : failed) << endl;
			}
			
			// Test 6.3 "Sets with duplicate elements"
			{
				vector<int> v{ -43,-43,-39,-35,-30,-28,-28,-28,-15,-14,-12,-10,-10,-10,-10,-1,0,
							1,1,5,6,8,8,8,8,8,19,22,28,30,34,34,34,34,58,59,59,93 };
				int x = 8;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 6.3 \"Sets with duplicate elements\": "
					<< ((result) ? succeed : failed) << endl;
			}
			
			// Test 6.4 "Sets with duplicate elements"
			{
				vector<int> v{ -43,-43,-39,-35,-30,-28,-28,-28,-15,-14,-12,-10,-10,-10,-10,-1,0,
							1,1,5,6,8,8,8,8,8,19,22,28,30,34,34,34,34,58,59,59,93 };
				int x = 59;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 6.4 \"Sets with duplicate elements\": "
					<< ((result) ? succeed : failed) << endl;
			}
			
			// Test 7.1 "Sets with even and with odd numbers of elements"
			{
				vector<int> v{ 2,4,5,8,9,14,22,43 };
				int x = 22;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 7.1 \"Sets with even and with odd numbers of elements\": "
					<< ((result) ? succeed : failed) << endl;
			}
			
			// Test 7.2 "Sets with even and with odd numbers of elements"
			{
				vector<int> v{ 2,4,5,8,9,14,22,43,66 };
				int x = 4;
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 7.2 \"Sets with even and with odd numbers of elements\": "
					<< ((result) ? succeed : failed) << endl;
			}
			
			// Test 8 "Sets generated using random numbers"
			constexpr int numberOfElements = 50;
			constexpr int spread = 20;
			for (int i = 1; i <= 20; ++i) {
				vector<int> v;
				int sum = 0;
				for (int j = 0; j < numberOfElements; ++j) {
					sum += randint(spread);
					v.push_back(sum);
				}
				int x = v[randint(v.size())];
				bool result = BinarySearch(v.begin(), v.end(), x);
				cout << sp_2 << "Test 8." << i << " \"Sets generated using random numbers\": "
					<< ((result) ? succeed : failed) << endl;
			}

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

template<class RandomAccessIterator>
bool BinarySearch(RandomAccessIterator first, RandomAccessIterator last, int x)
{
	using Iter = RandomAccessIterator;
	if (first == last) return false;
	--last;
	while (first <= last) {
		Iter middle = (last - first) / 2 + first;
		if (*middle == x) return true;
		else if (*middle > x) last = middle - 1;
		else first = middle + 1;								// *middle < x
	}
	return false;
}
