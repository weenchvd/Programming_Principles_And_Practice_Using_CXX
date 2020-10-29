/* Exercise 21.14 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<vector>
#include<cctype>
#include<algorithm>
#include"C21_Exercise_21.14.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const string actionList = "\tList of actions:\n"
		"  (1) AddWords(), (2) Print(), (3) SaveToFile(),\n"
		"  (4) CountOccurrences(), (5) MostFrequently(), (6) LongestWord(), (7) ShortestWord(),\n"
		"  (8) WordsStartingWith(), (9) NumberOfLetters(),\n"
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
		case CASE4: {
			cout << endl;
			cout << sp_2 << "Please enter a search term: ";
			string word;
			getline(cin, word);
			if (word.size() == 0) {
				cout << sp_4 << "Error. Incorrect input" << endl;
				break;
			}
			long long int count = dict.CountOccurrences(word);
			cout << sp_4 << "Number of occurences of \"" << word << "\" is " << count << endl;
			break;
		}
		case CASE5: {
			cout << endl;
			pair<string, int> mostFreq = dict.MostFrequently();
			if (mostFreq.second == 0) {
				cout << sp_4 << "The dictionary is empty" << endl;
			}
			else {
				cout << sp_4 << "The word with the most frequent occurrence: " << mostFreq.first << " (" <<
					mostFreq.second << " times)" << endl;
			}
			break;
		}
		case CASE6: {
			cout << endl;
			pair<string, int> longestWord = dict.LongestWord();
			if (longestWord.second == 0) {
				cout << sp_4 << "The dictionary is empty" << endl;
			}
			else {
				cout << sp_4 << "The longest word: " << longestWord.first << " (number of letters: " <<
					longestWord.first.size() << ")" << endl;
			}
			break;
		}
		case CASE7: {
			cout << endl;
			pair<string, int> shortestWord = dict.ShortestWord();
			if (shortestWord.second == 0) {
				cout << sp_4 << "The dictionary is empty" << endl;
			}
			else {
				cout << sp_4 << "The shortest word: " << shortestWord.first << " (number of letters: " <<
					shortestWord.first.size() << ")" << endl;
			}
			break;
		}
		case CASE8: {
			cout << endl;
			cout << sp_2 << "Please enter a search term: ";
			string expression;
			getline(cin, expression);
			if (expression.size() == 0) {
				cout << sp_4 << "Error. Incorrect input" << endl;
				break;
			}
			vector<const pair<string, int>*> v = dict.WordsStartingWith(expression);
			if (v.size() == 0) {
				cout << sp_4 << "No matches found or the dictionary is empty" << endl;
			}
			else {
				cout << sp_4 << "Words starting with \"" << expression << "\":" << endl;
				for (int i = 0; i < v.size(); ++i) {
					cout << sp_6 << v[i]->first << endl;
				}
			}
			break;
		}
		case CASE9: {
			cout << endl;
			cout << sp_2 << "Please enter a number: ";
			int number;
			if (!(cin >> number)) {
				cout << sp_4 << "Error. Incorrect input" << endl;
				break;
			}
			vector<const pair<string, int>*> v = dict.NumberOfLetters(number);
			if (v.size() == 0) {
				cout << sp_4 << "No matches found or the dictionary is empty" << endl;
			}
			else {
				cout << sp_4 << "The words with number of letters equal to " << number << ":" << endl;
				for (int i = 0; i < v.size(); ++i) {
					cout << sp_6 << v[i]->first << endl;
				}
			}
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

bool Dictionary::AddWords(istream& is)
{
	vector<pair<string, int>> words2;
	while (true) {
		pair<string, bool> word = GetNextWord(is);
		if (!word.second) return false;
		if (word.first.size() == 0) break;
		CleanUpWordAndAdd(words2, word.first);
	}
	sort(words2.begin(), words2.end(),
		[](const pair<string, int>& a, const pair<string, int>& b) { return a.first < b.first; });
	RemoveDuplicatesAndPlurals(words2);
	if (words.size() == 0) words = words2;
	else {
		vector<pair<string, int>> result;
		result.resize(words.size() + words2.size());
		merge(words.begin(), words.end(), words2.begin(), words2.end(), result.begin(),
			[](const pair<string, int>& a, const pair<string, int>& b) { return a.first < b.first; });
		RemoveDuplicatesAndPlurals(result);
		words = result;
	}
	return true;
}

void Dictionary::Print()
{
	for (int i = 0; i < words.size(); ++i) {
		*pout << words[i].first << "(" << words[i].second << ")" << endl;
	}
}

long long int Dictionary::CountOccurrences(const string& word)
{
	for (int i = 0; i < words.size(); ++i) {
		if (words[i].first == word) return words[i].second;
	}
	return 0;
}

pair<string, int> Dictionary::MostFrequently()
{
	if (words.size() == 0) return { "", 0 };
	int index = 0;
	int count = 0;
	for (int i = 0; i < words.size(); ++i) {
		if (words[i].second > count) {
			count = words[i].second;
			index = i;
		}
	}
	return words[index];
}

pair<string, int> Dictionary::LongestWord()
{
	if (words.size() == 0) return { "", 0 };
	int index = 0;
	int size = 0;
	for (int i = 0; i < words.size(); ++i) {
		if (words[i].first.size() > size) {
			size = words[i].first.size();
			index = i;
		}
	}
	return words[index];
}

pair<string, int> Dictionary::ShortestWord()
{
	if (words.size() == 0) return { "", 0 };
	int index = 0;
	int size = numeric_limits<int>::max();
	for (int i = 0; i < words.size(); ++i) {
		if (words[i].first.size() < size) {
			size = words[i].first.size();
			index = i;
		}
	}
	return words[index];
}

vector<const pair<string, int>*> Dictionary::WordsStartingWith(const string& s)
{
	vector<const pair<string, int>*> ret;
	for (int i = 0; i < words.size(); ++i) {
		int j = 0;
		for (; j < s.size(); ++j) {
			if (j >= words[i].first.size() || words[i].first[j] != s[j]) break;
		}
		if (j >= s.size()) ret.push_back(&words[i]);
	}
	return ret;
}

vector<const pair<string, int>*> Dictionary::NumberOfLetters(int n)
{
	vector<const pair<string, int>*> ret;
	for (int i = 0; i < words.size(); ++i) {
		if (words[i].first.size() == n) ret.push_back(&words[i]);
	}
	return ret;
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

void Dictionary::CleanUpWordAndAdd(vector<pair<string, int>>& v, string& word)
{
	// !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
	vector<pair<string, int>> temp;
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
void Dictionary::Add(vector<pair<string, int>>& v, string& word, int first, int last)
{
	string s;
	while (first < last) s += word[first++];
	if (s.size() > 0) v.push_back({ s, 1 });
}

// range [first : last)
void Dictionary::Parse(vector<pair<string, int>>& v, string& word, int first, int last)
{
	string s;
	while (first < last) s += word[first++];
	if (s == "don't") { v.push_back({ "do", 1 }); v.push_back({ "not", 1 }); }
	else if (s == "doesn't") { v.push_back({ "does", 1 }); v.push_back({ "not", 1 }); }
	else if (s == "didn't") { v.push_back({ "did", 1 }); v.push_back({ "not", 1 }); }
	else if (s == "shouldn't") { v.push_back({ "should", 1 }); v.push_back({ "not", 1 }); }
	else if (s == "won't") { v.push_back({ "will", 1 }); v.push_back({ "not", 1 }); }
	else if (s == "wasn't") { v.push_back({ "was", 1 }); v.push_back({ "not", 1 }); }
	else if (s == "weren't") { v.push_back({ "were", 1 }); v.push_back({ "not", 1 }); }
	else if (s == "isn't") { v.push_back({ "is", 1 }); v.push_back({ "not", 1 }); }
	else if (s == "aren't") { v.push_back({ "are", 1 }); v.push_back({ "not", 1 }); }
	else if (s == "can't") { v.push_back({ "can", 1 }); v.push_back({ "not", 1 }); }
	else if (s.size() > 0) v.push_back({ s, 1 });
}

void Dictionary::RemoveDuplicatesAndPlurals(vector<pair<string, int>>& v)
{
	for (vector<pair<string, int>>::iterator it = ++v.begin(); it != v.end(); ++it) {
		if ((it - 1)->first.size() == it->first.size() && (it - 1)->first == it->first) {
			auto temp = it--;
			it->second += temp->second;
			v.erase(temp);
		}
		else if ((it - 1)->first.size() == it->first.size() - 1 && it->first[it->first.size() - 1] == 's') {
			string s;
			for (int i = 0; i < it->first.size() - 1; ++i) s += it->first[i];
			if ((it - 1)->first == s) {
				auto temp = it--;
				it->second += temp->second;
				v.erase(temp);
			}
		}
	}
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

