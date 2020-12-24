/* Exercise 27.4 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include<cassert>
#include"C27_Exercise_27.4.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Test(the test only works in the debug configuration)\n"
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
		case CASE1: {
			cout << endl;

			List<string> ls;
			ls.PushBack("Alexa");
			assert(ls.GetFront().data == "Alexa");
			assert(ls.GetFront().prev == nullptr);
			assert(ls.GetFront().succ == nullptr);
			assert(&ls.GetFront() == &ls.GetBack());
			ls.PushBack("Siri");
			assert(ls.GetFront().data == "Alexa");
			assert(ls.GetFront().prev == nullptr);
			assert(ls.GetFront().succ == &ls.GetBack());
			assert(ls.GetBack().data == "Siri");
			assert(ls.GetBack().prev == &ls.GetFront());
			assert(ls.GetBack().succ == nullptr);
			ls.Clear();

			ls.PushFront("Alexa");
			assert(ls.GetFront().data == "Alexa");
			assert(ls.GetFront().prev == nullptr);
			assert(ls.GetFront().succ == nullptr);
			assert(&ls.GetFront() == &ls.GetBack());
			ls.PushFront("Siri");
			assert(ls.GetFront().data == "Siri");
			assert(ls.GetFront().prev == nullptr);
			assert(ls.GetFront().succ == &ls.GetBack());
			assert(ls.GetBack().data == "Alexa");
			assert(ls.GetBack().prev == &ls.GetFront());
			assert(ls.GetBack().succ == nullptr);

			Link<string>& alexa = ls.Advance(ls.GetFront(), 1);
			assert(alexa.data == "Alexa");
			Link<string>& siri = ls.Advance(ls.GetBack(), -1);
			assert(siri.data == "Siri");

			ls.Insert("Naomi", ls.GetFront());
			assert(ls.GetFront().data == "Naomi");
			assert(ls.GetFront().prev == nullptr);
			assert(ls.GetFront().succ == &siri);
			ls.Insert("Petra", ls.GetBack());
			assert(ls.Advance(ls.GetBack(), -1).data == "Petra");
			assert(ls.Advance(ls.GetBack(), -1).prev->data == "Siri");
			assert(ls.Advance(ls.GetBack(), -1).succ->data == "Alexa");
			ls.Insert("Alisa", ls.Advance(ls.GetBack(), -1));
			assert(ls.Advance(ls.GetFront(), 0).data == "Naomi");
			assert(ls.Advance(ls.GetFront(), 1).data == "Siri");
			assert(ls.Advance(ls.GetFront(), 2).data == "Alisa");
			assert(ls.Advance(ls.GetFront(), 3).data == "Petra");
			assert(ls.Advance(ls.GetFront(), 4).data == "Alexa");

			ls.Erase(siri);
			assert(ls.Advance(ls.GetFront(), 0).data == "Naomi");
			assert(ls.Advance(ls.GetFront(), 1).data == "Alisa");
			assert(ls.Advance(ls.GetFront(), 2).data == "Petra");
			assert(ls.Advance(ls.GetFront(), 3).data == "Alexa");
			ls.Erase(ls.GetFront());
			assert(ls.Advance(ls.GetFront(), 0).data == "Alisa");
			assert(ls.Advance(ls.GetFront(), 1).data == "Petra");
			assert(ls.Advance(ls.GetFront(), 2).data == "Alexa");
			ls.Erase(ls.GetBack());
			assert(ls.Advance(ls.GetFront(), 0).data == "Alisa");
			assert(ls.Advance(ls.GetFront(), 1).data == "Petra");

			
			cout << "\t\tAll tests passed" << endl;

			cout << vsp_2;
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
		cerr << "Runtime error. " << e.what() << endl;
	}
	catch (exception& e) {
		cerr << "Error. " << e.what() << endl;
	}
	catch (...) {
		cerr << "Exception" << endl;
		return 1;
	}
	return 0;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}

template<class T> List<T>::~List()
{
	Clear();
}

template<class T> Link<T>& List<T>::GetFront()
{
	if (first == nullptr) throw out_of_range{ "List::GetFront()" };
	return *first;
}

template<class T> const Link<T>& List<T>::GetFront() const
{
	if (first == nullptr) throw out_of_range{ "List::GetFront() const" };
	return *first;
}

template<class T> Link<T>& List<T>::GetBack()
{
	if (last == nullptr) throw out_of_range{ "List::GetBack()" };
	return *last;
}

template<class T> const Link<T>& List<T>::GetBack() const
{
	if (last == nullptr) throw out_of_range{ "List::GetBack() const" };
	return *last;
}

template<class T> void List<T>::PushFront(const T& data)
{
	Link<T>* pl = new Link<T>{ nullptr, nullptr, data };
	if (first != nullptr) {
		pl->succ = first;
		first->prev = pl;
	}
	else {
		last = pl;
	}
	first = pl;
}

template<class T> void List<T>::PushBack(const T& data)
{
	Link<T>* pl = new Link<T>{ nullptr, nullptr, data };
	if (last != nullptr) {
		last->succ = pl;
		pl->prev = last;
	}
	else {
		first = pl;
	}
	last = pl;
}

template<class T> void List<T>::Insert(const T& data, Link<T>& link)
{
	Link<T>* pl = new Link<T>{ nullptr, nullptr, data };
	pl->prev = link.prev;
	pl->succ = &link;
	if (&link == first) {
		first = pl;
	}
	else {
		link.prev->succ = pl;
	}
	link.prev = pl;
}

template<class T> T List<T>::Erase(Link<T>& link)
{
	T ret = link.data;
	Link<T>* pl = &link;
	if (pl == first) {
		if (pl->succ != nullptr) {
			first = pl->succ;
			pl->succ->prev = nullptr;
		}
		else {
			first = last = nullptr;
		}
	}
	else if (pl == last) {
		if (pl->prev != nullptr) {
			last = pl->prev;
			pl->prev->succ = nullptr;
		}
		else {
			first = last = nullptr;
		}
	}
	else {
		pl->succ->prev = pl->prev;
		pl->prev->succ = pl->succ;
	}
	delete pl;
	return ret;
}

template<class T> Link<T>& List<T>::Advance(Link<T>& link, int n)
{
	Link<T>* pl = &link;
	while (n != 0 && pl != nullptr) {
		if (n > 0) {
			pl = pl->succ;
			--n;
		}
		else {
			pl = pl->prev;
			++n;
		}
	}
	if (pl == nullptr) throw out_of_range{ "List::Advance()" };
	return *pl;
}

template<class T> const Link<T>& List<T>::Advance(const Link<T>& link, int n) const
{
	const Link<T>* pl = &link;
	while (n != 0 && pl != nullptr) {
		if (n > 0) {
			pl = pl->succ;
			--n;
		}
		else {
			pl = pl->prev;
			++n;
		}
	}
	if (pl == nullptr) throw out_of_range{ "List::Advance()" };
	return *pl;
}

template<class T> void List<T>::Clear()
{
	Link<T>* cur = first;
	while (cur != nullptr) {
		Link<T>* next = cur->succ;
		delete cur;
		cur = next;
	}
	first = last = nullptr;
}
