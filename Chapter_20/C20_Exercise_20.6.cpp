/* Exercise 20.6 */

#include<iostream>
#include<fstream>
#include<istream>
#include<string>
#include<vector>
#include<list>
#include<iomanip>
#include<sstream>
#include<cstdlib>
#include"C20_Exercise_20.6.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		FINDANDREPLACE
	};
	const string actionList = "\tList of actions:\n"
	"  (1) FindAndReplace()\n"
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
		case FINDANDREPLACE: {
			Document doc;
			istringstream iss;
			iss.str("Title\nThe first line of the document\nAnother line\nUPPER CASE LETTERS\nLast line...");
			iss >> doc;
			cout << endl << sp_2 << "Initial Document:" << endl;
			print(doc);

			FindAndReplace(doc, "line", "LINE");
			cout << endl << endl << sp_2 << "After FindAndReplace(line -> LINE):" << endl;
			print(doc);

			FindAndReplace(doc, "LINE", "STringSTringSTring");
			cout << endl << endl << sp_2 << "After FindAndReplace(LINE -> STringSTringSTring):" << endl;
			print(doc);

			FindAndReplace(doc, "STringSTringSTring", "ln");
			cout << endl << endl << sp_2 << "After FindAndReplace(STringSTringSTring -> ln):" << endl;
			print(doc);

			FindAndReplace(doc, "CASE", "_____________case_____________");
			cout << endl << endl << sp_2 << "After FindAndReplace(CASE -> _____________case_____________):" << endl;
			print(doc);

			FindAndReplace(doc, "document", "Doc");
			cout << endl << endl << sp_2 << "After FindAndReplace(document -> Doc):" << endl;
			print(doc);

			cout << endl << endl;
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

Text_iterator Document::begin()									// first character of first line
{
	return Text_iterator(line.begin(), line.begin()->begin());
}

Text_iterator Document::end()									// one beyond the last character of the last line
{
	auto last = line.end();
	--last;														// we know that the document is not empty
	return Text_iterator(last, last->end());
}


istream& operator>>(istream& is, Document& d)
{
	for (char ch; is.get(ch); ) {
		d.line.back().push_back(ch);							// add the character
		if (ch == '\n') d.line.push_back(Line{});				// add another line
	}
	if (d.line.back().size()) d.line.push_back(Line{});			// add final empty line
	return is;
}

Text_iterator& Text_iterator::operator++()
{
	++pos;														// proceed to next character
	if (pos == (*ln).end()) {
		++ln;													// proceed to next line
		pos = (*ln).begin();									// bad if ln==line.end(); so make sure it isn’t
	}
	return* this;
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s)
{
	if (s.size() == 0) return last;								// can’t find an empty string
	char first_char = s[0];
	while (true) {
		auto p = find(first, last, first_char);
		if (p == last || match(p, last, s)) return p;
		first = ++p;											// look at the next character
	}
}

bool match(Text_iterator first, Text_iterator last, const string& s)
{
	Text_iterator it = first;
	for (int i = 0; i < s.size(); i++) {
		if (it == last || *it != s[i]) return false;
		++it;
	}
	return true;
}

bool FindAndReplace(Document& doc, const string& find, const string& replace)
{
	Text_iterator pos = doc.begin();
	bool ret = false;
	while (pos != doc.end()) {
		pos = find_txt(pos, doc.end(), find);
		if (pos == doc.end()) return ret;
		else ret = true;
		pos = Replace(pos, find, replace);
		++pos;
	}
	return ret;
}

Text_iterator Replace(Text_iterator position, const string& find, const string& replace)
{
	list<Line>::iterator line = position.GetLine();
	Line::iterator it = position.GetPosition();
	int i;
	for (i = 0; i < find.size() && i < replace.size(); i++) {
		*it = replace[i];
		++it;
	}
	if (i < find.size()) line->erase(it, it + (find.size() - i));
	else if (i < replace.size()) line->insert(it, replace.begin() + i, replace.end());
	return Text_iterator{ line, line->begin() + i };
}
