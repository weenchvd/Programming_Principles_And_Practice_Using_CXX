/* Exercise 18.11 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include<cmath>
#include"C18_Exercise_18.11.h"

using namespace std;
using namespace OrderedList;

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
		PRINT, FIND, ADD, REMOVE
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Print(), (2) Find(), (3) Add(), (4) Remove()\n"
		"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	const char* space2 = "  ";
	const char* space4 = "    ";
	SkipList sl;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case PRINT: {
			sl.Print();
			break;
		}
		case FIND: {
			cout << "\nPlease enter the number to find: ";
			int n;
			if (!(cin >> n)) { ClearInput(cin); error("Error. Incorrect input"); }
			char ch;
			cin.get(ch);
			DataNode* dn = sl.Find(n);
			if (dn != nullptr) {
				cout << space4 << "num == " << dn->GetNumber() << ", s == " << dn->GetString() << endl;
			}
			else cout << space4 << "Not found" << endl;
			break;
		}
		case ADD: {
			cout << "\nPlease enter the number: ";
			int n;
			if (!(cin >> n)) { ClearInput(cin); error("Error. Incorrect input"); }
			char ch;
			cin.get(ch);
			cout << "Please enter the string in English (only ASCII): ";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			sl.Add(n, s);
			break;
		}
		case REMOVE: {
			cout << "\nPlease enter the number to remove: ";
			int n;
			if (!(cin >> n)) { ClearInput(cin); error("Error. Incorrect input"); }
			char ch;
			cin.get(ch);
			sl.Remove(n);
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

void SkipList::Print() const
{
	const string horizontalLine = "------------------------------------------------------------";
	LineNode* e = el;
	LineNode* n = nl;
	int i = 0;
	while (n != nullptr) {
		cout << horizontalLine << endl;
		if (e != nullptr && e->bottom == n) {
			cout << setw(14) << "Express line:" << " ";
			Print(e, 15);
			e = e->right;
		}
		cout << setw(14) << "Normal line:" << " ";
		Print(n, 15);
		cout << setw(14) << "Data:" << " ";
		Print(n->data, 15);
		n = n->right;
		i++;
	}
	cout << horizontalLine << endl;
	cout << "Quantity: " << i << endl;
	cout << horizontalLine << endl;
}

void SkipList::Print(LineNode* node, int shift) const
{
	cout << setw(8) << static_cast<void*>(node) << " " << setw(6) << "rigth" << " -> "
		<< PrintAddress(static_cast<void*>(node->right)) << endl;
	cout << setw(30) << "bottom" << " -> " << PrintAddress(static_cast<void*>(node->bottom)) << endl;
	cout << setw(30) << "data" << " -> " << PrintAddress(static_cast<void*>(node->data)) << endl;
}

void SkipList::Print(DataNode* node, int shift) const
{
	cout << setw(8) << static_cast<void*>(node) << " " << setw(6) << "num" << " == " << node->num << endl;
	cout << setw(30) << "s" << " == " << node->s << endl;
}

string SkipList::PrintAddress(void* p) const
{
	ostringstream oss;
	if (p) oss << p;
	else oss << "NULL";
	return oss.str();
}

void SkipList::Add(int number, string string)
{
	DataNode* d = new DataNode{ number, string };
	LineNode* n = new LineNode{ d };
	LineNode* prev = FindPreviousInNormalLine(number);
	if (prev == nullptr) {
		n->right = nl;
		nl = n;
	}
	else {
		n->right = prev->right;
		prev->right = n;
	}
	sz++;
	RebuildExpressLine();
}

DataNode* SkipList::Find(int number)
{
	LineNode* ln = el;
	while (ln != nullptr) {
		if (ln->data->num < number) {
			if (ln->right != nullptr) ln = ln->right;
			else ln = ln->bottom;
		}
		else if (ln->data->num == number) return ln->data;
		else break;
	}
	return nullptr;
}

void SkipList::Remove(int number)
{
	LineNode* prevInNormalLine = FindPreviousInNormalLine(number);
	LineNode* node = nullptr;
	if (prevInNormalLine == nullptr) {
		if (nl != nullptr && nl->data->num == number) {
			node = nl;
			nl = node->right;
		}
	}
	else {
		if (prevInNormalLine->right != nullptr && prevInNormalLine->right->data->num == number) {
			node = prevInNormalLine->right;
			prevInNormalLine->right = node->right;
		}
	}
	if (node == nullptr) return;
	LineNode* prevInExpressLine = nullptr;
	LineNode* e = el;
	while (e != nullptr) {
		if (e->bottom == node) break;
		prevInExpressLine = e;
		e = e->right;
	}
	if (prevInExpressLine != nullptr && prevInExpressLine->right != nullptr
		&& prevInExpressLine->right->bottom == node) {
		prevInExpressLine->right = prevInExpressLine->right->right;
	}
	delete node->data;
	delete node;
	sz--;
	RebuildExpressLine();
}

/* if the return value == nullptr then 'number' is the first item of the list */
LineNode* SkipList::FindPreviousInNormalLine(int number)
{
	LineNode* prevInExpressLine = nullptr;
	LineNode* e = el;
	while (e != nullptr) {
		if (e->data->num < number) {
			prevInExpressLine = e;
			e = e->right;
		}
		else break;
	}
	LineNode* prevInNormalLine = nullptr;
	LineNode* n = (prevInExpressLine) ? prevInExpressLine->bottom : nl;
	while (n != nullptr) {
		if (n->data->num < number) {
			prevInNormalLine = n;
			n = n->right;
		}
		else break;
	}
	return prevInNormalLine;
}

