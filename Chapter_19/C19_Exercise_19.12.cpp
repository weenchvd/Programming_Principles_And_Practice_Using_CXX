/* Exercise 19.12 */

#include<iostream>
#include<istream>
#include<fstream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C19_Exercise_19.12.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		FILEHANDLE
	};
	const string actionList = "\tList of actions:\n"
	"  (1) FileHandle()\n"
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
		case FILEHANDLE: {
			string fileName = "C19_Exercise_19.12_numbers.txt";
			FileHandle<ifstream> ifh{ fileName };
			if (!ifh) error("Error. Can't open input file: ", fileName);
			int temp;
			cout << space_c2;
			while (ifh.Get() >> temp) cout << temp << " ";
			cout << endl << space_c4 << "EOF" << endl;
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
