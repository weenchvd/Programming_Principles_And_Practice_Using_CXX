/* Exercise 25.15 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include<chrono>
#include<vector>
#include"C25_Exercise_25.15.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }
inline int randint(int max) { return rand() % max; }
inline int randint(int min, int max) { return randint(max - min) + min; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Time\n"
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
			constexpr int numberOfObjects = 10000;
			constexpr int maxSizeOfObject = 1000;
			using timeUnit = chrono::nanoseconds;

			vector<size_t> sizes;
			sizes.resize(numberOfObjects);
			for (int i = 0; i < sizes.size(); ++i) {
				sizes[i] = static_cast<size_t>(randint(1, maxSizeOfObject + 1));
			}

			vector<int> reverseOrder;
			reverseOrder.resize(numberOfObjects);
			for (int i = 0; i < reverseOrder.size(); ++i) {
				reverseOrder[i] = reverseOrder.size() - i - 1;
			}

			vector<bool> isAssigned;
			isAssigned.resize(numberOfObjects, false);
			vector<int> randOrder;
			randOrder.resize(numberOfObjects);
			for (int i = 0; i < randOrder.size(); ++i) {
				constexpr int numberOfTry = 100;
				int number;
				int j;
				for (j = 0; j < numberOfTry; ++j) {
					number = randint(numberOfObjects);
					if (isAssigned[number] == true) continue;
					else break;
				}
				if (j == numberOfTry) {
					number = 0;
					while (isAssigned[number] == true) ++number;
				}
				isAssigned[number] = true;
				randOrder[i] = number;
			}


			cout << sp_2 << "HEAP:" << endl;

			vector<void*> v1;
			v1.resize(numberOfObjects);
			
			long long int v1time1 = 0;
			for (int i = 0; i < v1.size(); ++i) {
				size_t size = sizes[i];
				auto t1 = chrono::system_clock::now();
				void* p = new char[size];
				auto t2 = chrono::system_clock::now();
				v1time1 += chrono::duration_cast<timeUnit>(t2 - t1).count();
				v1[i] = p;
			}
			cout << sp_4 << "Objects were allocated in " << v1time1 << " nanosecond(s)" << endl;

			long long int v1time2 = 0;
			for (int i = 0; i < v1.size(); ++i) {
				void* p = v1[reverseOrder[i]];
				auto t1 = chrono::system_clock::now();
				delete[] p;
				auto t2 = chrono::system_clock::now();
				v1time2 += chrono::duration_cast<timeUnit>(t2 - t1).count();
			}
			cout << sp_4 << "Objects were deallocated in " << v1time2 << " nanosecond(s) (reverse order)" << endl;
			cout << endl;

			vector<void*> v2;
			v2.resize(numberOfObjects);

			long long int v2time1 = 0;
			for (int i = 0; i < v2.size(); ++i) {
				size_t size = sizes[i];
				auto t1 = chrono::system_clock::now();
				void* p = new char[size];
				auto t2 = chrono::system_clock::now();
				v2time1 += chrono::duration_cast<timeUnit>(t2 - t1).count();
				v2[i] = p;
			}
			cout << sp_4 << "Objects were allocated in " << v2time1 << " nanosecond(s)" << endl;

			long long int v2time2 = 0;
			for (int i = 0; i < v2.size(); ++i) {
				void* p = v2[randOrder[i]];
				auto t1 = chrono::system_clock::now();
				delete[] p;
				auto t2 = chrono::system_clock::now();
				v2time2 += chrono::duration_cast<timeUnit>(t2 - t1).count();
			}
			cout << sp_4 << "Objects were deallocated in " << v2time2 << " nanosecond(s) (random order)" << endl;
			cout << endl << endl;




			cout << sp_2 << "POOL:" << endl;

			Pool<B500> pool(numberOfObjects);

			vector<B500*> vp1;
			vp1.resize(numberOfObjects);

			long long int vp1time1 = 0;
			for (int i = 0; i < vp1.size(); ++i) {
				auto t1 = chrono::system_clock::now();
				B500* p = pool.get();
				auto t2 = chrono::system_clock::now();
				vp1time1 += chrono::duration_cast<timeUnit>(t2 - t1).count();
				vp1[i] = p;
			}
			cout << sp_4 << "Objects were allocated in " << vp1time1 << " nanosecond(s)" << endl;

			long long int vp1time2 = 0;
			for (int i = 0; i < vp1.size(); ++i) {
				B500* p = vp1[reverseOrder[i]];
				auto t1 = chrono::system_clock::now();
				pool.free(p);
				auto t2 = chrono::system_clock::now();
				vp1time2 += chrono::duration_cast<timeUnit>(t2 - t1).count();
			}
			cout << sp_4 << "Objects were deallocated in " << vp1time2 << " nanosecond(s) (reverse order)" << endl;
			cout << endl;

			vector<B500*> vp2;
			vp2.resize(numberOfObjects);

			long long int vp2time1 = 0;
			for (int i = 0; i < vp2.size(); ++i) {
				auto t1 = chrono::system_clock::now();
				B500* p = pool.get();
				auto t2 = chrono::system_clock::now();
				vp2time1 += chrono::duration_cast<timeUnit>(t2 - t1).count();
				vp2[i] = p;
			}
			cout << sp_4 << "Objects were allocated in " << vp2time1 << " nanosecond(s)" << endl;

			long long int vp2time2 = 0;
			for (int i = 0; i < vp2.size(); ++i) {
				B500* p = vp2[randOrder[i]];
				auto t1 = chrono::system_clock::now();
				pool.free(p);
				auto t2 = chrono::system_clock::now();
				vp2time2 += chrono::duration_cast<timeUnit>(t2 - t1).count();
			}
			cout << sp_4 << "Objects were deallocated in " << vp2time2 << " nanosecond(s) (random order)" << endl;
			cout << endl << endl;




			cout << sp_2 << "STACK:" << endl;

			Stack stack(numberOfObjects * maxSizeOfObject);

			vector<void*> vs1;
			vs1.resize(numberOfObjects);

			long long int vs1time1 = 0;
			for (int i = 0; i < vs1.size(); ++i) {
				size_t size = sizes[i];
				auto t1 = chrono::system_clock::now();
				void* p = stack.get(size);
				auto t2 = chrono::system_clock::now();
				vs1time1 += chrono::duration_cast<timeUnit>(t2 - t1).count();
				vs1[i] = p;
			}
			cout << sp_4 << "Objects were allocated in " << vs1time1 << " nanosecond(s)" << endl;

			long long int vs1time2 = 0;
			for (int i = 0; i < vs1.size(); ++i) {
				auto t1 = chrono::system_clock::now();
				stack.free();
				auto t2 = chrono::system_clock::now();
				vs1time2 += chrono::duration_cast<timeUnit>(t2 - t1).count();
			}
			cout << sp_4 << "Objects were deallocated in " << vs1time2 << " nanosecond(s) (reverse order)" << endl;
			cout << endl;



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

Stack::Stack(int n) : top{ 0 }, n{ n }
{
	elem = new char[n];
	if (elem == nullptr) throw StackException{};
	chunk = new bool[n];
	if (chunk == nullptr) throw StackException{};
	for (int i = 0; i < n; ++i) chunk[i] = false;
}

Stack::~Stack()
{
	delete[] elem;
	delete[] chunk;
}

void* Stack::get(int n)
{
	if (top + n > this->n) return nullptr;
	chunk[top] = true;
	void* ret = &elem[top];
	top += n;
	return ret;
}

void Stack::free()
{
	if (top == 0) return;
	int i;
	for (i = top; i >= 0; --i) {
		if (chunk[i] == true) {
			chunk[i] = false;
			top = i;
			break;
		}
	}
	if (i < 0) throw StackException{};
}
