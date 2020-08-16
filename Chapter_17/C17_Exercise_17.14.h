/* Exercise 17.14 */

using namespace std;

class Link {
public:
	string value;
	Link(const string& v, Link* s = nullptr)
		: value{ v }, succ{ s } { }
	Link* insert(Link* head);							// insert n before this object
	Link* add(Link* n);											// insert n after this object
	Link* erase(Link* head);									// remove this object from list
	Link* find(const string& s);								// find s in list
	const Link* find(const string& s) const;					// find s in const list
	Link* advance(int n) const;									// move n positions in list
	Link* next() const { return succ; }
private:
	Link* succ;

	void EraseNextPointer() { succ = nullptr; }
};

void print_all(Link* p);
void ClearInput(istream& is);
