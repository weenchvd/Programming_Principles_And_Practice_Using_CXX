/* Exercise 19.8 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include<cstdlib>
#include"C19_Exercise_19.8.h"

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
		VECTOR
	};
	const string actionList = "\tList of actions:\n"
	"  (1) Vector()\n"
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
		case VECTOR: {
			Vector<int> vi1;
			vi1.push_back(2);
			vi1.push_back(10);
			vi1.push_back(0);
			vi1.resize(100, -1);
			cout << space_c2 << "vi1:" << endl;
			cout << space_c4;
			for (int i = 0; i < vi1.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vi1[i];
			}
			cout << endl << endl;

			Vector<Something> vt1(2);
			vt1[1] = {8, 'k'};
			vt1.push_back({2, 't'});
			vt1.push_back({6, 'd'});
			vt1.resize(40, { -1, '*' });
			cout << space_c2 << "vt1:" << endl;
			cout << space_c4;
			for (int i = 0; i < vt1.size(); i++) {
				if (i > 0) cout << "; ";
				cout << vt1[i].i << ", " << vt1[i].c;
			}
			cout << endl << endl;

			Vector<string> vs1(2);
			vs1[1] = "A1";
			vs1.push_back("B-");
			vs1.push_back("C-");
			vs1.resize(60, "#");
			cout << space_c2 << "vs1:" << endl;
			cout << space_c4;
			for (int i = 0; i < vs1.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vs1[i];
			}
			cout << endl << endl;

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

template<class T> T* Allocator<T>::allocate(int n)
{
	void* p;
	if (n <= 0 || (p = malloc(sizeof(T) * n)) == nullptr) return nullptr;
	return static_cast<T*>(p);
}

template<class T> void Allocator<T>::deallocate(T* p, int n)
{
	void* pf = static_cast<void*>(p);
	free(pf);
}

template<class T> void Allocator<T>::construct(T* p, const T& v)
{
	new (p) T(v);
}

template<class T> void Allocator<T>::destroy(T* p)
{
	p->~T();
}

template<class T, class A>
void Vector<T, A>::reserve(int newalloc)
{
	if (newalloc <= space) return;     // never decrease allocation
	T* p = alloc.allocate(newalloc); // allocate new space
	for (int i = 0; i < sz; ++i) alloc.construct(&p[i], elem[i]); // copy
	for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);        // destroy
	alloc.deallocate(elem, space);    // deallocate old space
	elem = p;
	space = newalloc;
}

template<class T, class A>
void Vector<T, A>::push_back(const T& val)
{
	// no more free space: get more
	if (space == 0)
		reserve(8);
	else
		if (space == sz)
			reserve(2 * space);

	alloc.construct(&elem[sz], val);  // add val at end
	++sz;                            // increase the size
}

template<class T, class A>
void Vector<T, A>::resize(int newsize, T val)
{
	reserve(newsize);
	for (int i = sz; i < newsize; ++i) alloc.construct(&elem[i], val); // construct
	for (int i = newsize; i < sz; ++i) alloc.destroy(&elem[i]); // destroy
	sz = newsize;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
