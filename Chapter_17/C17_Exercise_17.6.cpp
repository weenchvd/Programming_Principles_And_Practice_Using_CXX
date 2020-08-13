/* Exercise 17.6 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C17_Exercise_17.6.h"

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
		MEMORYEXHAUSTION
	};
	const string actionList = "\tList of actions:\n"
	"  (1) AllocateMemory()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	const char* indent2 = "  ";
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case MEMORYEXHAUSTION: {
			int i;
			for (i = 1; i < numeric_limits<int>::max(); i++) {
				if (AllocateMemory(1)) cout << indent2 << "Allocated " << i << " MB" << endl;
				else {
					cout << "No memory has been allocated" << endl;
					break;
				}
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

bool AllocateMemory(int numberOfMegaBytes)
{
	if (numberOfMegaBytes <= 0) return false;
	char* p = new char[numberOfMegaBytes * 1024 * 1024];
	if (p) return true;
	return false;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
