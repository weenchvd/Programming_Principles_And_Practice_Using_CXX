/* Exercise 20.10 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

using Line = vector<char>;					// a line is a vector of characters

enum class WordType {
	WHITESPACESEPARATED, CONSECUTIVEALPHABETIC
};

class Text_iterator;

struct Document {
	list<Line> line;						// a document is a list of lines
	Document() { line.push_back(Line{}); }
	Text_iterator begin();					// first character of first line
	Text_iterator end();					// one beyond the last character of the last line
	long long int NumberOfCharacters() const;
	long long int NumberOfWords(WordType type);
	long long int NumberOfWords(const vector<char>& spaces);
private:
	bool isIncluded(char ch, const vector<char>& spaces);
};

istream& operator>>(istream& is, Document& d);

class Text_iterator {						// keep track of line and character position within a line
	list<Line>::iterator ln;
	Line::iterator pos;
public:
	// start the iterator at line ll’s character position pp:
	Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		: ln{ ll }, pos{ pp } { }
	list<Line>::iterator GetLine() { return ln; }
	Line::iterator GetPosition() { return pos; }
	char& operator*() { return *pos; }
	Text_iterator& operator++();
	bool operator==(const Text_iterator& other) const { return ln == other.ln && pos == other.pos; }
	bool operator!=(const Text_iterator& other) const { return !(*this == other); }
};

void print(Document& d) { for (auto& p : d) cout << p; }
Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s);
bool match(Text_iterator first, Text_iterator last, const string& s);
bool FindAndReplace(Document& doc, const string& find, const string& replace);
Text_iterator Replace(Text_iterator position, const string& find, const string& replace);
