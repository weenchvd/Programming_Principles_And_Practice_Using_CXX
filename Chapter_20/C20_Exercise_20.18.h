/* Exercise 20.18 */

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

template<class T, class A = Allocator<T>> class Vector {
	A alloc;    // use allocate to handle memory for elements
	int sz;     // the size
	T* elem;    // a pointer to the elements
	int space;  // size+free_space

	void reserve(int newalloc);
public:
	class iterator;

	Vector() : sz(0), elem(nullptr), space(0) { }
	Vector(int s) :sz(s), space(s)
	{
		elem = alloc.allocate(s);
		for (int i = 0; i < sz; ++i) alloc.construct(&elem[i], T());    // elements are initialized
	}
	~Vector()
	{
		for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);
		alloc.deallocate(elem, space);
	}

	Vector(const Vector&) = delete;            // copy constructor
	Vector& operator=(const Vector&); // copy assignment

	iterator begin() { return iterator{ elem, elem, elem + sz }; }
	iterator end() { return iterator{ elem + sz, elem, elem + sz }; }

	T& operator[](int n) { return elem[n]; } // access: return reference
	const T& operator[](int n) const { return elem[n]; }

	int size() const { return sz; }   // the current size
	int capacity() const { return space; }

	void resize(int newsize, T def = T()); // growth
	void push_back(const T& d);
};

template<class T, class A> class Vector<T, A>::iterator {
	T* curr;
	T* begin;
	T* end;
public:
	iterator(T* ptr, T* begin, T* end) : curr{ ptr }, begin{ begin }, end{ end } {}
	iterator& operator++() { curr++; return *this; }
	iterator& operator--() { curr--; return *this; }
	T& operator*();
	const T& operator*() const;
	T& operator[](int i);
	const T& operator[](int i) const;

	friend iterator operator+(const iterator& a, int i) { return iterator{ a.curr + i, a.begin, a.end }; }
	friend iterator operator-(const iterator& a, int i) { return iterator{ a.curr - i, a.begin, a.end }; }
	friend int operator-(const iterator& a, const iterator& b) { return a.curr - b.curr; }
	friend bool operator==(const iterator& a, const iterator& b) { return a.curr == b.curr; }
	friend bool operator!=(const iterator& a, const iterator& b) { return a.curr != b.curr; }
};
