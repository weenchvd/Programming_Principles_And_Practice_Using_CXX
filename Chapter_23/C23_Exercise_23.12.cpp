/* Exercise 23.12 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<vector>
#include<regex>
#include"C23_Exercise_23.12.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Reformat to ISO date\n"
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
		case CASE1: {
			cout << endl;
			cout << sp_2 << "Please enter a file name: ";
			string fileName;
			getline(cin, fileName);
			if (!cin) error("Error. Incorrect input");
			ifstream ifs{ fileName };
			if(!ifs) error("Error. File opening error");
			ofstream ofs{ "C23_Exercise_23.12_reformat.txt" };
			if (!ofs) error("Error. File opening error");

			while (true) {
				string s;
				getline(ifs, s);
				if (!ifs) {
					if (ifs.eof()) break;
					else error("Error. Read error");
				}
				ReformatDateToISO(ofs, s);
			}

			cout << vsp_2;
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

void ReformatDateToISO(ostream& os, const string& s)
{
	constexpr int nPatterns = 4;
	constexpr int nDigitInYear = 4;
	constexpr int nDigitInMonth = 2;
	constexpr int nDigitInDay = 2;
	/* date pattern:
	dd/mm/yyyy OR dd-mm-yyyy OR dd.mm.yyyy OR
	mm/dd/yyyy OR mm-dd-yyyy OR mm.dd.yyyy OR
	yyyy/mm/dd OR yyyy-mm-dd OR yyyy.mm.dd OR
	yyyy/dd/mm OR yyyy-dd-mm OR yyyy.dd.mm
	*/
	string db{ R"((^|\s|$))" };									// date boundary
	string sep{ R"([./-])" };									// separator list
	string d{ R"((0?[1-9]|[12]\d|3[01]))" };					// day: D or DD
	string m{ R"((0?[1-9]|1[0-2]))" };							// month: M or MM
	string y{ R"((\d{4}))" };									// year: YYYY
	constexpr int sepGroupBegin = 1;
	constexpr int sepGroupEnd = 5;

	vector<regex> pattern(nPatterns);
	vector<PatternGroup> pg(nPatterns);

	pattern[0] = regex{ db + d + sep + m + sep + y + db };
	pg[0] = PatternGroup{ 4, 3, 2 };

	pattern[1] = regex{ db + m + sep + d + sep + y + db };
	pg[1] = PatternGroup{ 4, 2, 3 };

	pattern[2] = regex{ db + y + sep + m + sep + d + db };
	pg[2] = PatternGroup{ 2, 3, 4 };

	pattern[3] = regex{ db + y + sep + d + sep + m + db };
	pg[3] = PatternGroup{ 2, 4, 3 };

	string line = s;
	for (int i = 0; i < nPatterns; ++i) {
		string formatted;
		string::const_iterator itFirst = line.begin();
		string::const_iterator itLast = line.end();
		while (true) {
			smatch matched;
			if (!regex_search(itFirst, itLast, matched, pattern[i])) {
				formatted += string{ itFirst, itLast };
				break;
			}
			formatted += string{ itFirst, matched[0].first };
			formatted += string{ matched[sepGroupBegin].first, matched[sepGroupBegin].second };
			formatted += string{ matched[pg[i].y] };
			formatted += '-';
			if (matched[pg[i].m].second - matched[pg[i].m].first < nDigitInMonth) {
				formatted += '0';
			}
			formatted += string{ matched[pg[i].m] };
			formatted += '-';
			if (matched[pg[i].d].second - matched[pg[i].d].first < nDigitInDay) {
				formatted += '0';
			}
			formatted += string{ matched[pg[i].d] };
			formatted += string{ matched[sepGroupEnd].first, matched[sepGroupEnd].second };
			itFirst = matched.suffix().first;
		}
		line = formatted;
	}
	os << line << endl;
}
