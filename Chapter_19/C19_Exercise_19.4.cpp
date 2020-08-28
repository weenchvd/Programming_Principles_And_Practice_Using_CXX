/* Exercise 19.4 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C19_Exercise_19.4.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

const char* space_c2 = "  ";
const char* space_c4 = "    ";
//const char* errMessageInputFile = "Error. Can't open input file: ";
//const char* errMessageOutputFile = "Error. Can't open output file: ";

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		LISTOFGODS
	};
	const string actionList = "\tList of actions:\n"
	"  (1) ListOfGods()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case LISTOFGODS: {
			Link<God>* norse_gods = new Link<God>(God{ "Thor", "Norse", "", "Mjolnir" });
			norse_gods = norse_gods->insert(new Link<God>(God{ "Odin", "Norse", "Eight-legged flying horse called Sleipner", "Spear called Gungnir" }));
			norse_gods = norse_gods->insert(new Link<God>(God{ "Zeus", "Greek", "", "Thunderbolt" }));
			norse_gods = norse_gods->insert(new Link<God>(God{ "Freia", "Norse", "", "" }));

			Link<God>* greek_gods = new Link<God>(God{ "Hera", "Greek", "", "" });
			greek_gods = greek_gods->insert(new Link<God>(God{ "Athena", "Greek", "", "" }));
			greek_gods = greek_gods->insert(new Link<God>(God{ "Mars", "Greek", "", "The spear of Mars" }));
			greek_gods = greek_gods->insert(new Link<God>(God{ "Poseidon", "Greek", "", "Trident" }));

			Link<God>* p = greek_gods->find("Mars");
			if (p) p->val.name = "Ares";

			// Move Zeus into his correct Pantheon: 
			{
				Link<God>* p = norse_gods->find("Zeus");
				if (p) {
					if (p == norse_gods) norse_gods = p->next();
					p->erase();
					greek_gods = greek_gods->insert(p);
				}
			}

			Link<God>* egyptian_gods = new Link<God>(God{ "Ra", "Egyptian", "", "" });
			egyptian_gods = egyptian_gods->insert(new Link<God>(God{ "Osiris", "Egyptian", "", "Crook and flail" }));
			egyptian_gods = egyptian_gods->insert(new Link<God>(God{ "Ptah", "Egyptian", "", "Djed" }));

			// Finally, let's print out those lists:
			cout << "Unordered lists:" << endl;
			print_all(norse_gods);
			cout << "\n";
			print_all(greek_gods);
			cout << "\n";
			print_all(egyptian_gods);
			cout << "\n";

			Link<God>* orderedNorseGods = nullptr;
			p = norse_gods;
			while (p) {
				norse_gods = p->next();
				p->erase();
				orderedNorseGods = orderedNorseGods->add_ordered(new Link<God>{
					God{ p->val.name, p->val.mythology, p->val.vehicle, p->val.weapon } });
				delete p;
				p = norse_gods;
			}
			while (orderedNorseGods && orderedNorseGods->previous()) orderedNorseGods = orderedNorseGods->previous();

			Link<God>* orderedGreekGods = nullptr;
			p = greek_gods;
			while (p) {
				greek_gods = p->next();
				p->erase();
				orderedGreekGods = orderedGreekGods->add_ordered(new Link<God>{
					God{ p->val.name, p->val.mythology, p->val.vehicle, p->val.weapon } });
				delete p;
				p = greek_gods;
			}
			while (orderedGreekGods && orderedGreekGods->previous()) orderedGreekGods = orderedGreekGods->previous();

			Link<God>* orderedEgyptianGods = nullptr;
			p = egyptian_gods;
			while (p) {
				egyptian_gods = p->next();
				p->erase();
				orderedEgyptianGods = orderedEgyptianGods->add_ordered(new Link<God>{
					God{ p->val.name, p->val.mythology, p->val.vehicle, p->val.weapon } });
				delete p;
				p = egyptian_gods;
			}
			while (orderedEgyptianGods && orderedEgyptianGods->previous()) orderedEgyptianGods = orderedEgyptianGods->previous();

			cout << endl << "Ordered lists:" << endl;
			print_all(orderedNorseGods);
			cout << endl;
			print_all(orderedGreekGods);
			cout << endl;
			print_all(orderedEgyptianGods);
			cout << endl;

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

// insert n before 'this' object
template<class T> Link<T>* Link<T>::insert(Link<T>* n)										// insert n before this object; return n
{
	if (n == 0) return this;
	if (this == 0) return n;
	n->succ = this;												// this object comes after n
	if (prev) prev->succ = n;
	n->prev = prev;												// this object's predecessor becomes n's predecessor
	prev = n;													// n becomes this object's predecessor
	return n;
}

// insert n after 'this' object
template<class T> Link<T>* Link<T>::add(Link<T>* n)
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->prev = this;
	if (succ) succ->prev = n;
	n->succ = succ;
	succ = n;
	return n;
}

template<class T> Link<T>* Link<T>::add_ordered(Link<T>* n)
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	Link* current = this;
	if (n->val.name < current->val.name) {
		while (current->prev && n->val < current->prev->val) current = current->prev;
		return current->insert(n);
	}
	else {
		while (current->succ && n->val > current->succ->val) current = current->succ;
		return current->add(n);
	}
}

// remove 'this' object from the list; return this's successor
template<class T> Link<T>* Link<T>::erase()
{
	if (this == 0) return 0;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
}

// find s in list; return 0 for "not found"
template<class T> Link<T>* Link<T>::find(const string& s)
{
	Link* p = this;
	while (p) {
		if (p->val == s) return p;
		p = p->succ;
	}
	return 0;
}

template<class T> void print_all(Link<T>* p)
{
	cout << "{ " << endl;
	while (p) {
		cout << space_c4 << p->val;
		if (p = p->next()) cout << endl;
	}
	cout << endl << " }";
}

ostream& operator<<(ostream& os, const God& g)
{
	os << g.name;
	if (g.mythology.size() > 0) os << ", " << g.mythology;
	if (g.vehicle.size() > 0) os << ", " << g.vehicle;
	if (g.weapon.size() > 0) os << ", " << g.weapon;
	return os;
}
