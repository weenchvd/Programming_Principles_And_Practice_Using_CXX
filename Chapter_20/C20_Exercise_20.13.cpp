/* Exercise 20.13 */

#include<iostream>
#include<istream>
#include<sstream>
#include<string>
#include<iomanip>
#include"C20_Exercise_20.13.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		LIST
	};
	const string actionList = "\tList of actions:\n"
		"  (1) high()\n"
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
		case LIST: {
			cout << endl;
			List<int> li;
			PrintList(li, "Initial List<int>:");

			li.push_back(1);
			PrintList(li, "List<int> after li.push_back(1):");
			li.pop_back();
			PrintList(li, "List<int> after li.pop_back():");
			li.push_back(2);
			PrintList(li, "List<int> after li.push_back(2):");
			li.pop_front();
			PrintList(li, "List<int> after li.pop_front():");
			li.push_front(3);
			PrintList(li, "List<int> after li.push_front(3):");
			li.pop_back();
			PrintList(li, "List<int> after li.pop_back():");
			li.push_front(4);
			PrintList(li, "List<int> after li.push_front(4):");
			li.pop_front();
			PrintList(li, "List<int> after li.pop_front():");
			cout << endl;

			li.push_back(-22);
			PrintList(li, "List<int> after li.push_back(-22):");
			li.push_front(10);
			PrintList(li, "List<int> after li.push_front(10):");
			li.push_back(-21);
			PrintList(li, "List<int> after li.push_back(-21):");
			li.push_back(-20);
			PrintList(li, "List<int> after li.push_back(-20):");
			li.push_front(11);
			PrintList(li, "List<int> after li.push_front(11):");
			li.push_front(12);
			PrintList(li, "List<int> after li.push_front(12):");
			li.pop_back();
			PrintList(li, "List<int> after li.pop_back():");
			li.pop_front();
			PrintList(li, "List<int> after li.pop_front():");
			li.pop_front();
			PrintList(li, "List<int> after li.pop_front():");
			cout << endl;

			List<int>::iterator it = li.insert(li.begin(), 111);
			PrintList(li, "List<int> after it = li.insert(li.begin(), 111):");
			li.insert(it, 222);
			PrintList(li, "List<int> after li.insert(it, 222):");
			li.insert(li.end(), 333);
			PrintList(li, "List<int> after li.insert(li.end(), 333):");
			li.erase(li.end());
			PrintList(li, "List<int> after li.erase(li.end()):");
			li.erase(li.begin());
			PrintList(li, "List<int> after li.erase(li.begin()):");
			li.erase(it);
			PrintList(li, "List<int> after li.erase(it):");
			cout << endl;

			li.push_back(555);
			PrintList(li, "List<int> after li.push_back(555):");
			Link<int>* p;
			for (p = li.begin().GetPointer(); p->succ != nullptr; p = p->succ);
			li.erase(List<int>::iterator{ p });
			PrintList(li, "List<int> after li.erase(List<int>::iterator{ p }):");
			li.push_front(666);
			PrintList(li, "List<int> after li.push_front(666):");
			li.erase(li.begin());
			PrintList(li, "List<int> after li.erase(li.begin()):");
			li.pop_back();
			PrintList(li, "List<int> after li.pop_back():");
			li.pop_front();
			PrintList(li, "List<int> after li.pop_front():");
			li.insert(li.begin(), 17);
			PrintList(li, "List<int> after li.insert(li.begin(), 17):");
			li.insert(li.begin(), 32);
			PrintList(li, "List<int> after li.insert(li.begin(), 32):");
			li.push_front(77);
			PrintList(li, "List<int> after li.push_front(77):");
			li.push_front(0);
			PrintList(li, "List<int> after li.push_front(0):");
			li.push_back(25);
			PrintList(li, "List<int> after li.push_back(25):");
			li.push_back(26);
			PrintList(li, "List<int> after li.push_back(26):");
			li.push_front(14);
			PrintList(li, "List<int> after li.push_front(14):");
			cout << endl;

			cout << sp_2 << "List<int> front(): " << li.front() << endl;
			cout << sp_2 << "List<int> back(): " << li.back() << endl;

			List<int>::iterator highest = high(li.begin(), li.end());
			cout << sp_2 << "high(): " << *highest << endl;

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
