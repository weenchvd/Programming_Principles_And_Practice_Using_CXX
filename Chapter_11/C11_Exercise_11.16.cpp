/* Exercise 11.16 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"C11_Exercise_11.16.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

const string errMessageInputFile = "Error. Can't open input file: ";
const string errMessageOutputFile = "Error. Can't open output file: ";

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		PRINTSTATISTIC
	};
	const string actionList = "\tList of actions:\n"
	"  (1) ReadAndPrintStatistic()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case PRINTSTATISTIC: {
			string inFileName;
			cout << "Please enter the name of input file: ";
			if (!(cin >> inFileName)) { ClearInput(cin); error("Error. Incorrect input"); }
			ReadAndPrintStatistic(inFileName);
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

void ReadAndPrintStatistic(const string& inputFileName)
{
	ifstream ifs;
	ifs.open(inputFileName);
	if (!ifs) error(errMessageInputFile, inputFileName);
	vector<int> numbers;
	for (int n; ifs >> n; ) {
		numbers.push_back(n);
	}
	if (!ifs.eof()) error("Input failure");
	sort(numbers.begin(), numbers.end());
	constexpr int fieldWidth = 10;
	int i = 0;
	cout << setw(fieldWidth) << numbers[i];
	int counter = 1;
	for (i++; i < numbers.size(); i++) {
		if (numbers[i] == numbers[i - 1]) {
			counter++;
		}
		else {
			if (counter > 1) cout << setw(fieldWidth) << counter;
			cout << endl << setw(fieldWidth) << numbers[i];
			counter = 1;
		}
	}
	if (counter > 1) cout << setw(fieldWidth) << counter;
	cout << endl;
	ifs.close();
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
