/* Exercise 17.11 */

using namespace std;

class Link {
public:
	string value;
	Link(const string& v, Link* p = nullptr, Link* s = nullptr)
		: value{ v }, prev{ p }, succ{ s } { }
	Link* insert(Link* n);										// insert n before this object
	Link* add(Link* n);											// insert n after this object
	Link* erase();												// remove this object from list
	Link* find(const string& s);								// find s in list
	const Link* find(const string& s) const;					// find s in const list
	Link* advance(int n) const;									// move n positions in list
	Link* next() const { return succ; }
	Link* previous() const { return prev; }
private:
	Link* prev;
	Link* succ;
};

void print_all(Link* p);
void ClearInput(istream& is);
