/* Exercise 17.9 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C17_Exercise_17.9.h"

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
		STACK
	};
	const string actionList = "\tList of actions:\n"
	"  (1) StackHeapGrow()\n"
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
		case STACK: {
			int stack1[] = { 1, 2 , 3, 4, 5, 6, 7, 8, 9, 10};
			int stack2[] = { 1, 2 , 3, 4, 5, 6, 7, 8, 9, 10};
			cout << endl << indent2 << "Stack grows: "
				<< (((&(stack1[0]) - &(stack2[0])) > 0)
					? "down (toward lower addresses)" : "up (toward higher addresses)") << endl;
			cout << indent2 << "Address of stack1[0]: " << &(stack1[0]) << endl;
			cout << indent2 << "Address of stack2[0]: " << &(stack2[0]) << endl;
			int* heap1 = new int[10];
			for (int i = 0; i < 100; i++) int* temp = new int[10];
			int* heap2 = new int[10];
			cout << endl << indent2 << "Heap grows: "
				<< (((&(heap1[0]) - &(heap2[0])) > 0) ? "down (toward lower addresses)" : "up (toward higher addresses)") << endl;
			cout << indent2 << "Address of heap1[0]: " << &(heap1[0]) << endl;
			cout << indent2 << "Address of heap2[0]: " << &(heap2[0]) << endl;
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
