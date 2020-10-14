/* Exercise 20.15 */

#include<iostream>
#include<istream>
#include<sstream>
#include<string>
#include<iomanip>
#include"C20_Exercise_20.15.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		PVECTOR
	};
	const string actionList = "\tList of actions:\n"
		"  (1) PVector\n"
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
		case PVECTOR: {
			PVector<int> pvi1(1);
			*pvi1.at(0) = new int{ -2222 };
			pvi1.push_back(new int{ 2 });
			pvi1.push_back(new int{ 10 });
			pvi1.push_back(new int{ 0 });
			pvi1.resize(10);
			cout << sp_2 << "pvi1:" << endl;
			for (int i = 0; i < pvi1.size(); i++) {
				cout << sp_4 << "pvi1[" << i << "]: ";
				if (pvi1[i] != nullptr) cout << sp_4 << pvi1[i] << " -> " << *pvi1[i];
				else cout << sp_4 << "nullptr";
				cout << endl;
			}
			cout << endl << endl;

			PVector<Something> pvt1(2);
			*pvt1.at(1) = new Something{ 8, 'k' };
			pvt1.push_back(new Something{ 2, 't' });
			pvt1.push_back(new Something{ 6, 'd' });
			pvt1.resize(8);
			cout << sp_2 << "pvt1:" << endl;
			for (int i = 0; i < pvt1.size(); i++) {
				cout << sp_4 << "pvt1[" << i << "]: ";
				if (pvt1[i] != nullptr) cout << sp_4 << pvt1[i] << " -> " << pvt1[i]->i << ", " << pvt1[i]->c;
				else cout << sp_4 << "nullptr";
				cout << endl;
			}
			cout << endl << endl;

			PVector<string> pvs1(2);
			*pvs1.at(1) = new string{ "A1" };
			pvs1.push_back(new string{ "B-" });
			pvs1.push_back(new string{ "C-" });
			pvs1.resize(6);
			cout << sp_2 << "pvs1:" << endl;
			for (int i = 0; i < pvs1.size(); i++) {
				cout << sp_4 << "pvs1[" << i << "]: ";
				if (pvs1[i] != nullptr) cout << sp_4 << pvs1[i] << " -> " << *pvs1[i];
				else cout << sp_4 << "nullptr";
				cout << endl;
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

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}

template<class T> T** Allocator<T>::allocate(int n)
{
	void* p;
	if (n <= 0 || (p = malloc(sizeof(T*) * n)) == nullptr) return nullptr;
	return static_cast<T**>(p);
}

template<class T> void Allocator<T>::deallocate(T** p, int n)
{
	void* pf = static_cast<void*>(p);
	free(pf);
}

template<class T> void Allocator<T>::construct(T** p, const T* ptr)
{
	new (p) const T*{ ptr };
}

template<class T> void Allocator<T>::destroy(T** p)
{
	if (*p != nullptr) delete (*p);
}

template<class T, class A>
void PVector<T, A>::reserve(int newalloc)
{
	if (newalloc <= space) return;								// never decrease allocation
	T** p = alloc.allocate(newalloc);							// allocate new space
	for (int i = 0; i < sz; ++i) alloc.construct(&p[i], elem[i]);			// copy
	alloc.deallocate(elem, space);								// deallocate old space
	elem = p;
	space = newalloc;
}

template<class T, class A>
void PVector<T, A>::push_back(const T* ptr)
{
	// no more free space: get more
	if (space == 0) reserve(8);
	else {
		if (space == sz) reserve(2 * space);
	}
	alloc.construct(&elem[sz++], ptr);
}

template<class T, class A>
void PVector<T, A>::resize(int newsize)
{
	reserve(newsize);
	for (int i = sz; i < newsize; ++i) alloc.construct(&elem[i], nullptr);	// construct
	for (int i = newsize; i < sz; ++i) alloc.construct(&elem[i], nullptr);	// destroy
	sz = newsize;
}
