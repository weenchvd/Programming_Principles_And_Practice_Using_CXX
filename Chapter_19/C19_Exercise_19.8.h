/* Exercise 19.8 */

using namespace std;

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
public:
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

    //Vector(const Vector&);            // copy constructor
    //Vector& operator=(const Vector&); // copy assignment

    T& operator[ ] (int n) { return elem[n]; } // access: return reference
    const T& operator[ ] (int n) const { return elem[n]; }

    int size() const { return sz; }   // the current size
    int capacity() const { return space; }

    void resize(int newsize, T def = T()); // growth
    void push_back(const T& d);
    void reserve(int newalloc);
};

void ClearInput(istream& is);
