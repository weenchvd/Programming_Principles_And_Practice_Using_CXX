/* Exercise 20.18 */

#include<iostream>
#include<istream>
#include<sstream>
#include<string>
#include<iomanip>
#include"C20_Exercise_20.18.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		ITERATOR
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Iterator\n"
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
		case ITERATOR: {
			Vector<string> vs(2);
			vs[1] = "A1";
			vs.push_back("B2");
			vs.push_back("C3");
			vs.resize(10, "####");
			cout << sp_2 << "Number of items: " << vs.end() - vs.begin() << endl;
			cout << sp_2 << "vs:" << endl << sp_4;
			for (Vector<string>::iterator it = vs.begin(); it != vs.end(); ++it) {
				if (it != vs.begin()) cout << ", ";
				cout << *it;
			}
			cout << endl;

			Vector<string>::iterator first = vs.begin();
			*first = "First item";
			first[3] = "Fourth item";
			*(first + 4) = "5";
			Vector<string>::iterator last = vs.end();
			--last;
			*last = "LAST";
			last[-1] = "9((((";
			*(last - 2) = "8****";
			cout << sp_2 << "vs:" << endl << sp_4;
			for (int i = 0; i < vs.size(); i++) {
				if (i > 0) cout << ", ";
				cout << vs[i];
			}
			cout << endl;

			++first;
			*first = "AAA---";
			cout << sp_2 << "vs:" << endl << sp_4;
			Vector<string>::iterator it = vs.begin();
			for (int i = 0; i < vs.size(); i++) {
				if (i > 0) cout << ", ";
				cout << it[i];
			}
			cout << endl << endl;

			cout << sp_2 << "last + 1: " << *++last << endl; // throw exception "out_of_range"

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

template<class T, class A>
T& Vector<T, A>::iterator::operator*()
{
	if (curr >= begin && curr < end) return *curr;
	else throw std::out_of_range{ "Vector::iterator::operator*()" };
}

template<class T, class A>
const T& Vector<T, A>::iterator::operator*() const
{
	if (curr >= begin && curr < end) return *curr;
	else throw std::out_of_range{ "Vector::iterator::operator*() const" };
}

template<class T, class A>
T& Vector<T, A>::iterator::operator[](int i)
{
	if (curr + i >= begin && curr + i < end) return *(curr + i);
	else throw std::out_of_range{ "Vector::iterator::operator[](int i)" };
}

template<class T, class A>
const T& Vector<T, A>::iterator::operator[](int i) const
{
	if (curr + i >= begin && curr + i < end) return *(curr + i);
	else throw std::out_of_range{ "Vector::iterator::operator[](int i) const" };
}
