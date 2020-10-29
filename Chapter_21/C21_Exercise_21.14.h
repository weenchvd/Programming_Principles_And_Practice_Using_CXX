/* Exercise 21.14 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

class Dictionary {
public:
	Dictionary() : pout{ &cout }, perr{ &cerr } {}
	bool AddWords(istream& is);
	void SetOutputStream(ostream& output, ostream& error) { pout = &output; perr = &error; }
	void Print();
	long long int CountOccurrences(const string& word);
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
