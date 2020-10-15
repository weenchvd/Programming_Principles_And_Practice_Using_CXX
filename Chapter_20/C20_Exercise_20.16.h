/* Exercise 20.16 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

struct Something {
	Something() : i{ 0 }, c{ '-' } {}
	Something(int number, char symbol) : i{ number }, c{ symbol } {}
	int i;
	char c;
};

template<class T> class Allocator {
public:
	T** allocate(int n);										// allocate space for n objects of type T
	void deallocate(T** p, int n);								// deallocate n objects of type T starting at p

	void construct(T** p, const T* ptr);						// construct a T with the value v in p
	void destroy(T** p);										// destroy the T in p
};

template<class T, class A = Allocator<T>> class OVector {
	A alloc;													// use allocate to handle memory for elements
	int sz;														// the size
	T** elem;													// a pointer to the elements
	int space;													// size+free_space
	int index;
public:
	OVector() : sz{ 0 }, elem{ nullptr }, space{ 0 } {}
	OVector(int s) : sz{ s }, space{ s }, index{ 0 }
	{
		elem = alloc.allocate(s);
		for (int i = 0; i < sz; ++i) alloc.construct(&elem[i], nullptr);			// elements are initialized
	}
	~OVector()
	{
		for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);
		alloc.deallocate(elem, space);
	}

	OVector(const OVector&) = delete;							// copy constructor
	OVector& operator=(const OVector&) = delete;				// copy assignment

	T& operator[](int n) { return *elem[n]; }					// access: return reference
	const T& operator[](int n) const { return *elem[n]; }
	T& operator*() { return *elem[index]; }
	const T& operator*() const { return *elem[index]; }
	T* operator->() { return elem[index]; }
	const T* operator->() const { return elem[index]; }
	T** at(int n) { return &elem[n]; }

	OVector& set_index(int i) { index = i; return *this; }

	int size() const { return sz; }								// the current size
	int capacity() const { return space; }

	void resize(int newsize);					// growth
	void push_back(const T* ptr);
	void reserve(int newalloc);
};
