/* Exercise 17.2 */

#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C17_Exercise_17.2.h"

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
		PRINTNUMBYTES
	};
	const string actionList = "\tList of actions:\n"
	"  (1) PrintNumberOfBytes()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case PRINTNUMBYTES: {
			cout << "I think: bool == 1 byte, int == 4 bytes, double == 8 bytes" << endl;
			cout << "sizeof(): bool == " << sizeof(bool) << ", int == " << sizeof(int) << ", double == "
				<< sizeof(double) << endl;
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
