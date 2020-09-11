/* Exercise 19.16 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

template<class T, class A> class Vector;

struct Something {
	Something() : i{ 0 }, c{ '-' } {}
	Something(int number, char symbol) : i{ number }, c{ symbol } {}
	int i;
	char c;
};

template<class T> class Allocator {
public:
	T* allocate(int n);						// allocate space for n objects of type T
	void deallocate(T* p, int n);			// deallocate n objects of type T starting at p

	void construct(T* p, const T& v);		// construct a T with the value v in p
	void destroy(T* p);						// destroy the T in p
};

template<class T, class A> class VectorRepresentation {
public:
	VectorRepresentation(size_t size);
	~VectorRepresentation();

	friend class Vector<T, A>;
private:
	T* elem;			// a pointer to the elements
	size_t sz;			// the size
	size_t space;		// size+free_space
	A alloc;			// use allocate to handle memory for elements
};

template<class T, class A = Allocator<T>> class Vector {
public:
	Vector() : rep{ nullptr } {}
	Vector(size_t size);
	~Vector();

	Vector(const Vector&);										// copy constructor
	Vector& operator=(const Vector&);							// copy assignment

	T& operator[ ] (int n) { return rep->elem[n]; }				// access: return reference
	const T& operator[ ] (int n) const { return rep->elem[n]; }

	int size() const { return (rep) ? rep->sz : 0; }			// the current size
	int capacity() const { return (rep) ? rep->space : 0; }

	void resize(size_t newsize, T def = T());					// growth
	void push_back(const T& d);
	void reserve(size_t newalloc);
private:
	VectorRepresentation<T, A>* rep;
};

void ClearInput(istream& is);
