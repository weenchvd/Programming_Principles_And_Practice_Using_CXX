/* Exercise 19.16 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include<cstdlib>
#include"C19_Exercise_19.16.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

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
			cout << sp_2 << "vi1:" << endl;
			cout << sp_4;
			for (int i = 0; i < vi1.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vi1[i];
			}
			cout << endl;
			cout << sp_2 << "vi2 before '=':" << endl;
			cout << sp_4;
			for (int i = 0; i < vi2.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vi2[i];
			}
			cout << endl;
			vi2 = vi1;
			cout << sp_2 << "vi2 after '=':" << endl;
			cout << sp_4;
			for (int i = 0; i < vi2.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vi2[i];
			}
			cout << endl << endl;

			Vector<Something> vt1(2);
			vt1[1] = { 8, 'k' };
			vt1.push_back({ 2, 't' });
			vt1.push_back({ 6, 'd' });
			vt1.resize(40, { -1, '*' });
			Vector<Something> vt2;
			cout << sp_2 << "vt1:" << endl;
			cout << sp_4;
			for (int i = 0; i < vt1.size(); i++) {
				if (i > 0) cout << "; ";
				cout << vt1[i].i << ", " << vt1[i].c;
			}
			cout << endl;
			cout << sp_2 << "vt2 before '=':" << endl;
			cout << sp_4;
			for (int i = 0; i < vt2.size(); i++) {
				if (i > 0) cout << "; ";
				cout << vt2[i].i << ", " << vt2[i].c;
			}
			cout << endl;
			vt2 = vt1;
			cout << sp_2 << "vt2 after '=':" << endl;
			cout << sp_4;
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
			cout << sp_2 << "vs1:" << endl;
			cout << sp_4;
			for (int i = 0; i < vs1.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vs1[i];
			}
			cout << endl;
			cout << sp_2 << "vs2 before '=':" << endl;
			cout << sp_4;
			for (int i = 0; i < vs2.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vs2[i];
			}
			cout << endl;
			vs2 = vs1;
			cout << sp_2 << "vs2 after '=':" << endl;
			cout << sp_4;
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

template<class T, class A> VectorRepresentation<T, A>::VectorRepresentation(size_t size)
{
	sz = 0;
	space = size;
	elem = alloc.allocate(space);
	for (int i = 0; i < space; ++i) alloc.construct(&elem[i], T());    // elements are initialized
}

template<class T, class A> VectorRepresentation<T, A>::~VectorRepresentation()
{
	for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);
	alloc.deallocate(elem, space);
}

template<class T, class A> Vector<T, A>::Vector(size_t size)
{
	if (size > 0) {
		rep = new VectorRepresentation<T, A>(size);
		rep->sz = size;
	}
	else rep = nullptr;
}

template<class T, class A> Vector<T, A>::~Vector()
{
	delete rep;
}

template<class T, class A> Vector<T, A>& Vector<T, A>::operator=(const Vector<T, A>& a)
{
	if (this == &a) return *this;													// self-assignment, no work needed
	if (rep == nullptr && a.rep == nullptr) return *this;
	else if (a.rep == nullptr) {
		delete rep;
		return *this;
	}
	else if (rep == nullptr || a.rep->sz <= rep->space) {
		if (rep == nullptr) rep = new VectorRepresentation<T, A>(a.rep->sz);
		for (int i = 0; i < a.rep->sz; ++i) rep->elem[i] = a.rep->elem[i];			// copy elements
		rep->sz = a.rep->sz;
		return *this;
	}

	T* p = rep->alloc.allocate(a.rep->sz);											// allocate new space
	for (int i = 0; i < a.rep->sz; ++i) rep->alloc.construct(&p[i], a.rep->elem[i]);// copy elements
	for (int i = 0; i < rep->sz; ++i) rep->alloc.destroy(&rep->elem[i]);
	rep->alloc.deallocate(rep->elem, rep->space);
	rep->space = rep->sz = a.rep->sz;												// set new size
	rep->elem = p;																	// set new elements
	return *this;																	// return a self-reference
}

template<class T, class A> void Vector<T, A>::reserve(size_t newalloc)
{
	if (rep == nullptr) {
		if (newalloc > 0) rep = new VectorRepresentation<T, A>(newalloc);
		return;
	}
	else if (newalloc <= rep->space) return;										// never decrease allocation
	T* p = rep->alloc.allocate(newalloc);											// allocate new space
	for (int i = 0; i < rep->sz; ++i) rep->alloc.construct(&p[i], rep->elem[i]);	// copy
	for (int i = 0; i < rep->sz; ++i) rep->alloc.destroy(&rep->elem[i]);			// destroy
	rep->alloc.deallocate(rep->elem, rep->space);									// deallocate old space
	rep->elem = p;
	rep->space = newalloc;
}

template<class T, class A> void Vector<T, A>::push_back(const T& val)
{
	constexpr int initialSize = 8;
	if (rep == nullptr) reserve(initialSize);
	else if (rep->space == rep->sz) reserve(rep->space * 2);
	rep->alloc.construct(&rep->elem[rep->sz++], val);
}

template<class T, class A> void Vector<T, A>::resize(size_t newsize, T val)
{
	reserve(newsize);
	for (int i = rep->sz; i < newsize; ++i) rep->alloc.construct(&rep->elem[i], val);		// construct
	for (int i = newsize; i < rep->sz; ++i) rep->alloc.destroy(&rep->elem[i]);				// destroy
	rep->sz = newsize;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
