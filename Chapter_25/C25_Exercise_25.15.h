/* Exercise 25.15 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

struct B500 {
	char s[500];
};

class PoolException {};

template<typename T> class Pool {								// Pool of objects of type T
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

class StackException {};

class Stack {													// stack of bytes
public:
	Stack(int n = 4096);										// make an n-byte stack
	~Stack();
	void* get(int n);											// allocate n bytes from the stack; return nullptr if no free space
	void free();												// return the last value returned by get() to the stack
	int available() const { return n - top; }					// number of available bytes
private:
	// space for char[N] and data to keep track of what is allocated
	// and what is not (e.g., a top-of-stack pointer)
	char* elem;
	bool* chunk;												// chunk start mark
	int top;													// top-of-stack
	int n;														// number of objects
};
