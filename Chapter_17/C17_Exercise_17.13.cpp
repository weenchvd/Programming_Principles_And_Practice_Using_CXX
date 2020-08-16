/* Exercise 17.13 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C17_Exercise_17.13.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

const string errMessageInputFile = "Error. Can't open input file: ";
const string errMessageOutputFile = "Error. Can't open output file: ";

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
	const char* indent2 = "  ";
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case LISTOFGODS: {
			Link* norse_gods = new Link(God{ "Thor", "Norse", "", "Mjolnir" });
			norse_gods = norse_gods->insert(new Link(God{ "Odin", "Norse", "Eight-legged flying horse called Sleipner", "Spear called Gungnir" }));
			norse_gods = norse_gods->insert(new Link(God{ "Zeus", "Greek", "", "Thunderbolt" }));
			norse_gods = norse_gods->insert(new Link(God{ "Freia", "Norse", "", "" }));

			Link* greek_gods = new Link(God{ "Hera", "Greek", "", "" });
			greek_gods = greek_gods->insert(new Link(God{ "Athena", "Greek", "", "" }));
			greek_gods = greek_gods->insert(new Link(God{ "Mars", "Greek", "", "The spear of Mars" }));
			greek_gods = greek_gods->insert(new Link(God{ "Poseidon", "Greek", "", "Trident" }));

			Link* p = greek_gods->find("Mars");
			if (p) p->god.name = "Ares";

			// Move Zeus into his correct Pantheon: 
			{
				Link* p = norse_gods->find("Zeus");
				if (p) {
					if (p == norse_gods) norse_gods = p->next();
					p->erase();
					greek_gods = greek_gods->insert(p);
				}
			}

			Link* egyptian_gods = new Link(God{ "Ra", "Egyptian", "", "" });
			egyptian_gods = egyptian_gods->insert(new Link(God{ "Osiris", "Egyptian", "", "Crook and flail" }));
			egyptian_gods = egyptian_gods->insert(new Link(God{ "Ptah", "Egyptian", "", "Djed" }));

			// Finally, let's print out those lists:
			cout << "Unordered lists:" << endl;
			print_all(norse_gods);
			cout << "\n";
			print_all(greek_gods);
			cout << "\n";
			print_all(egyptian_gods);
			cout << "\n";

			Link* orderedNorseGods = nullptr;
			p = norse_gods;
			while (p) {
				norse_gods = p->next();
				p->erase();
				orderedNorseGods = orderedNorseGods->add_ordered(new Link{
					God{ p->god.name, p->god.mythology, p->god.vehicle, p->god.weapon } });
				delete p;
				p = norse_gods;
			}
			while (orderedNorseGods && orderedNorseGods->previous()) orderedNorseGods = orderedNorseGods->previous();

			Link* orderedGreekGods = nullptr;
			p = greek_gods;
			while (p) {
				greek_gods = p->next();
				p->erase();
				orderedGreekGods = orderedGreekGods->add_ordered(new Link{
					God{ p->god.name, p->god.mythology, p->god.vehicle, p->god.weapon } });
				delete p;
				p = greek_gods;
			}
			while (orderedGreekGods && orderedGreekGods->previous()) orderedGreekGods = orderedGreekGods->previous();

			Link* orderedEgyptianGods = nullptr;
			p = egyptian_gods;
			while (p) {
				egyptian_gods = p->next();
				p->erase();
				orderedEgyptianGods = orderedEgyptianGods->add_ordered(new Link{
					God{ p->god.name, p->god.mythology, p->god.vehicle, p->god.weapon } });
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

Link* Link::insert(Link* n)										// insert n before this object; return n
{
	if (n == 0) return this;
	if (this == 0) return n;
	n->succ = this;												// this object comes after n
	if (prev) prev->succ = n;
	n->prev = prev;												// this object's predecessor becomes n's predecessor
	prev = n;													// n becomes this object's predecessor
	return n;
}

Link* Link::add(Link* n)
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->prev = this;
	if (succ) succ->prev = n;
	n->succ = succ;
	succ = n;
	return n;
}

Link* Link::add_ordered(Link* n)
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	Link* current = this;
	if (n->god.name < current->god.name) {
		while (current->prev && n->god.name < current->prev->god.name) current = current->prev;
		return current->insert(n);
	}
	else {
		while (current->succ && n->god.name > current->succ->god.name) current = current->succ;
		return current->add(n);
	}
}

Link* Link::erase()												// remove this object from the list; return this's successor
{
	if (this == 0) return 0;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
}

Link* Link::find(const string& s)								// find s in list;
// return 0 for "not found"
{
	Link* p = this;
	while (p) {
		if (p->god.name == s) return p;
		p = p->succ;
	}
	return 0;
}

void print_all(Link* p)
{
	constexpr char* space4 = "    ";
	cout << "{ " << endl;
	while (p) {
		cout << space4 << p->god.name;
		if (p->god.mythology.size() > 0) cout << ", " << p->god.mythology;
		if (p->god.vehicle.size() > 0) cout << ", " << p->god.vehicle;
		if (p->god.weapon.size() > 0) cout << ", " << p->god.weapon;
		if (p = p->next()) cout << endl;
	}
	cout << endl << " }";
}
