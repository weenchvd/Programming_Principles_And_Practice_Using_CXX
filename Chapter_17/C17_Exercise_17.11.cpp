/* Exercise 17.11 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C17_Exercise_17.11.h"

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
			Link* norse_gods = new Link("Thor");
			norse_gods = norse_gods->insert(new Link("Odin"));
			norse_gods = norse_gods->insert(new Link("Zeus"));
			norse_gods = norse_gods->insert(new Link("Freia"));

			Link* greek_gods = new Link("Hera");
			greek_gods = greek_gods->insert(new Link("Athena"));
			greek_gods = greek_gods->insert(new Link("Mars"));
			greek_gods = greek_gods->insert(new Link("Poseidon"));

			Link* p = greek_gods->find("Mars");
			if (p) p->value = "Ares";

			// Move Zeus into his correct Pantheon: 
			{
				Link* p = norse_gods->find("Zeus");
				if (p) {
					if (p == norse_gods) norse_gods = p->next();
					p->erase();
					greek_gods = greek_gods->insert(p);
				}
			}

			norse_gods = norse_gods->insert(new Link("Loki"));
			norse_gods = norse_gods->insert(new Link("Ullr"));
			norse_gods = norse_gods->insert(new Link("Vili"));
			norse_gods = norse_gods->insert(new Link("Baldr"));
			norse_gods = norse_gods->insert(new Link("Forseti"));

			greek_gods = greek_gods->insert(new Link("Apollo"));
			greek_gods = greek_gods->insert(new Link("Dionysus"));
			greek_gods = greek_gods->insert(new Link("Hades"));
			greek_gods = greek_gods->insert(new Link("Hermes"));
			greek_gods = greek_gods->insert(new Link("Hephaestus"));

			// Finally, let's print out those lists:
			print_all(norse_gods);
			cout << "\n";
			print_all(greek_gods);
			cout << "\n";
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
		if (p->value == s) return p;
		p = p->succ;
	}
	return 0;
}

void print_all(Link* p)
{
	cout << "{ ";
	while (p) {
		cout << p->value;
		if (p = p->next()) cout << ", ";
	}
	cout << " }";
}
