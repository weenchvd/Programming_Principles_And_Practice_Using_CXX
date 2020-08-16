/* Exercise 17.14 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C17_Exercise_17.14.h"

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
			norse_gods = (new Link("Odin"))->insert(norse_gods);
			norse_gods = (new Link("Zeus"))->insert(norse_gods);
			norse_gods = (new Link("Freia"))->insert(norse_gods);

			Link* greek_gods = new Link("Hera");
			greek_gods = (new Link("Athena"))->insert(greek_gods);
			greek_gods = (new Link("Mars"))->insert(greek_gods);
			greek_gods = (new Link("Poseidon"))->insert(greek_gods);

			Link* p = greek_gods->find("Mars");
			if (p) p->value = "Ares";

			// Move Zeus into his correct Pantheon: 
			{
				Link* p = norse_gods->find("Zeus");
				if (p) {
					norse_gods = p->erase(norse_gods);
					greek_gods = p->insert(greek_gods);
				}
			}

			norse_gods = (new Link("Loki"))->insert(norse_gods);
			norse_gods = (new Link("Ullr"))->insert(norse_gods);
			norse_gods = (new Link("Vili"))->insert(norse_gods);
			norse_gods = (new Link("Baldr"))->insert(norse_gods);
			norse_gods = (new Link("Forseti"))->insert(norse_gods);

			greek_gods = (new Link("Apollo"))->insert(greek_gods);
			greek_gods = (new Link("Dionysus"))->insert(greek_gods);
			greek_gods = (new Link("Hades"))->insert(greek_gods);
			greek_gods = (new Link("Hermes"))->insert(greek_gods);
			greek_gods = (new Link("Hephaestus"))->insert(greek_gods);

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

Link* Link::insert(Link* head)									// insert this object at the beginning of the list; return the pointer to the first object from the list
{
	if (this == nullptr) return head;
	succ = head;
	return this;
}

Link* Link::erase(Link* head)									// remove this object from the list; return the pointer to the first object from the list
{
	if (this == nullptr) return head;
	if (head == this)  return succ;
	Link* prev = head;
	while (prev && prev->succ != this) prev = prev->succ;
	if (prev == nullptr) return head;
	prev->succ = succ;
	return head;
}

Link* Link::find(const string& s)								// find s in list;
// return 0 for "not found"
{
	Link* p = this;
	while (p) {
		if (p->value == s) return p;
		p = p->succ;
	}
	return nullptr;
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
