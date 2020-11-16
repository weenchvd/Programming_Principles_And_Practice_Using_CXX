/* Exercise 23.14 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<vector>
#include<regex>
#include"C23_Exercise_23.14.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10, CASE11, CASE12
	};
	string pattern1{ R"(\b\d{4}\b)" };
	string pattern2{ R"(To\w*)" };
	string pattern3{ R"(-\n)" };
	string pattern4{ R"(\b\w{8}\b)" };
	string pattern5{ R"(^.+;$)" };
	string pattern6{ R"( -\w+\b)" };
	string pattern7{ R"(\b\w+: )" };
	string pattern8{ R"(\s\d{4}(-\d{2}){1,2}\s)" };
	string pattern9{ R"(\s"\w+"\W)" };
	string pattern10{ R"(^(\S+ ){2}\S+$)" };
	const string actionList = "\tList of actions:\n"
		"  (1) Search\n"
		"  (2) pattern: " + pattern1 + '\n' +
		"  (3) pattern: " + pattern2 + '\n' +
		"  (4) pattern: " + pattern3 + '\n' +
		"  (5) pattern: " + pattern4 + '\n' +
		"  (6) pattern: " + pattern5 + '\n' +
		"  (7) pattern: " + pattern6 + '\n' +
		"  (8) pattern: " + pattern7 + '\n' +
		"  (9) pattern: " + pattern8 + '\n' +
		"  (10) pattern: " + pattern9 + '\n' +
		"  (11) pattern: " + pattern10 + '\n' +
		"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	
	string text;
	int action;
	bool cond{ true };
	while (cond) try {
		if (text.size() == 0) {
			cout << sp_2 << "Please enter a file name: ";
			string fileName;
			getline(cin, fileName);
			if (!cin) error("Error. Incorrect input");
			ifstream ifs{ fileName };
			if (!ifs) error("Error. File opening error");
			while (true) {
				string s;
				getline(ifs, s);
				if (!ifs) {
					if (ifs.eof() && s.size() == 0) break;
					else error("Error. Read error");
				}
				text += s + '\n';
			}
		}

		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case CASE1: {
			cout << endl;

			string s;
			cout << sp_2 << "Please enter a pattern: ";
			getline(cin, s);
			if (!cin) error("Error. Incorrect input");

			regex pattern;
			try {
				pattern = s; // this checks pat
				cout << sp_4 << "Pattern: " << s << endl;
			}
			catch (regex_error) {
				cout << s + " is not a valid regular expression\n";
				break;
			}
			
			PrintStringsMatched(text, pattern);

			cout << vsp_2;
			break;
		}
		case CASE2:
			PrintStringsMatched(text, regex{ pattern1 });
			cout << vsp_2;
			break;
		case CASE3:
			PrintStringsMatched(text, regex{ pattern2 });
			cout << vsp_2;
			break;
		case CASE4:
			PrintStringsMatched(text, regex{ pattern3 });
			cout << vsp_2;
			break;
		case CASE5:
			PrintStringsMatched(text, regex{ pattern4 });
			cout << vsp_2;
			break;
		case CASE6:
			PrintStringsMatched(text, regex{ pattern5 });
			cout << vsp_2;
			break;
		case CASE7:
			PrintStringsMatched(text, regex{ pattern6 });
			cout << vsp_2;
			break;
		case CASE8:
			PrintStringsMatched(text, regex{ pattern7 });
			cout << vsp_2;
			break;
		case CASE9:
			PrintStringsMatched(text, regex{ pattern8 });
			cout << vsp_2;
			break;
		case CASE10:
			PrintStringsMatched(text, regex{ pattern9 });
			cout << vsp_2;
			break;
		case CASE11:
			PrintStringsMatched(text, regex{ pattern10 });
			cout << vsp_2;
			break;
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

void PrintStringsMatched(const string& text, const regex& pattern)
{
	cout << sp_4 << "[Format] Strings that match the pattern:" << endl;
	string::const_iterator itTextFirst = text.begin();
	string::const_iterator itTextLast = text.end();
	while (true) {
		smatch matches;
		if (!regex_search(itTextFirst, itTextLast, matches, pattern)) break;
		string::const_iterator itLineFirst = matches[0].first;
		while (true) {
			if (itLineFirst == text.begin()) break;
			if (*itLineFirst == '\n') {
				++itLineFirst;
				break;
			}
			--itLineFirst;
		}
		string::const_iterator itLineLast = matches.suffix().first;
		while (itLineLast != text.end() && *itLineLast != '\n') ++itLineLast;

		cout << sp_6;
		for (; itLineFirst != itLineLast; ++itLineFirst) {
			cout.put(*itLineFirst);
			if (*itLineFirst == '\n') cout << sp_6;
		}
		cout << endl << sp_8 << "Match: " << matches[0] << endl;
		itTextFirst = matches.suffix().first;
	}
}
