/* Exercise 21.15 */

using namespace std;
using namespace Graph_lib;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

class Dictionary {
public:
	Dictionary() : pout{ &cout }, perr{ &cerr } {}
	bool AddWords(istream& is);
	void SetOutputStream(ostream& output, ostream& error) { pout = &output; perr = &error; }
	size_t GetSize() { return words.size(); }
	void Print();
	pair<string, int> CountOccurrences(const string& word);
	pair<string, int> MostFrequently();
	pair<string, int> LongestWord();
	pair<string, int> ShortestWord();
	vector<const pair<string, int>*> WordsStartingWith(const string& s);
	vector<const pair<string, int>*> NumberOfLetters(int n);
private:
	pair<string, bool> GetNextWord(istream& is);
	void CleanUpWordAndAdd(vector<pair<string, int>>& v, string& word);
	void Add(vector<pair<string, int>>& v, string& word, int first, int last);
	void Parse(vector<pair<string, int>>& v, string& word, int first, int last);
	void RemoveDuplicatesAndPlurals(vector<pair<string, int>>& v);
private:
	vector<pair<string, int>> words;
	ostream* pout;
	ostream* perr;
};

void SaveToFile(Dictionary& dict);

namespace Graph_lib {
	constexpr int defFontSize = 14;
	constexpr int defLineSpacing = defFontSize * 140 / 100;
	constexpr int defFont = int(Font::helvetica);
	constexpr int defFontBold = int(Font::helvetica_bold);

	struct MText : Shape {
		// the point is the top left of the first letter (first line)
		MText(Point x, int numberOfLines, int fontSize, int lineSpacing);

		void draw_lines() const;

		int NumberOfLines() const { return nLines; }
		void Resize(int numberOfLines);
		void HideAllString();
		void Hide() { show = false; }
		void Show() { show = true; }

		void Set(int index, const string& s, Font f = defFont, Color c = Color::black);

		void SetLabel(int index, const string& s) { lab[index] = s; showElem[index] = true; }
		string GetLabel(int index) const { return lab[index]; }

		void SetFont(int index, Font f) { fnt[index] = f; }
		Font GetFont(int index) const { return fnt[index]; }

		void SetColor(int index, Color c) { col[index] = c; }
		Color GetColor(int index) const { return col[index]; }

		void SetFontSize(int size) { fntSz = size; }
		int GetFontSize() const { return fntSz; }

		void SetLineSpacing(int lineSpacing) { lineSp = lineSpacing; }
		int GetLineSpacing() const { return lineSp; }
	private:
		vector<string> lab;
		vector<Font> fnt;
		vector<Color> col;
		vector<bool> showElem;
		int fntSz;
		int lineSp;
		int nLines;
		bool show;
	};

	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);
		bool wait_for_button();
	private:
		enum class Action {
			DO, CLEAR
		};
		void WordsStartingWith(Action action);
		void NumberOfLetters(Action action);
		void Reset(Text& text) { text.set_label(""); }
	private:
		Dictionary dict;

		In_box inboxInputFile;
		ifstream ifs;
		Button buttonOpenInput;

		In_box inboxOutputFile;
		ofstream ofs;
		Button buttonOpenOutput;

		In_box inboxInputString;
		Button buttonCountOccur;
		Button buttonMostFreq;
		Button buttonLongest;
		Button buttonShortest;
		Button buttonStartingWith;
		Button buttonStartingWithNext;
		Button buttonStartingWithClear;
		Button buttonNumberOfLetters;
		Button buttonNumberOfLettersNext;
		Button buttonNumberOfLettersClear;

		Text textOutput;
		MText mtextOutput;
		//ostringstream oss;

		Button buttonQuit;
		bool quitPushed;

		void OpenInputFile();
		void OpenOutputFile();
		void CountOccurrences();
		void MostFrequently();
		void LongestWord();
		void ShortestWord();
		void WordsStartingWithDo() { WordsStartingWith(Action::DO); }
		void WordsStartingWithClear() { WordsStartingWith(Action::CLEAR); }
		void NumberOfLettersDo() { NumberOfLetters(Action::DO); }
		void NumberOfLettersClear() { NumberOfLetters(Action::CLEAR); }
		
		void quit();
	};
}
