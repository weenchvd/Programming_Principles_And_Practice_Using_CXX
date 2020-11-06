/* Exercise 23.5 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include<regex>
#include<chrono>
#include"C23_Exercise_23.5.h"

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
			using timeUnit = chrono::milliseconds;			
			
			cout << sp_2 << "Please enter a file name: ";
			string fileName;
			getline(cin, fileName);
			if (!cin) error("Error. Incorrect input");

			Mail_file mailFile{ fileName };
			cout << sp_4 << "Mail file was created" << endl;

			auto mmapTime1 = chrono::system_clock::now();
			multimap<string, const Message*> sender1;
			for (const auto& m : mailFile) {
				string s;
				if (find_from_addr(&m, s)) {
					sender1.insert(make_pair(s, &m));
				}
			}
			auto mmapTime2 = chrono::system_clock::now();
			long long int multimapTime = chrono::duration_cast<timeUnit>(mmapTime2 - mmapTime1).count();
			cout << sp_4 << "Multimap was created in " << multimapTime << " millisecond(s)" << endl;

			auto ummapTime1 = chrono::system_clock::now();
			unordered_multimap<string, const Message*> sender2;
			for (const auto& m : mailFile) {
				string s;
				if (find_from_addr(&m, s)) {
					sender2.insert(make_pair(s, &m));
				}
			}
			auto ummapTime2 = chrono::system_clock::now();
			long long int umultimapTime = chrono::duration_cast<timeUnit>(ummapTime2 - ummapTime1).count();
			cout << sp_4 << "Unordered multimap was created in " << umultimapTime << " millisecond(s)" << endl;

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
{
	ifstream in{ n };						// open the file
	if (!in) error("Error. File opening error");
	for (string s; getline(in, s); ) {		// build the vector of lines
		lines.push_back(s);
	}
	auto first = lines.begin();				// build the vector of Messages
	for (auto p = lines.begin(); p != lines.end(); ++p) {
		if (regex_match(*p, regex{ R"(^--\S*--$)" })) {
			m.push_back(Message{ first, p });
			first = p + 1;
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

string find_from(const Message* m)
{
	constexpr int n = sizeof("From: ") - 1;
	for (const auto& x : *m) {
		if (regex_search(x, regex{ R"(^From: )"})) return string(x, n);
	}
	return "";
}

string find_subject(const Message* m)
{
	constexpr int n = sizeof("Subject: ") - 1;
	for (const auto& x : *m) {
		if (regex_search(x, regex{ R"(^Subject: )"})) return string(x, n);
	}
	return "";
}
