/* Exercise 23.10 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<vector>
#include<map>
#include<regex>
#include"C23_Exercise_23.10.h"

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
		"  (1) Merge rows\n"
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
			ifstream ifs{ "C23_Exercise_23.9_table.txt" };
			if (!ifs) error("Error. File opening error");
			ofstream ofs{ "C23_Exercise_23.10_table_merged.txt" };
			if (!ofs) error("Error. File opening error");
			string first;
			size_t lineNum = 0;
			regex header{ R"(^[\w ]+(\t[\w ]+)*$)" };			// header line
			regex row{ R"(^([\w ]+)(\t\d+)(\t\d+)(\t\d+)$)" };	// data line

			if (getline(ifs, first)) {							// check header line
				smatch matches;
				if (!regex_match(first, matches, header)) {
					error("Error. No header");
				}
			}

			string line;
			string last;
			map<string, SchoolClass> classes;
			while (true) {
				++lineNum;
				getline(ifs, line);
				if (!ifs) {
					if (ifs.eof() && line.size() == 0) break;
					else error("Error. Read error");
				}
				smatch matches;
				if (!regex_match(line, matches, row)) cerr << "bad line: " << lineNum << '\n';
				if (matches[1] == "Alle klasser") {
					last = line;
					break;
				}
				string classNum;
				string temp = matches[1];
				for (int i = 0; i < temp.size(); ++i) {
					if (isdigit(temp[i])) classNum += temp[i];
					else {
						if (i == 0) classNum = temp;
						break;
					}
				}
				int curr_boy = from_string<int>(matches[2]);
				int curr_girl = from_string<int>(matches[3]);
				int curr_total = from_string<int>(matches[4]);
				if (curr_boy + curr_girl != curr_total) error("bad row sum\n");
				SchoolClass& cl = classes[classNum];
				cl.boys += curr_boy;
				cl.girls += curr_girl;
				cl.total += curr_total;
			}

			ofs << first << endl;
			for (auto it = classes.begin(); it != classes.end(); ++it) {
				ofs << it->first << '\t' << it->second.boys << '\t' << it->second.girls
					<< '\t' << it->second.total << endl;
			}
			ofs << last;

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
