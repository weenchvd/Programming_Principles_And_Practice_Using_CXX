/* Exercise 27.4 */

#ifndef C27_Exercise_27_4_H
#define C27_Exercise_27_4_H

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

template<class T> struct Link {			// link for doubly-linked list
	Link<T>* prev;
	Link<T>* succ;
	T data;
	Link(Link<T>* previous, Link<T>* succsessor, const T& data)
		: prev{ previous }, succ{ succsessor }, data{ data } {}
};

template<class T> class List {
	Link<T>* first;
	Link<T>* last;
public:
	List() : first{ nullptr }, last{ nullptr } {}
	~List();

	Link<T>& GetFront();
	const Link<T>& GetFront() const;
	Link<T>& GetBack();
	const Link<T>& GetBack() const;

	void PushFront(const T& data);
	void PushBack(const T& data);
	void Insert(const T& data, Link<T>& link);
	T Erase(Link<T>& link);
	Link<T>& Advance(Link<T>& link, int n);
	const Link<T>& Advance(const Link<T>& link, int n) const;
	void Clear();

	List(const List<T>&) = delete;
	List<T>& operator=(const List<T>&) = delete;
};

void ClearInput(istream& is);

#endif