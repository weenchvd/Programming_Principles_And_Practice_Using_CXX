/* Exercise 18.7 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C18_Exercise_18.7.h"

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
		CONCATENATEDOT, CONCATENATE
	};
	const string actionList = "\tList of actions:\n"
	"  (1) cat_dot(dot), (2) cat_dot(separator)\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	const char* space2 = "  ";
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case CONCATENATEDOT: {
			cout << "\nPlease enter the first string in English (only ASCII): ";
			string s1;
			if (!getline(cin, s1)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cs1 = new char[s1.size() + 1];
			int i;
			for (i = 0; i < s1.size(); i++) cs1[i] = s1[i];
			cs1[i] = '\0';
			cout << "Please enter the second string in English (only ASCII): ";
			string s2;
			if (!getline(cin, s2)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cs2 = new char[s2.size() + 1];
			for (i = 0; i < s2.size(); i++) cs2[i] = s2[i];
			cs2[i] = '\0';

			char* result = cat_dot(cs1, cs2);
			cout << space2 << "Result: " << result << endl;
			delete[] cs1;
			delete[] cs2;
			break;
		}
		case CONCATENATE: {
			cout << "\nPlease enter the first string in English (only ASCII): ";
			string s1;
			if (!getline(cin, s1)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cs1 = new char[s1.size() + 1];
			int i;
			for (i = 0; i < s1.size(); i++) cs1[i] = s1[i];
			cs1[i] = '\0';
			cout << "Please enter the second string in English (only ASCII): ";
			string s2;
			if (!getline(cin, s2)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cs2 = new char[s2.size() + 1];
			for (i = 0; i < s2.size(); i++) cs2[i] = s2[i];
			cs2[i] = '\0';
			cout << "Please enter the separator (string) in English (only ASCII): ";
			string sep;
			if (!getline(cin, sep)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cSeparator = new char[sep.size() + 1];
			for (i = 0; i < sep.size(); i++) cSeparator[i] = sep[i];
			cSeparator[i] = '\0';

			char* result = cat_dot(cs1, cs2, cSeparator);
			cout << space2 << "Result: " << result << endl;
			delete[] cs1;
			delete[] cs2;
			delete[] cSeparator;
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

char* cat_dot(const char* s1, const char* s2, const char* separator)
{
	int size1 = 0;
	while (s1[size1] != '\0') size1++;
	int size2 = 0;
	while (s2[size2] != '\0') size2++;
	int size3 = 0;
	while (separator[size3] != '\0') size3++;
	char* ret = new char[size1 + size2 + size3 + 1];
	int i = 0;
	for (int j = 0; j < size1; j++) ret[i++] = s1[j];
	for (int j = 0; j < size3; j++) ret[i++] = separator[j];
	for (int j = 0; j < size2; j++) ret[i++] = s2[j];
	ret[i] = '\0';
	return ret;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
