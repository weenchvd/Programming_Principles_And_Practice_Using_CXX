/* Exercise 21.13 */

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
private:
	pair<string, bool> GetNextWord(istream& is);
	void CleanUpWordAndAdd(vector<string>& v, string& word);
	void Add(vector<string>& v, string& word, int first, int last);
	void Parse(vector<string>& v, string& word, int first, int last);
	void RemoveDuplicatesAndPlurals(vector<string>& v);
private:
	vector<string> words;
	ostream* pout;
	ostream* perr;
};

void SaveToFile(Dictionary& dict);
