/* Exercise 20.17 */

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
	T* allocate(int n);            // allocate space for n objects of type T
	void deallocate(T* p, int n);  // deallocate n objects of type T starting at p

	void construct(T* p, const T& v); // construct a T with the value v in p
	void destroy(T* p);            // destroy the T in p
};

template<class T> class AllocatorPtr {
public:
	T** allocate(int n);										// allocate space for n objects of type T
	void deallocate(T** p, int n);								// deallocate n objects of type T starting at p

	void construct(T** p, T* ptr);						// construct a T with the value v in p
	void destroy(T** p);										// destroy the T in p
};

template<class T, class A = AllocatorPtr<T>> class OwnershipVector {
	A alloc;													// use allocate to handle memory for elements
	Allocator<bool> allocOwn;
	int sz;														// the size
	T** elem;													// a pointer to the elements
	bool* isOwned;
	int space;													// size+free_space
	
	void reserve(int newalloc);
public:
	OwnershipVector() : sz{ 0 }, elem{ nullptr }, isOwned{ nullptr }, space{ 0 } {}
	OwnershipVector(int s) : sz{ s }, space{ s }
	{
		elem = alloc.allocate(s);
		isOwned = allocOwn.allocate(s);
		for (int i = 0; i < sz; ++i) {
			alloc.construct(&elem[i], nullptr);			// elements are initialized
			isOwned[i] = true;
		}
	}
	~OwnershipVector()
	{
		for (int i = 0; i < sz; ++i) {
			if (isOwned[i]) alloc.destroy(&elem[i]);
		}
		alloc.deallocate(elem, space);
	}

	OwnershipVector(const OwnershipVector&) = delete;							// copy constructor
	OwnershipVector& operator=(const OwnershipVector&) = delete;				// copy assignment

	T* operator[](int n) { return elem[n]; }					// access: return pointer
	const T* operator[](int n) const { return elem[n]; }
	T** at(int n) { return &elem[n]; }

	int size() const { return sz; }								// the current size
	int capacity() const { return space; }

	void resize(int newsize);					// growth
	void push_back(T* ptr);
	void release(int n) { isOwned[n] = false; }
	void own(int n) { isOwned[n] = true; }
};
