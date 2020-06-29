/* Exercise 11.3 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"C11_Exercise_11.3.h"

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
		REMOVEVOWELS
	};
	const string actionList = "\tList of actions:\n"
	"  (1) RemoveVowelsFromFile()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case REMOVEVOWELS: {
			string fn;
			cout << "Please enter the file name: ";
			if (!(cin >> fn)) { ClearInput(cin); error("Error. Incorrect input"); }
			RemoveVowelsFromFile(fn);
			cout << "Done!\n";
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

void RemoveVowelsFromFile(const string fileName)
{
	ifstream ifs{ fileName };
	if (!ifs) error(errMessageInputFile, fileName);
	string ofn = "temp";
	ofstream ofs{ ofn };
	if (!ofs) error(errMessageOutputFile, ofn);
	while (true) {
		char ch;
		ifs.get(ch);
		if (!ifs) {
			if (ifs.eof()) break;
			error("Input failure");
		}
		if (!isVowel(ch)) ofs.put(ch);
	}
	ifs.close();
	ofs.close();
	const char* fi = fileName.c_str();
	remove(fi);
	const char* fo = ofn.c_str();
	rename(fo, fi);
}

bool isVowel(const char ch)
{
	char c = tolower(ch);
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return true;
	return false;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
