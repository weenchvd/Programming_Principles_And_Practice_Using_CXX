/* Exercise 19.3 */

#include<iostream>
#include<istream>
#include<string>
#include<vector>
#include<iomanip>
#include<sstream>
#include"C19_Exercise_19.3.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

const char* space_c2 = "  ";
const char* space_c4 = "    ";
//const char* errMessageInputFile = "Error. Can't open input file: ";
//const char* errMessageOutputFile = "Error. Can't open output file: ";

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		PAIR
	};
	const string actionList = "\tList of actions:\n"
	"  (1) Pair\n"
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
		case PAIR: {
			vector<Pair<string, double>> constants;
			constants.push_back({ "Pi", 3.14159 });
			constants.push_back({ "e", 2.71828 });
			constants.push_back({ "Phi", 1.61803 });
			constants.push_back({ "W", 2.09455 });
			constants.push_back({ "G", 0.83463 });
			cout << space_c2 << "constants:" << endl;
			for (int i = 0; i < constants.size(); i++) {
				cout << space_c4 << constants[i].val1 << " == " << constants[i].val2 << endl;
			}

			vector<Pair<int, bool>> numbers;
			numbers.push_back({ 2, true });
			numbers.push_back({ 5, false });
			numbers.push_back({ 1, false });
			numbers.push_back({ -17, false });
			numbers.push_back({ 8, true });
			numbers.push_back({ 100, true });
			numbers.push_back({ 0, true });
			cout << space_c2 << "numbers: " << endl;
			for (int i = 0; i < numbers.size(); i++) {
				cout << space_c4 << numbers[i].val1 << " (" << ((numbers[i].val2) ? "true" : "false") << ")" << endl;
			}
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
