/* Exercise 21.15 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
#include<iomanip>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C21_Exercise_21.15.h"

using namespace std;

inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
try {
	constexpr int windowLength = 1280;
	constexpr int windowHeight = 1024;

	My_window mw{ Point{ 80, 0 }, windowLength, windowHeight, "Orders" };

	mw.wait_for_button();
	return 0;
}
catch (runtime_error& e) {
	cerr << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "Error. Exception\n";
	return 2;
}

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	inboxInputFile{ Point{ 200, 0 }, 300, 20, "Input file:" },
	buttonOpenInput{ Point{ 200, 20 }, 150, 20, "Add words from file",
		[](Address, Address pw) { reference_to<My_window>(pw).OpenInputFile(); } },

	inboxOutputFile{ Point{ 600, 0 }, 300, 20, "Output file:" },
	buttonOpenOutput{ Point{ 600, 20 }, 150, 20, "Record dictionary",
		[](Address, Address pw) { reference_to<My_window>(pw).OpenOutputFile(); } },

	inboxInputString{ Point{ 200, 60 }, 300, 20, "String:" },
	buttonCountOccur{ Point{ 200, 80 }, 300, 20, "Count occurrences",
		[](Address, Address pw) { reference_to<My_window>(pw).CountOccurrences(); } },
	buttonMostFreq{ Point{ 200, 100 }, 300, 20, "Most frequent occurrence",
		[](Address, Address pw) { reference_to<My_window>(pw).MostFrequently(); } },
	buttonLongest{ Point{ 200, 120 }, 300, 20, "The longest word",
		[](Address, Address pw) { reference_to<My_window>(pw).LongestWord(); } },
	buttonShortest{ Point{ 200, 140 }, 300, 20, "The shortest word",
		[](Address, Address pw) { reference_to<My_window>(pw).ShortestWord(); } },
	buttonStartingWith{ Point{ 200, 160 }, 300, 20, "Words starting with",
		[](Address, Address pw) { reference_to<My_window>(pw).WordsStartingWithDo(); } },
	buttonStartingWithNext{ Point{ 200, 160 }, 200, 20, "Next page",
		[](Address, Address pw) { reference_to<My_window>(pw).WordsStartingWithDo(); } },
	buttonStartingWithClear{ Point{ 400, 160 }, 100, 20, "Clear",
		[](Address, Address pw) { reference_to<My_window>(pw).WordsStartingWithClear(); } },
	buttonNumberOfLetters{ Point{ 200, 180 }, 300, 20, "Number of letters equal to",
		[](Address, Address pw) { reference_to<My_window>(pw).NumberOfLettersDo(); } },
	buttonNumberOfLettersNext{ Point{ 200, 180 }, 200, 20, "Next page",
		[](Address, Address pw) { reference_to<My_window>(pw).NumberOfLettersDo(); } },
	buttonNumberOfLettersClear{ Point{ 400, 180 }, 100, 20, "Clear",
		[](Address, Address pw) { reference_to<My_window>(pw).NumberOfLettersClear(); } },

	textOutput{ Point{ 200, 235 }, "" },
	mtextOutput{ Point{ 200, 240 }, 40, defFontSize, defLineSpacing },

	buttonQuit{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<My_window>(pw).quit(); } },
	quitPushed{ false }
{
	attach(inboxOutputFile);
	attach(buttonOpenOutput);

	attach(inboxInputFile);
	attach(buttonOpenInput);

	attach(inboxInputString);
	attach(buttonCountOccur);
	attach(buttonMostFreq);
	attach(buttonLongest);
	attach(buttonShortest);
	attach(buttonStartingWith);
	attach(buttonStartingWithNext);
	buttonStartingWithNext.hide();
	attach(buttonStartingWithClear);
	buttonStartingWithClear.hide();
	attach(buttonNumberOfLetters);
	attach(buttonNumberOfLettersNext);
	buttonNumberOfLettersNext.hide();
	attach(buttonNumberOfLettersClear);
	buttonNumberOfLettersClear.hide();

	textOutput.set_font(defFontBold);
	textOutput.set_font_size(defFontSize);
	textOutput.set_color(Color::black);
	attach(textOutput);
	attach(mtextOutput);

	attach(buttonQuit);

	//dict.SetOutputStream(oss, cerr);
}

void My_window::OpenInputFile()
{
	mtextOutput.Hide();
	if (ifs.is_open()) ifs.close();
	string file = inboxInputFile.get_string();
	ifs.open(file);
	if (!ifs) {
		textOutput.set_label("File is not open");
		textOutput.set_color(Color::dark_red);
		redraw();
		return;
	}
	if (!dict.AddWords(ifs)) {
		textOutput.set_label("Error adding words");
		textOutput.set_color(Color::dark_red);
		redraw();
		return;
	}
	textOutput.set_label("Words from file have been successfully added");
	textOutput.set_color(Color::dark_green);
	redraw();
}

void My_window::OpenOutputFile()
{
	mtextOutput.Hide();
	if (ofs.is_open()) ofs.close();
	string file = inboxOutputFile.get_string();
	ofs.open(file);
	if (!ofs) {
		textOutput.set_label("File is not open");
		textOutput.set_color(Color::dark_red);
	}
	dict.SetOutputStream(ofs, cerr);
	dict.Print();
	dict.SetOutputStream(cout, cerr);
	textOutput.set_label("The dictionary have been successfully recorded");
	textOutput.set_color(Color::dark_green);
	redraw();
}

void My_window::CountOccurrences()
{
	mtextOutput.Hide();
	string s = inboxInputString.get_string();
	if (s.size() == 0) {
		textOutput.set_label("Nothing entered");
		textOutput.set_color(Color::dark_red);
		redraw();
		return;
	}
	if (dict.GetSize() == 0) {
		textOutput.set_label("The dictionary is empty");
		textOutput.set_color(Color::dark_red);
		redraw();
		return;
	}
	pair<string, int> word = dict.CountOccurrences(s);
	ostringstream oss;
	oss << "The number of occurences of \"" << word.first << "\" is " << word.second;
	textOutput.set_label(oss.str());
	textOutput.set_color(Color::dark_green);
	redraw();
}

void My_window::MostFrequently()
{
	mtextOutput.Hide();
	pair<string, int> word = dict.MostFrequently();
	if (word.second == 0) {
		textOutput.set_label("The dictionary is empty");
		textOutput.set_color(Color::dark_red);
		redraw();
		return;
	}
	ostringstream oss;
	oss << "The word with the most frequent occurrence: " << word.first << " (" << word.second << " times)";
	textOutput.set_label(oss.str());
	textOutput.set_color(Color::dark_green);
	redraw();
}

void My_window::LongestWord()
{
	mtextOutput.Hide();
	pair<string, int> word = dict.LongestWord();
	if (word.second == 0) {
		textOutput.set_label("The dictionary is empty");
		textOutput.set_color(Color::dark_red);
		redraw();
		return;
	}
	ostringstream oss;
	oss << "The longest word: " << word.first << " (number of letters: " << word.first.size() << ")";
	textOutput.set_label(oss.str());
	textOutput.set_color(Color::dark_green);
	redraw();
}

void My_window::ShortestWord()
{
	mtextOutput.Hide();
	pair<string, int> word = dict.ShortestWord();
	if (word.second == 0) {
		textOutput.set_label("The dictionary is empty");
		textOutput.set_color(Color::dark_red);
		redraw();
		return;
	}
	ostringstream oss;
	oss << "The shortest word: " << word.first << " (number of letters: " << word.first.size() << ")";
	textOutput.set_label(oss.str());
	textOutput.set_color(Color::dark_green);
	redraw();
}

void My_window::WordsStartingWith(Action action)
{
	static int i = 0;
	static vector<const pair<string, int>*> v;
	if (action == Action::CLEAR) {
		i = 0;
		mtextOutput.Hide();
		buttonStartingWithNext.hide();
		buttonStartingWithClear.hide();
		buttonStartingWith.show();
		redraw();
		return;
	}
	if (i == 0) {
		string s = inboxInputString.get_string();
		if (s.size() == 0) {
			textOutput.set_label("Nothing entered");
			textOutput.set_color(Color::dark_red);
			redraw();
			return;
		}
		if (dict.GetSize() == 0) {
			textOutput.set_label("The dictionary is empty");
			textOutput.set_color(Color::dark_red);
			redraw();
			return;
		}
		v = dict.WordsStartingWith(s);
		if (v.size() == 0) {
			textOutput.set_label("No matches found");
			textOutput.set_color(Color::dark_green);
			redraw();
			return;
		}
		ostringstream oss;
		oss << "Words starting with \"" << s << "\":";
		textOutput.set_label(oss.str());
		textOutput.set_color(Color::dark_green);
	}
	mtextOutput.Show();
	mtextOutput.HideAllString();
	buttonStartingWithNext.show();
	buttonStartingWithClear.show();
	buttonStartingWith.hide();
	int j;
	for (j = 0; j < mtextOutput.NumberOfLines(); ++j) {
		if (i < v.size()) mtextOutput.Set(j, v[i++]->first);
		else break;
	}
	if (i >= v.size() || j >= mtextOutput.NumberOfLines() && i + 1 >= v.size()) {
		i = 0;
		buttonStartingWithNext.hide();
		buttonStartingWithClear.hide();
		buttonStartingWith.show();
	}
	redraw();
}

void My_window::NumberOfLetters(Action action)
{
	static int i = 0;
	static vector<const pair<string, int>*> v;
	if (action == Action::CLEAR) {
		i = 0;
		mtextOutput.Hide();
		buttonNumberOfLettersNext.hide();
		buttonNumberOfLettersClear.hide();
		buttonNumberOfLetters.show();
		redraw();
		return;
	}
	if (i == 0) {
		string s = inboxInputString.get_string();
		if (s.size() == 0) {
			textOutput.set_label("Nothing entered");
			textOutput.set_color(Color::dark_red);
			redraw();
			return;
		}
		istringstream iss;
		iss.str(s);
		int number;
		if (!(iss >> number)) {
			textOutput.set_label("Error. Incorrect input");
			textOutput.set_color(Color::dark_red);
			redraw();
			return;
		}
		if (dict.GetSize() == 0) {
			textOutput.set_label("The dictionary is empty");
			textOutput.set_color(Color::dark_red);
			redraw();
			return;
		}
		v = dict.NumberOfLetters(number);
		if (v.size() == 0) {
			textOutput.set_label("No matches found");
			textOutput.set_color(Color::dark_green);
			redraw();
			return;
		}
		ostringstream oss;
		oss << "The words with number of letters equal to " << number << ":";
		textOutput.set_label(oss.str());
		textOutput.set_color(Color::dark_green);
	}
	mtextOutput.Show();
	mtextOutput.HideAllString();
	buttonNumberOfLettersNext.show();
	buttonNumberOfLettersClear.show();
	buttonNumberOfLetters.hide();
	int j;
	for (j = 0; j < mtextOutput.NumberOfLines(); ++j) {
		if (i < v.size()) mtextOutput.Set(j, v[i++]->first);
		else break;
	}
	if (i >= v.size() || j >= mtextOutput.NumberOfLines() && i + 1 >= v.size()) {
		i = 0;
		buttonNumberOfLettersNext.hide();
		buttonNumberOfLettersClear.hide();
		buttonNumberOfLetters.show();
	}
	redraw();
}

bool My_window::wait_for_button()
{
	show();
	quitPushed = false;
	while (!quitPushed) Fl::wait();
	Fl::redraw();
	return quitPushed;
}

void My_window::quit()
{
	quitPushed = true;
	hide();
}

#include <FL/Fl_Output.H>
string Graph_lib::In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	string s;
	return s.assign(pi.value());
}

Graph_lib::MText::MText(Point x, int numberOfLines, int fontSize, int lineSpacing)
	: nLines{ numberOfLines }, fntSz{ fontSize }, lineSp{ lineSpacing }, show{ true }
{
	add(x);
	lab.resize(numberOfLines);
	fnt.resize(numberOfLines, Font{ defFont });
	col.resize(numberOfLines, Color{ Color::black });
	showElem.resize(numberOfLines, false);
}

void Graph_lib::MText::draw_lines() const
{
	if (show == false) return;
	int ofnt = fl_font();
	int osz = fl_size();
	for (int i = 0; i < nLines; ++i) {
		if (showElem[i]) {
			fl_color(col[i].as_int());
			fl_font(fnt[i].as_int(), fntSz);
			fl_draw(lab[i].c_str(), point(0).x, point(0).y + lineSp * i + (lineSp * 90) / 100);
		}
	}
	fl_font(ofnt, osz);
}

void Graph_lib::MText::Resize(int numberOfLines)
{
	lab.resize(numberOfLines);
	fnt.resize(numberOfLines, Font{ defFont });
	col.resize(numberOfLines, Color{ Color::black });
	showElem.resize(numberOfLines, false);
	nLines = numberOfLines;
}

void Graph_lib::MText::HideAllString()
{
	for (int i = 0; i < nLines; ++i) showElem[i] = false;
}

void Graph_lib::MText::Set(int index, const string& s, Font f, Color c)
{
	lab[index] = s;
	fnt[index] = f;
	col[index] = c;
	showElem[index] = true;
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
		*pout << words[i].first << " (" << words[i].second << ")" << endl;
	}
}

pair<string, int> Dictionary::CountOccurrences(const string& word)
{
	for (int i = 0; i < words.size(); ++i) {
		if (words[i].first == word) return words[i];
	}
	return { word, 0 };
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

#undef max;
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

