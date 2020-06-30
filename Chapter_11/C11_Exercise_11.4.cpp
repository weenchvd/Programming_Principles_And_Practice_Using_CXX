/* Exercise 11.4 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"C11_Exercise_11.4.h"

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
		MULTIINPUT
	};
	const string actionList = "\tList of actions:\n"
	"  (1) multi input\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case MULTIINPUT: {
			vector<Integer>integers;
			int num;
			cout << "Please enter several integers (octal, decimal, hexadecimal). "
				"Enter any letter to finish input\n";
			while (true) {
				string s;
				cin >> s;
				if (!cin) {
					if (cin.eof()) break;
					error("Bad input");
				}
				int i = 0;
				char ch = s[i];
				if (ch == '-') {
					if (s.size() > i + 1) ch = s[++i];
					else error("Error. Incorrect input");
				}
				if (ch == '0') {
					if (s.size() > i + 1) {
						if (i > 0) error("Hexadecimal or octal number must be positive");
						ch = s[++i];
					}
					else {
						integers.push_back(Integer(0, 'd'));
						continue;
					}
					if (ch == 'x' || ch == 'X') integers.push_back(GetInteger(s, 'h'));
					else if (isdigit(ch) && ch != '0') integers.push_back(GetInteger(s, 'o'));
					else error("Error. Incorrect input");
				}
				else if (isdigit(ch)) integers.push_back(GetInteger(s, 'd'));
				else if (isalpha(ch)) break;
				else error("Error. Incorrect input");
			}
			int field1 = 0;
			int field2 = 0;
			for (int i = 0; i < integers.size(); i++) {
				int nDigits = 1;
				if (integers[i].base == 'h') {
					int x = integers[i].decNum;
					while (x /= 16) nDigits++;
					nDigits += 2;
				}
				else if (integers[i].base == 'o') {
					int x = integers[i].decNum;
					while (x /= 8) nDigits++;
					nDigits += 1;
				}
				else if (integers[i].base == 'd') {
					int x = integers[i].decNum;
					while (x /= 10) nDigits++;
				}
				else error("Unknown base");
				if (nDigits > field1) field1 = nDigits;
				int nDecimalDigits = 1;
				if (integers[i].base == 'd') nDecimalDigits = nDigits;
				else {
					int x = integers[i].decNum;
					while (x /= 10) nDecimalDigits++;
				}
				if (nDecimalDigits > field2) field2 = nDecimalDigits;
			}
			cout << endl;
			for (int i = 0; i < integers.size(); i++) {
				cout << showbase << setw(field1);
				if (integers[i].base == 'h') {
					cout << hex << integers[i].decNum << setw(12) << left << " hexadecimal";
				}
				else if (integers[i].base == 'o') {
					cout << oct << integers[i].decNum << setw(12) << left << " octal";
				}
				else if (integers[i].base == 'd') {
					cout << dec << integers[i].decNum << setw(12) << left << " decimal";
				}
				cout << " converts to " << setw(field2) << dec << right << integers[i].decNum << " decimal";
				cout << endl;
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

Integer GetInteger(const string& s, const char base)
{
	istringstream iss;
	iss.str(s);
	int num;
	if (base == 'h') iss >> hex >> num;
	else if (base == 'o') iss >> oct >> num;
	else if (base == 'd') iss >> num;
	else error("Invalid base");
	if (iss) return Integer(num, base);
	error("Error. Incorrect input");
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
