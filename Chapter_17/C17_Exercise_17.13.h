/* Exercise 17.13 */

using namespace std;

struct God {
	God(const string& name)
		: name{ name } {}
	God(const string& name, const string& mythology, const string& vehicle, const string& weapon)
		: name{ name }, mythology{ mythology }, vehicle{ vehicle }, weapon{ weapon } {}
	string name;
	string mythology;
	string vehicle;
	string weapon;
};

class Link {
public:
	God god;
	Link(const God& god, Link* p = nullptr, Link* s = nullptr)
		: god{ god }, prev{ p }, succ{ s } { }
	Link* insert(Link* n);										// insert n before this object
	Link* add(Link* n);											// insert n after this object
	Link* add_ordered(Link* n);
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