void SkipList::RebuildExpressLine()
{
	if (sz > 0 && el != nullptr && el->bottom != nl) {
		el->bottom = nl;
		el->data = nl->data;
	}
	int current = 0;
	for (LineNode* e = el; e != nullptr; e = e->right) current++;
	int nExpressLineNodes = sqrt(sz);										// number of express line nodes
	if (nExpressLineNodes == current) return;
	if (nExpressLineNodes == 0) DeleteExpressLine();
	else if (nExpressLineNodes == 1) {
		if (nl == nullptr) error("Error. RebuildExpressLine(). Case nExpressLineNodes == 1. 'nl == nullptr'");
		if (el == nullptr) {
			LineNode* ln = new LineNode{ nl->data };
			ln->bottom = nl;
			el = ln;
		}
		else {
			LineNode* e = el->right;
			if (e == nullptr || e->right != nullptr) error("Error. RebuildExpressLine(). "
				"Case nExpressLineNodes == 1. 'e == nullptr || e->right != nullptr'"); // TODO delete
			delete e;
		}
	}
	else if (nExpressLineNodes > 1) {
		if (el == nullptr || nl == nullptr) error("Error. RebuildExpressLine(). 'el == nullptr || nl == nullptr'");
		LineNode* e = el;
		LineNode* n = nl;
		int i = 0;												// 0 - first node of the normal line
		while (n->right != nullptr) {
			if ((++i % nExpressLineNodes) == 0) {
				if (e->right == nullptr) {
					e->right = new LineNode{ n->right->data };
					e->right->bottom = n->right;
				}
				else {
					e->right->data = n->right->data;
					e->right->bottom = n->right;
				}
				e = e->right;
			}
			n = n->right;
		}
		if (e->right != nullptr) {
			if (e->right->right != nullptr) error("Error. RebuildExpressLine(). "
				"Case nExpressLineNodes > 1. 'e->right->right != nullptr'"); // TODO delete
			delete e;
		}
	}
	else error("Error. RebuildExpressLine(). nExpressLineNodes < 0");
}

void SkipList::DeleteExpressLine()
{
	LineNode* e = el;
	while (e != nullptr) {
		LineNode* next = e->right;
		delete e;
		e = next;
	}
	el = nullptr;
}

void SkipList::DeleteNormalLineAndData()
{
	LineNode* n = nl;
	while (n != nullptr) {
		delete n->data;
		LineNode* next = n->right;
		delete n;
		n = next;
	}
	nl = nullptr;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
