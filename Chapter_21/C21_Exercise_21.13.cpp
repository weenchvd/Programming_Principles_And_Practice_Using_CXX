/* Exercise 21.13 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<vector>
#include<cctype>
#include<algorithm>
#include"C21_Exercise_21.13.h"

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
		"  (1) AddWords(), (2) Print(), (3) SaveToFile(),\n"
		"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	Dictionary dict;
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
			cout << sp_2 << "Please enter the file name: ";
			string file;
			getline(cin, file);
			ifstream ifs;
			ifs.open(file);
			if (!ifs) {
				cout << sp_4 << "Error. Can't open file: " + file << endl;
				break;
			}
			if (dict.AddWords(ifs)) cout << sp_4 << "Succsess!" << endl;
			else cout << sp_4 << "Failure" << endl;

			cout << vsp_2;
			break;
		}
		case CASE2:
			dict.Print();
			break;
		case CASE3:
			SaveToFile(dict);
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

bool Dictionary::AddWords(istream& is)
{
	vector<string> words2;
	while (true) {
		pair<string, bool> word = GetNextWord(is);
		if (!word.second) return false;
		if (word.first.size() == 0) break;
		CleanUpWordAndAdd(words2, word.first);
	}
	sort(words2.begin(), words2.end());
	RemoveDuplicatesAndPlurals(words2);
	if (words.size() == 0) words = words2;
	else {
		vector<string> result;
		result.resize(words.size() + words2.size());
		merge(words.begin(), words.end(), words2.begin(), words2.end(), result.begin());
		RemoveDuplicatesAndPlurals(result);
		words = result;
	}
	return true;
}

pair<string, bool> Dictionary::GetNextWord(istream& is)
{
	string word;
	while (true) {
		char ch;
		is.get(ch);
		if (is.eof()) {
			if (word.size() > 0) return pair<string, bool>{ word, true };
			else return { string{ "" }, true };
		}
		if (!is) {
			*perr << "\t\t" << "Read error" << endl;
			return { string{ "" }, false };
		}
		ch = tolower(ch);
		if (!isspace(ch)) {
			word += ch;
			continue;
		}
		else if (word.size() == 0) continue;
		return { word, true };
	}
}

void Dictionary::CleanUpWordAndAdd(vector<string>& v, string& word)
{
	// !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
	vector<string> temp;
	int pos = 0;
	int i = 0;
	for (i = 0; i < word.size(); ++i) {
		if (!ispunct(word[i])) continue;
		if (word[i] == '\'') {
			if (i - 1 >= 0 && word[i - 1] == 'n' &&
				i + 1 < word.size() && word[i + 1] == 't' &&
				i + 2 == word.size()) {
				Parse(temp, word, pos, i + 2);
				pos = i;
				break;
			}
			else if (i + 1 < word.size() && word[i + 1] == 's' && i + 2 == word.size()) break;
		}
		else if (word[i] == ',' || word[i] == '.') {
			if (i - 1 >= 0 && isdigit(word[i - 1]) &&
				i + 1 < word.size() && isdigit(word[i + 1])) continue;
		}
		Add(temp, word, pos, i);
		pos += i - pos + 1;
	}
	Add(temp, word, pos, i);
	for (int i = 0; i < temp.size(); ++i) v.push_back(temp[i]);
}

// range [first : last)
void Dictionary::Add(vector<string>& v, string& word, int first, int last)
{
	string s;
	while (first < last) s += word[first++];
	if (s.size() > 0) v.push_back(s);
}

// range [first : last)
void Dictionary::Parse(vector<string>& v, string& word, int first, int last)
{
	string s;
	while (first < last) s += word[first++];
	if (s == "don't") { v.push_back("do"); v.push_back("not"); }
	else if (s == "doesn't") { v.push_back("does"); v.push_back("not"); }
	else if (s == "didn't") { v.push_back("did"); v.push_back("not"); }
	else if (s == "shouldn't") { v.push_back("should"); v.push_back("not"); }
	else if (s == "won't") { v.push_back("will"); v.push_back("not"); }
	else if (s == "wasn't") { v.push_back("was"); v.push_back("not"); }
	else if (s == "weren't") { v.push_back("were"); v.push_back("not"); }
	else if (s == "isn't") { v.push_back("is"); v.push_back("not"); }
	else if (s == "aren't") { v.push_back("are"); v.push_back("not"); }
	else if (s == "can't") { v.push_back("can"); v.push_back("not"); }
	else if (s.size() > 0) v.push_back(s);
}

void Dictionary::RemoveDuplicatesAndPlurals(vector<string>& v)
{
	for (vector<string>::iterator it = ++v.begin(); it != v.end(); ++it) {
		if ((it - 1)->size() == it->size() && *(it - 1) == *it) {
			auto temp = it--;
			v.erase(temp);
		}
		else if ((it - 1)->size() == it->size() - 1 && (*it)[it->size() - 1] == 's') {
			string s;
			for (int i = 0; i < it->size() - 1; ++i) s += (*it)[i];
			if (*(it - 1) == s) {
				auto temp = it--;
				v.erase(temp);
			}
		}
	}
}

void Dictionary::Print()
{
	for (int i = 0; i < words.size(); ++i) *pout << words[i] << endl;
}

void SaveToFile(Dictionary& dict)
{
	cout << endl;
	cout << sp_2 << "Please enter the file name: ";
	string file;
	getline(cin, file);
	ofstream ofs;
	ofs.open(file);
	if (!ofs) {
		cout << sp_4 << "Error. Can't open file: " + file << endl;
		return;
	}
	dict.SetOutputStream(ofs, cerr);
	dict.Print();
	dict.SetOutputStream(cout, cerr);
	cout << sp_4 << "Succsess!" << endl;
}
