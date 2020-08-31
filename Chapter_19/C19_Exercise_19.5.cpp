/* Exercise 19.5 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C19_Exercise_19.5.h"

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
		INT
	};
	const string actionList = "\tList of actions:\n"
	"  (1) Int()\n"
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
		case INT: {
			Int i1;
			Int i2{ 10 };
			Int i3 = i2;
			cout << space_c2 << "Int i1;" << endl
				<< space_c2 << "Int i2{ 10 };" << endl
				<< space_c2 << "Int i3 = i2;" << endl;
			cout << space_c4 << "i1 == " << i1 << ", i2 == " << i2 << ", i3 == " << i3 << endl << endl;

			string s = "  23 11";
			istringstream iss;
			iss.str(s);
			iss >> i1 >> i2;
			i3 = i2;
			cout << space_c2 << "string s = \"  23 11\";" << endl
				<< space_c2 << "istringstream iss;" << endl
				<< space_c2 << "iss.str(s);" << endl
				<< space_c2 << "iss >> i1 >> i2;" << endl
				<< space_c2 << "i3 = i2;" << endl;
			cout << space_c4 << "i1 == " << i1 << ", i2 == " << i2 << ", i3 == " << i3 << endl << endl;

			Int sum = i1 + i2;
			Int dif = i1 - i2;
			Int mult = i1 * i2;
			Int quot = i1 / i2;
			cout << space_c2 << "Int sum = i1 + i2;" << endl
				<< space_c2 << "Int dif = i1 - i2;" << endl
				<< space_c2 << "Int mult = i1 * i2;" << endl
				<< space_c2 << "Int quot = i1 / i2;" << endl;
			cout << space_c4 << "sum == " << sum << ", dif == " << dif
				<< ", mult == " << mult << ", quot == " << quot << endl << endl;

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

istream& operator>>(istream& is, Int& i)
{
	int temp;
	if (!(is >> temp)) return is;
	i.v = temp;
	return is;
}

ostream& operator<<(ostream& os, Int i)
{
	os << i.v;
	return os;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
