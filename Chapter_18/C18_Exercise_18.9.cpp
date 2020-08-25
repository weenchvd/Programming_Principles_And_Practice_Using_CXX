/* Exercise 18.9 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C18_Exercise_18.9.h"

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
		DRAWMEMORY
	};
	const string actionList = "\tList of actions:\n"
	"  (1) draw memory layout\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	const char* space2 = "  ";
	const char* space4 = "    ";
	static char* staticVar = "Static Variable";
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case DRAWMEMORY: {
			char* stackVar = "Stack Variable";;
			char* heapVar = new char[]{ "Heap Variable" };
			void* ptrStaticVar = &staticVar;
			void* ptrStackVar = &stackVar;
			void* ptrHeapVar = heapVar;
			void* pointers[] = { ptrStaticVar, ptrStackVar, ptrHeapVar };
			SortPointer(pointers, 3);
			cout << endl << space4 << "Address: highest" << endl;
			cout << space4 << "Address: " << pointers[2];
			if (pointers[2] == ptrStaticVar) cout << " (Static Variable)" << endl;
			else if (pointers[2] == ptrStackVar) cout << " (Stack Variable)" << endl;
			else if (pointers[2] == ptrHeapVar) cout << " (Heap Variable)" << endl;
			cout << space4 << "Address: " << pointers[1];
			if (pointers[1] == ptrStaticVar) cout << " (Static Variable)" << endl;
			else if (pointers[1] == ptrStackVar) cout << " (Stack Variable)" << endl;
			else if (pointers[1] == ptrHeapVar) cout << " (Heap Variable)" << endl;
			cout << space4 << "Address: " << pointers[0];
			if (pointers[0] == ptrStaticVar) cout << " (Static Variable)" << endl;
			else if (pointers[0] == ptrStackVar) cout << " (Stack Variable)" << endl;
			else if (pointers[0] == ptrHeapVar) cout << " (Heap Variable)" << endl;
			cout << space4 << "Address: 0" << endl;

			cout << "Windows allocates address blocks in the virtual address space\n"
				"for static storage, stack, and heap at its discretion (see screenshot).\n"
				"Therefore variable addresses do not correspond to the memory layout order specified in 17.4" << endl;
			cout << "\nPress Enter" << endl;

			char ch;
			cin.get(ch);
			staticVar[0] = '-';
			stackVar[0] = '-';
			heapVar[0] = '-';

			delete[] heapVar;
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

void SortPointer(void* pointers[], int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (pointers[i] > pointers[j]) {
				void* temp = pointers[i];
				pointers[i] = pointers[j];
				pointers[j] = temp;
			}
		}
	}
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
