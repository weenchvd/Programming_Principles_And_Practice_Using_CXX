/* Exercise 20.19 */

#include<iostream>
#include<istream>
#include<sstream>
#include<string>
#include<iomanip>
#include"C20_Exercise_20.19.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		ITERATOR
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Iterator\n"
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
		case ITERATOR: {
			cout << endl;
			List<int> li;
			PrintList(li, "Initial List<int>:");

			li.push_back(1);
			li.push_back(2);
			li.push_front(3);
			li.push_front(4);
			li.push_back(-22);
			li.push_front(10);
			li.push_back(-21);
			li.push_back(-20);
			li.push_front(11);
			li.push_front(12);
			PrintList(li, "List<int> state 1:");
			cout << endl;

			List<int>::iterator it = li.insert(li.begin(), 111);
			li.insert(it, 222);
			li.insert(li.end(), 333);
			li.erase(li.end());
			li.erase(li.begin());
			li.erase(it);
			PrintList(li, "List<int> state 2:");
			cout << endl;

			cout << sp_2 << "List<int> front(): " << li.front() << endl;
			cout << sp_2 << "List<int> back(): " << li.back() << endl;

			List<int>::iterator highest = high(li.begin(), li.end());
			cout << sp_2 << "high(): " << *highest << endl;
			it = li.begin();
			cout << sp_2 << "*it: " << *it << endl;
			cout << sp_2 << "*++it: " << *++it << endl;
			cout << sp_2 << "*--it: " << *--it << endl;
			cout << sp_2 << "*++it: " << *++it << endl;
			cout << sp_2 << "*++it: " << *++it << endl;
			cout << sp_2 << "*++it: " << *++it << endl;
			cout << sp_2 << "*++it: " << *++it << endl;
			cout << sp_2 << "*++it: " << *++it << endl;
			cout << sp_2 << "*++it: " << *++it << endl;
			cout << sp_2 << "*++it: " << *++it << endl;
			cout << sp_2 << "*++it: " << *++it << endl;
			cout << sp_2 << "*++it: " << *++it << endl;
			cout << sp_2 << "*++it: " << *++it << endl; // throw exception "out_of_range"

			cout << endl;
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

template<class Elem>
List<Elem>::~List()
{
	while (first != nullptr) {
		Link<Elem>* succ = first->succ;
		delete first;
		first = succ;
	}
}

template<class Elem>
List<Elem>::template iterator List<Elem>::insert(iterator previous, const Elem& value)
{
	Link<Elem>* prev = previous.GetPointer();
	if (prev == nullptr) return iterator{ nullptr };
	Link<Elem>* ptr = new Link<Elem>(value, prev, prev->succ);
	if (prev->succ != nullptr) prev->succ->prev = ptr;
	prev->succ = ptr;
	return iterator{ ptr };
}

template<class Elem>
List<Elem>::template iterator List<Elem>::erase(iterator p)
{
	Link<Elem>* ptr = p.GetPointer();
	if (ptr == nullptr) return p;
	if (ptr == first) first = ptr->succ;
	if (ptr->prev != nullptr) ptr->prev->succ = ptr->succ;
	if (ptr->succ != nullptr) ptr->succ->prev = ptr->prev;
	Link<Elem>* prev = ptr->prev;
	delete ptr;
	return iterator{ prev };
}

template<class Elem>
void List<Elem>::push_front(const Elem& value)
{
	first = new Link<Elem>(value, nullptr, first);
	if (first->succ != nullptr) first->succ->prev = first;
}

template<class Elem>
void List<Elem>::push_back(const Elem& value)
{
	if (first == nullptr) {
		first = new Link<Elem>(value, nullptr, nullptr);
		return;
	}
	Link<Elem>* back;
	for (back = first; back->succ != nullptr; back = back->succ);
	back->succ = new Link<Elem>(value, back, nullptr);
}

template<class Elem>
void List<Elem>::pop_front()
{
	if (first == nullptr) return;
	Link<Elem>* front = first;
	if (first->succ == nullptr) first = nullptr;
	else {
		first->succ->prev = nullptr;
		first = first->succ;
	}
	delete front;
}

template<class Elem>
void List<Elem>::pop_back()
{
	if (first == nullptr) return;
	Link<Elem>* back;
	for (back = first; back->succ != nullptr; back = back->succ);
	if (back == first) first = nullptr;
	else back->prev->succ = nullptr;
	delete back;
}

template<class Elem>
Elem& List<Elem>::back()
{
	Link<Elem>* p;
	for (p = first; p->succ != nullptr; p = p->succ);
	return p->val;
}

template<class Elem>
Elem& List<Elem>::iterator::operator*()
{
	if (curr) return curr->val;
	else throw std::out_of_range{ "List::iterator::operator*()" };
}

template<class Elem>
const Elem& List<Elem>::iterator::operator*() const
{
	if (curr) return curr->val;
	else throw std::out_of_range{ "List::iterator::operator*() const" };
}

template<class Iterator>
Iterator high(Iterator first, Iterator last)
// return an iterator to the element in [first,last) that has the highest value
{
	Iterator high = first;
	for (Iterator p = first; p != last; ++p) {
		if (*high < *p) high = p;
	}
	return high;
}

template<class Iterator> void Print(Iterator first, Iterator last)
{
	for (Iterator it = first; it != last; ++it) cout << *it << ' ';
}

template<class T> void PrintList(List<T>& li, const string& message)
{
	cout << sp_2 << message << endl << sp_4;
	Print(li.begin(), li.end());
	cout << endl;
}
