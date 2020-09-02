/* Exercise 19.9 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include<cstdlib>
#include"C19_Exercise_19.9.h"

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
			Vector<int> vi2;
			vi2.resize(100, -9);
			cout << space_c2 << "vi1:" << endl;
			cout << space_c4;
			for (int i = 0; i < vi1.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vi1[i];
			}
			cout << endl;
			cout << space_c2 << "vi2 before '=':" << endl;
			cout << space_c4;
			for (int i = 0; i < vi2.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vi2[i];
			}
			cout << endl;
			vi2 = vi1;
			cout << space_c2 << "vi2 after '=':" << endl;
			cout << space_c4;
			for (int i = 0; i < vi2.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vi2[i];
			}
			cout << endl << endl;

			Vector<Something> vt1(2);
			vt1[1] = {8, 'k'};
			vt1.push_back({2, 't'});
			vt1.push_back({6, 'd'});
			vt1.resize(40, { -1, '*' });
			Vector<Something> vt2;
			cout << space_c2 << "vt1:" << endl;
			cout << space_c4;
			for (int i = 0; i < vt1.size(); i++) {
				if (i > 0) cout << "; ";
				cout << vt1[i].i << ", " << vt1[i].c;
			}
			cout << endl;
			cout << space_c2 << "vt2 before '=':" << endl;
			cout << space_c4;
			for (int i = 0; i < vt2.size(); i++) {
				if (i > 0) cout << "; ";
				cout << vt2[i].i << ", " << vt2[i].c;
			}
			cout << endl;
			vt2 = vt1;
			cout << space_c2 << "vt2 after '=':" << endl;
			cout << space_c4;
			for (int i = 0; i < vt2.size(); i++) {
				if (i > 0) cout << "; ";
				cout << vt2[i].i << ", " << vt2[i].c;
			}
			cout << endl << endl;

			Vector<string> vs1(2);
			vs1[1] = "A1";
			vs1.push_back("B-");
			vs1.push_back("C-");
			vs1.resize(60, "#");
			Vector<string> vs2;
			vs2.resize(10, "&");
			cout << space_c2 << "vs1:" << endl;
			cout << space_c4;
			for (int i = 0; i < vs1.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vs1[i];
			}
			cout << endl;
			cout << space_c2 << "vs2 before '=':" << endl;
			cout << space_c4;
			for (int i = 0; i < vs2.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vs2[i];
			}
			cout << endl;
			vs2 = vs1;
			cout << space_c2 << "vs2 after '=':" << endl;
			cout << space_c4;
			for (int i = 0; i < vs2.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vs2[i];
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
Vector<T, A>& Vector<T, A>::operator=(const Vector<T, A>& a)
{
	if (this == &a) return *this;    // self-assignment, no work needed

	if (a.sz <= space) {             // enough space, no need for new allocation
		for (int i = 0; i < a.sz; ++i) elem[i] = a.elem[i]; // copy elements
		sz = a.sz;
		return *this;
	}

	T* p = alloc.allocate(a.sz);  // allocate new space
	for (int i = 0; i < a.sz; ++i) alloc.construct(&p[i], a.elem[i]); // copy elements
	for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);
	alloc.deallocate(elem, space);
	space = sz = a.sz;             // set new size
	elem = p;                      // set new elements
	return *this;                  //  return a self-reference
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
