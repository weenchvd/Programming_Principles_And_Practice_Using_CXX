/* Exercise 25.14 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include"C25_Exercise_25.14.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const string actionList = "\tList of actions:\n"
		"  (1) VectorPool\n"
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
		case CASE1: {
			cout << endl;

			Pool<int> poolInt;

			int* ptrInt01 = poolInt.get();
			if (ptrInt01 != nullptr) {
				*ptrInt01 = 111111;
				cout << sp_2 << "*ptrInt01 = " << *ptrInt01 << endl;
			}
			int* ptrInt02 = poolInt.get();
			if (ptrInt02 != nullptr) {
				*ptrInt02 = 222222;
				cout << sp_2 << "*ptrInt02 = " << *ptrInt02 << endl;
			}
			cout << endl;

			VectorPool<int, 1024> vpi1{ poolInt };
			for (int i = 0; i < vpi1.Size(); ++i) {
				vpi1[i] = i;
			}
			cout << sp_2 << "vpi1:" << endl;
			for (int i = 0; i < vpi1.Size(); ++i) {
				cout << sp_4 << "vpi1[" << i << "] = " << vpi1[i] << endl;
			}
			cout << endl;

			int* ptrInt03 = poolInt.get();
			if (ptrInt03 != nullptr) {
				*ptrInt03 = 333333;
				cout << sp_2 << "*ptrInt03 = " << *ptrInt03 << endl;
			}
			int* ptrInt04 = poolInt.get();
			if (ptrInt04 != nullptr) {
				*ptrInt04 = 444444;
				cout << sp_2 << "*ptrInt04 = " << *ptrInt04 << endl;
			}
			cout << endl;

			VectorPool<int, 512> vpi2{ poolInt };
			for (int i = 0; i < vpi2.Size(); ++i) {
				vpi2[i] = i + 1000;
			}
			cout << sp_2 << "vpi2:" << endl;
			for (int i = 0; i < vpi2.Size(); ++i) {
				cout << sp_4 << "vpi2[" << i << "] = " << vpi2[i] << endl;
			}
			cout << endl;

			int* ptrInt05 = poolInt.get();
			if (ptrInt05 != nullptr) {
				*ptrInt05 = 555555;
				cout << sp_2 << "*ptrInt05 = " << *ptrInt05 << endl;
			}
			int* ptrInt06 = poolInt.get();
			if (ptrInt06 != nullptr) {
				*ptrInt06 = 666666;
				cout << sp_2 << "*ptrInt06 = " << *ptrInt06 << endl;
			}
			cout << endl;
			poolInt.free(ptrInt05);
			poolInt.free(ptrInt06);

			VectorPool<int, 64> vpi3{ poolInt };
			for (int i = 0; i < vpi3.Size(); ++i) {
				vpi3[i] = i + 2000;
			}
			cout << sp_2 << "vpi3:" << endl;
			for (int i = 0; i < vpi3.Size(); ++i) {
				cout << sp_4 << "vpi3[" << i << "] = " << vpi3[i] << endl;
			}
			cout << endl;

			int* ptrInt07 = poolInt.get();
			if (ptrInt07 != nullptr) {
				*ptrInt07 = 777777;
				cout << sp_2 << "*ptrInt07 = " << *ptrInt07 << endl;
			}
			int* ptrInt08 = poolInt.get();
			if (ptrInt08 != nullptr) {
				*ptrInt08 = 888888;
				cout << sp_2 << "*ptrInt08 = " << *ptrInt08 << endl;
			}
			cout << endl;
			poolInt.free(ptrInt07);
			poolInt.free(ptrInt08);

			// print all pool
			cout << "Pool<int> poolInt:" << endl;
			cout << poolInt;

			cout << vsp_2;
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

template<typename T> Pool<T>::Pool(int n)
	: nFree{ n }, n{ n }
{
	elem = new T[n];
	if (elem == nullptr) throw PoolException{};
	isUsed = new bool[n];
	if (isUsed == nullptr) throw PoolException{};
	for (int i = 0; i < n; ++i) isUsed[i] = false;
}

template<typename T> Pool<T>::~Pool()
{
	delete[] elem;
	delete[] isUsed;
}

template<typename T> T* Pool<T>::get()
{
	if (nFree == 0) return nullptr;
	for (int i = 0; i < n; ++i) {
		if (isUsed[i] == false) {
			isUsed[i] = true;
			--nFree;
			return &elem[i];
		}
	}
	return nullptr;
}

template<typename T> T* Pool<T>::get(int n)
{
	if (nFree == 0) return nullptr;
	int i = 0;
	while (i < this->n) {
		if (isUsed[i] == false) {
			int j;
			for (j = 0; j < n; ++j) {
				if (i >= this->n) return nullptr;
				if (isUsed[i] == true) break;
				++i;
			}
			if (j == n) {
				for (int k = i - n; k < i; ++k) isUsed[k] = true;
				nFree -= n;
				return &elem[i - n];
			}
		}
		++i;
	}
	return nullptr;
}

template<typename T> void Pool<T>::free(T* ptr)
{
	if (ptr >= elem && ptr < &elem[n]) {						// range [elem[0]:elem[N])
		isUsed[ptr - elem] = false;
		++nFree;
	}
}

template<typename T> void Pool<T>::free(T* ptr, int n)
{
	if (ptr >= elem && ptr + n - 1 < &elem[this->n]) {				// range [elem[0]:elem[N])
		int i = ptr - elem;
		for (int j = 0; j < n; ++j) {
			isUsed[i] = false;
			++i;
		}
		nFree += n;
	}
}

template<typename T> ostream& operator<<(ostream& os, const Pool<T>& pool)
{
	os << boolalpha;
	for (int i = 0; i < pool.n; ++i) {
		os << sp_4 << "elem[" << i << "] = " << pool.elem[i]
			<< ", isUsed[" << i << "] = " << pool.isUsed[i] << endl;
	}
	os << noboolalpha;
	return os;
}

template<typename T, int N> VectorPool<T, N>::VectorPool(Pool<T>& pool)
	: sz{ N }, pl{ pool }
{
	elem = pool.get(N);
	if (elem == nullptr) throw VectorPoolException{};
}

template<typename T, int N> VectorPool<T, N>::~VectorPool()
{
	pl.free(elem, sz);
}
