/* Exercise 19.6 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C19_Exercise_19.6.h"

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
		NUMBER
	};
	const string actionList = "\tList of actions:\n"
	"  (1) Number()\n"
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
		case NUMBER: {
			Number<int> ni1;
			Number<int> ni2{ 10 };
			Number<int> ni3 = ni2;
			cout << space_c2 << "Number<int> ni1;" << endl
				<< space_c2 << "Number<int> ni2{ 10 };" << endl
				<< space_c2 << "Number<int> ni3 = ni2;" << endl;
			cout << space_c4 << "ni1 == " << ni1 << ", ni2 == " << ni2 << ", ni3 == " << ni3 << endl << endl;

			string s1 = "  23 11";
			istringstream iss;
			iss.str(s1);
			iss >> ni1 >> ni2;
			ni3 = ni2;
			cout << space_c2 << "string s = \"  23 11\";" << endl
				<< space_c2 << "istringstream iss;" << endl
				<< space_c2 << "iss.str(s);" << endl
				<< space_c2 << "iss >> ni1 >> ni2;" << endl
				<< space_c2 << "ni3 = ni2;" << endl;
			cout << space_c4 << "ni1 == " << ni1 << ", ni2 == " << ni2 << ", ni3 == " << ni3 << endl << endl;

			Number<int> isum = ni1 + ni2;
			Number<int> idif = ni1 - ni2;
			Number<int> imult = ni1 * ni2;
			Number<int> iquot = ni1 / ni2;
			Number<int> irem = ni1 % ni2;
			cout << space_c2 << "Number<int> isum = ni1 + ni2;" << endl
				<< space_c2 << "Number<int> idif = ni1 - ni2;" << endl
				<< space_c2 << "Number<int> imult = ni1 * ni2;" << endl
				<< space_c2 << "Number<int> iquot = ni1 / ni2;" << endl
				<< space_c2 << "Number<int> irem = ni1 % ni2;" << endl;
			cout << space_c4 << "isum == " << isum << ", idif == " << idif
				<< ", imult == " << imult << ", iquot == " << iquot << ", irem == " << irem << endl << endl;
			
			
			cout << endl << endl;
			Number<double> nd1;
			Number<double> nd2{ 3.34 };
			Number<double> nd3 = nd2;
			cout << space_c2 << "Number<double> nd1;" << endl
				<< space_c2 << "Number<double> nd2{ 3.34 };" << endl
				<< space_c2 << "Number<double> nd3 = ni2;" << endl;
			cout << space_c4 << "nd1 == " << nd1 << ", nd2 == " << nd2 << ", nd3 == " << nd3 << endl << endl;

			string s2 = "23.15    11.1   ";
			iss.clear();
			iss.str(s2);
			iss >> nd1 >> nd2;
			nd3 = nd2;
			cout << space_c2 << "string s2 = \"23.15    11.1   \";" << endl
				<< space_c2 << "iss.clear();" << endl
				<< space_c2 << "iss.str(s2);" << endl
				<< space_c2 << "iss >> nd1 >> nd2;" << endl
				<< space_c2 << "nd3 = nd2;" << endl;
			cout << space_c4 << "nd1 == " << nd1 << ", nd2 == " << nd2 << ", nd3 == " << nd3 << endl << endl;

			Number<double> dsum = nd1 + nd2;
			Number<double> ddif = nd1 - nd2;
			Number<double> dmult = nd1 * nd2;
			Number<double> dquot = nd1 / nd2;
			//Number<double> drem = nd1 % nd2;
			cout << space_c2 << "Number<double> dsum = nd1 + nd2;" << endl
				<< space_c2 << "Number<double> ddif = nd1 - nd2;" << endl
				<< space_c2 << "Number<double> dmult = nd1 * nd2;" << endl
				<< space_c2 << "Number<double> dquot = nd1 / nd2;" << endl
				/*<< space_c2 << "Number<double> drem = nd1 % nd2;" << endl*/;
			cout << space_c4 << "dsum == " << dsum << ", ddif == " << ddif
				<< ", dmult == " << dmult << ", dquot == " << dquot /*<< ", drem == " << drem */<< endl << endl;

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

template<class T> istream& operator>>(istream& is, Number<T>& n)
{
	T temp;
	if (!(is >> temp)) return is;
	n.v = temp;
	return is;
}

template<class T> ostream& operator<<(ostream& os, Number<T> n)
{
	os << n.v;
	return os;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
