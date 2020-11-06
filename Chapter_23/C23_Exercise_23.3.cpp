/* Exercise 23.3 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<vector>
#include<map>
#include<regex>
#include"C23_Exercise_23.3.h"

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
		"  (1) Sender\n"
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
			Mail_file mfile{ "C23_Exercise_23.1_mail.txt" };	// initialize mfile from a file
			// first gather messages from each sender together in a multimap:
			multimap<string, const Message*> sender;
			for (const auto& m : mfile) {
				string s;
				if (find_from_addr(&m, s)) {
					sender.insert(make_pair(s, &m));
				}
			}
			// now iterate through the multimap
			// and extract the subjects of John Doe’s messages:
			auto pp = sender.equal_range("John Doe <jdoe@machine.example>");
			for (auto p = pp.first; p != pp.second; ++p) {
				cout << find_subject(p->second) << '\n';
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

bool find_from_addr(const Message* m, string& s)
{
	constexpr int n = sizeof("From: ") - 1;
	for (const auto& x : *m) {
		if (regex_search(x, regex{ R"(^From: )" })) {
			s = string(x, n);
			return true;
		}
	}
	return false;
}

string find_subject(const Message* m)
{
	constexpr int n = sizeof("Subject: ") - 1;
	for (const auto& x : *m) {
		if (regex_search(x, regex{ R"(^Subject: )"})) return string(x, n);
	}
	return "";
}
