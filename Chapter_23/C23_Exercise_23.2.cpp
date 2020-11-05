/* Exercise 23.2 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<vector>
#include<map>
#include"C23_Exercise_23.2.h"

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
		"  (1) Subject\n"
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
			Mail_file mfile{ "C23_Exercise_23.1_mail.txt" };
			multimap<string, const Message*> subjects;
			for (const auto& m : mfile) {
				string s;
				if (find_subject_field(&m, s)) {
					subjects.insert(make_pair(s, &m));
				}
			}
			string s;
			cout << sp_2 << "Please enter a subject: ";
			getline(cin, s);
			if (!cin) { ClearInput(cin); error("Error. Incorrect input"); }
			cout << endl;
			auto pp = subjects.equal_range(s);
			int messageNum = 0;
			for (auto p = pp.first; p != pp.second; ++p) {
				++messageNum;
				cout << sp_2 << "Message #" << messageNum << endl;
				for (auto it = p->second->begin(); it != p->second->end(); ++it) {
					cout << sp_4 << *it << endl;
				}
				cout << endl;
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

Mail_file::Mail_file(const string& n)
// open file named n
// read the lines from n into lines
// find the messages in the lines and compose them in m
// for simplicity assume every message is ended by a ---- line
{
	ifstream in{ n };						// open the file
	if (!in) {
		cerr << "no " << n << '\n';
		exit(1);							// terminate the program
	}
	for (string s; getline(in, s); ) {		// build the vector of lines
		lines.push_back(s);
	}
	auto first = lines.begin();				// build the vector of Messages
	for (auto p = lines.begin(); p != lines.end(); ++p) {
		if (*p == "----") {					// end of message
			m.push_back(Message(first, p));
			first = p + 1;					// ---- not part of message
		}
	}
}

int is_prefix(const string& s, const string& p)					// is p the first part of s?
{
	int n = p.size();
	if (string(s, 0, n) == p) return n;
	return 0;
}

bool find_from_addr(const Message* m, string& s)
{
	for (const auto& x : *m) {
		if (int n = is_prefix(x, "From: ")) {
			s = string(x, n);
			return true;
		}
	}
	return false;
}

bool find_to_addr(const Message* m, string& s)
{
	for (const auto& x : *m) {
		if (int n = is_prefix(x, "To: ")) {
			s = string(x, n);
			return true;
		}
	}
	return false;
}

bool find_subject_field(const Message* m, string& s)
{
	for (const auto& x : *m) {
		if (int n = is_prefix(x, "Subject: ")) {
			s = string(x, n);
			return true;
		}
	}
	return false;
}

string find_subject(const Message* m)
{
	for (const auto& x : *m) {
		if (int n = is_prefix(x, "Subject: ")) return string(x, n);
	}
	return "";
}
