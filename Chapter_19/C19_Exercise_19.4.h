/* Exercise 19.4 */

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

bool operator>(const God& g1, const God& g2) { return (g1.name > g2.name); }
bool operator<(const God& g1, const God& g2) { return (g1.name < g2.name); }
bool operator==(const God& g, const string& s) { return (g.name == s); }
ostream& operator<<(ostream& os, const God& g);

template<class T> class Link {
public:
	T val;
	Link(const T& value, Link* p = nullptr, Link* s = nullptr)
		: val{ value }, prev{ p }, succ{ s } { }
	Link<T>* insert(Link<T>* n);
	Link<T>* add(Link<T>* n);
	Link<T>* add_ordered(Link<T>* n);
	Link<T>* erase();
	Link<T>* find(const string& s);
	const Link<T>* find(const string& s) const;					// find s in const list
	Link<T>* advance(int n) const;								// move n positions in list
	Link<T>* next() const { return succ; }
	Link<T>* previous() const { return prev; }
private:
	Link<T>* prev;
	Link<T>* succ;
};

template<class T> void print_all(Link<T>* p);
void ClearInput(istream& is);
