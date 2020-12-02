/* Exercise 25.14 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

class PoolException{};

template<typename T> class Pool {								// Pool of N objects of type T
public:
	Pool(int n = 4096);											// make pool of n Ts
	~Pool();
	T* get();													// get a T from the pool; return 0 if no free Ts
	T* get(int n);												// get a T[n] from the pool; return nullptr if no free Ts
	void free(T* ptr);											// return a T given out by get() to the pool
	void free(T* ptr, int n);									// return a T[n] given out by get() to the pool
	int available() const { return nFree; }						// number of free Ts
	int size() { return n; }

	template<typename T> friend ostream& operator<<(ostream& os, const Pool<T>& pool);
private:
	// space for T[N] and data to keep track of which Ts are allocated
	// and which are not (e.g., a list of free objects)
	T* elem;
	bool* isUsed;
	int nFree;													// number of free objects
	int n;														// number of objects
};

class VectorPoolException {};

template<typename T, int N> class VectorPool {
public:
	VectorPool(Pool<T>& pool);
	~VectorPool();
	int Size() { return sz; }
	T& operator[](int i) { return elem[i]; }
	const T& operator[](int i) const { return elem[i]; }
private:
	T* elem;
	int sz;
	Pool<T>& pl;
};