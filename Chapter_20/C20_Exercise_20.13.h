/* Exercise 20.13 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

template<class Elem> struct Link {
	Link* prev;													// previous link
	Link* succ;													// successor (next) link
	Elem  val;													// the value
	Link(const Elem& value = Elem{}, Link* previous = nullptr, Link* successor = nullptr)
		: val{ value }, prev{ previous }, succ{ successor } {}
};

template<class Elem> class List {
	Link<Elem>* first;
public:
	class iterator;												// member type: iterator

	List() : first{ nullptr } {}
	~List();

	iterator begin() { return iterator{ first }; }				// iterator to first element
	iterator end() { return iterator{ nullptr }; }				// iterator to one beyond last element

	iterator insert(iterator previous, const Elem& value);		// insert value into list after previous
	iterator erase(iterator p);									// remove p from the list

	void push_front(const Elem& value);							// insert value at front
	void push_back(const Elem& value);							// insert value at end
	void pop_front();											// remove the first element
	void pop_back();											// remove the last element

	Elem& front() { return first->val; }						// the first element
	Elem& back();												// the last element
};

template<class Elem> class List<Elem>::iterator {
	Link<Elem>* curr;											// current node
public:
	iterator(Link<Elem>* ptr) : curr{ ptr } {}
	Link<Elem>* GetPointer() { return curr; }
	iterator& operator++() { curr = curr->succ; return *this; }			// forward
	iterator& operator--() { curr = curr->prev; return *this; }			// backwards
	Elem& operator*() { return curr->val; }						// get value (dereference)

	friend bool operator==(const iterator& a, const iterator& b) { return a.curr == b.curr; }
	friend bool operator!=(const iterator& a, const iterator& b) { return a.curr != b.curr; }
};

template<class Iterator> Iterator high(Iterator first, Iterator last);
template<class Iterator> void Print(Iterator first, Iterator last);
template<class T> void PrintList(List<T>& li, const string& message);
