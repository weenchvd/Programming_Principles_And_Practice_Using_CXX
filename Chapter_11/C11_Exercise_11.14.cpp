/* Exercise 11.14 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"C11_Exercise_11.14.h"

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
		PRINTCLASSIFICATION
	};
	const string actionList = "\tList of actions:\n"
	"  (1) PrintCharacterClassification()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case PRINTCLASSIFICATION: {
			string inFileName;
			cout << "Please enter the name of input file: ";
			if (!(cin >> inFileName)) { ClearInput(cin); error("Error. Incorrect input"); }
			PrintCharacterClassification(inFileName);
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

void PrintCharacterClassification(const string& inputFileName)
{
	ifstream ifs;
	ifs.open(inputFileName);
	if (!ifs) error(errMessageInputFile, inputFileName);
	CharClassification cl;
	for (char ch; ifs.get(ch); ) {
		if (isspace(ch)) {
			cl.space++;
		}
		if (isalpha(ch)) {
			cl.letter++;
			if (isupper(ch)) cl.upper++;
			else cl.lower++;
		}
		if (isdigit(ch)) {
			cl.digit++;
		}
		if (iscntrl(ch)) {
			cl.control++;
		}
		if (ispunct(ch)) {
			cl.punct++;
		}
		if (isprint(ch)) {
			cl.print++;
		}
	}
	if (!ifs.eof()) error("Input failure");
	int field1 = 23;
	int field2 = 10;
	cout << "\nClassification:\n";
	cout << setw(field1) << right << "Whitespace: " << setw(field2) << left << cl.space << endl;
	cout << setw(field1) << right << "Letter: " << setw(field2) << left << cl.letter << endl;
	cout << setw(field1) << right << "Uppercase letter: " << setw(field2) << left << cl.upper << endl;
	cout << setw(field1) << right << "Lowercase letter: " << setw(field2) << left << cl.lower << endl;
	cout << setw(field1) << right << "Decimal digit: " << setw(field2) << left << cl.digit << endl;
	cout << setw(field1) << right << "Control character: " << setw(field2) << left << cl.control << endl;
	cout << setw(field1) << right << "Punctuation character: " << setw(field2) << left << cl.punct << endl;
	cout << setw(field1) << right << "Printable: " << setw(field2) << left << cl.print << endl;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
