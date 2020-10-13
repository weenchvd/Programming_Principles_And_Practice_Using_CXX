/* Exercise 20.14 */

#include<iostream>
#include<istream>
#include<sstream>
#include<string>
#include<iomanip>
#include"C20_Exercise_20.14.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		SLIST
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
		case SLIST: {
			cout << endl;
			SList<int> li;
			PrintList(li, "Initial SList<int>:");

			li.push_front(1);
			PrintList(li, "SList<int> after li.push_front(1):");
			li.pop_front();
			PrintList(li, "SList<int> after li.pop_front():");
			li.push_front(2);
			PrintList(li, "SList<int> after li.push_front(2):");
			li.pop_front();
			PrintList(li, "SList<int> after li.pop_front():");
			li.push_front(3);
			PrintList(li, "SList<int> after li.push_front(3):");
			li.pop_front();
			PrintList(li, "SList<int> after li.pop_front():");
			li.push_front(4);
			PrintList(li, "SList<int> after li.push_front(4):");
			li.pop_front();
			PrintList(li, "SList<int> after li.pop_front():");
			cout << endl;

			li.push_front(-22);
			PrintList(li, "SList<int> after li.push_front(-22):");
			li.push_front(10);
			PrintList(li, "SList<int> after li.push_front(10):");
			li.push_front(-21);
			PrintList(li, "SList<int> after li.push_front(-21):");
			li.push_front(-20);
			PrintList(li, "SList<int> after li.push_front(-20):");
			li.push_front(11);
			PrintList(li, "SList<int> after li.push_front(11):");
			li.push_front(12);
			PrintList(li, "SList<int> after li.push_front(12):");
			li.pop_front();
			PrintList(li, "SList<int> after li.pop_front():");
			li.pop_front();
			PrintList(li, "SList<int> after li.pop_front():");
			li.pop_front();
			PrintList(li, "SList<int> after li.pop_front():");
			cout << endl;

			SList<int>::iterator it = li.insert(li.begin(), 111);
			PrintList(li, "SList<int> after it = li.insert(li.begin(), 111):");
			li.insert(it, 222);
			PrintList(li, "SList<int> after li.insert(it, 222):");
			li.insert(li.end(), 333);
			PrintList(li, "SList<int> after li.insert(li.end(), 333):");
			li.erase(li.end());
			PrintList(li, "SList<int> after li.erase(li.end()):");
			li.erase(li.begin());
			PrintList(li, "SList<int> after li.erase(li.begin()):");
			li.erase(it);
			PrintList(li, "SList<int> after li.erase(it):");
			cout << endl;

			li.push_front(555);
			PrintList(li, "SList<int> after li.push_front(555):");
			Link<int>* p;
			for (p = li.begin().GetPointer(); p->succ != nullptr; p = p->succ);
			li.erase(SList<int>::iterator{ p });
			PrintList(li, "SList<int> after li.erase(SList<int>::iterator{ p }):");
			li.push_front(666);
			PrintList(li, "SList<int> after li.push_front(666):");
			li.erase(li.begin());
			PrintList(li, "SList<int> after li.erase(li.begin()):");
			li.pop_front();
			PrintList(li, "SList<int> after li.pop_front():");
			li.pop_front();
			PrintList(li, "SList<int> after li.pop_front():");
			li.insert(li.begin(), 17);
			PrintList(li, "SList<int> after li.insert(li.begin(), 17):");
			li.insert(li.begin(), 32);
			PrintList(li, "SList<int> after li.insert(li.begin(), 32):");
			li.push_front(77);
			PrintList(li, "SList<int> after li.push_front(77):");
			li.push_front(0);
			PrintList(li, "SList<int> after li.push_front(0):");
			li.push_front(25);
			PrintList(li, "SList<int> after li.push_front(25):");
			li.push_front(26);
			PrintList(li, "SList<int> after li.push_front(26):");
			li.push_front(14);
			PrintList(li, "SList<int> after li.push_front(14):");
			cout << endl;

			cout << sp_2 << "SList<int> front(): " << li.front() << endl;
			cout << sp_2 << "SList<int> back(): " << li.back() << endl;

			SList<int>::iterator highest = high(li.begin(), li.end());
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
SList<Elem>::~SList()
{
	while (first != nullptr) {
		Link<Elem>* succ = first->succ;
		delete first;
		first = succ;
	}
}

template<class Elem>
SList<Elem>::template iterator SList<Elem>::insert(iterator previous, const Elem& value)
{
	Link<Elem>* prev = previous.GetPointer();
	if (prev == nullptr) return iterator{ nullptr };
	Link<Elem>* ptr = new Link<Elem>(value, prev->succ);
	prev->succ = ptr;
	return iterator{ ptr };
}

template<class Elem>
SList<Elem>::template iterator SList<Elem>::erase(iterator p)
{
	Link<Elem>* ptr = p.GetPointer();
	if (ptr == nullptr) return p;
	Link<Elem>* prev;
	if (ptr == first) {
		first = ptr->succ;
		prev = nullptr;
	}
	else {
		for (prev = first; prev->succ != ptr; prev = prev->succ);
		prev->succ = ptr->succ;
	}
	delete ptr;
	return iterator{ prev };
}

template<class Elem>
void SList<Elem>::push_front(const Elem& value)
{
	first = new Link<Elem>(value, first);
}

template<class Elem>
void SList<Elem>::pop_front()
{
	if (first == nullptr) return;
	Link<Elem>* front = first;
	first = first->succ;
	delete front;
}

template<class Elem>
Elem& SList<Elem>::back()
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

template<class T> void PrintList(SList<T>& li, const string& message)
{
	cout << sp_2 << message << endl << sp_4;
	Print(li.begin(), li.end());
	cout << endl;
}
