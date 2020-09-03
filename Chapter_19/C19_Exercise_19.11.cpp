/* Exercise 19.11 */
/* Build and run x86-Debug only */

#include<iostream>
#include<istream>
#include<string>
#include<vector>
#include<iomanip>
#include<sstream>
#include<initializer_list>
#include"C19_Exercise_19.11.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		COUNTEDPTR
	};
	const string actionList = "\tList of actions:\n"
	"  (1) CountedPtr()\n"
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
		case COUNTEDPTR: {
			cout << space_c2 << "cpi:" << endl;
			CountedPtr<int> cpi;
			*cpi = 15;
			cout << space_c4 << "cpi == " << *cpi << endl << endl;

			cout << space_c2 << "cpd:" << endl;
			CountedPtr<double> cpd{ 3.14 };
			cout << space_c4 << "cpd == " << *cpd << endl << endl;

			cout << space_c2 << "cps:" << endl;
			CountedPtr<string> cps{ "ABCDEFFFF" };
			cout << space_c4 << "cps == " << *cps << endl;
			cout << space_c4 << "(*cps).size() == " << (*cps).size() << endl;
			cout << space_c4 << "cps->size() == " << cps->size() << endl;
			*cps = "YYY";
			cout << space_c4 << "cps == " << *cps << endl;
			cps = cps;
			cout << space_c4 << "cps == " << *cps << endl;
			CountedPtr<string> cpsdup1 = cps;
			cout << space_c4 << "cpsdup1 == " << *cpsdup1 << endl;
			CountedPtr<string> cpsdup2{"----"};
			cout << space_c4 << "cpsdup2 == " << *cpsdup2 << endl;
			cpsdup2 = cpsdup1;
			cout << space_c4 << "cpsdup2 == " << *cpsdup2 << endl << endl;

			cout << space_c2 << "cpi2:" << endl;
			CountedPtr<int> cpi2 = Create(int{ 555 });
			cout << space_c4 << "cpi2 == " << *cpi2 << endl << endl;

			cout << space_c2 << "cps2:" << endl;
			CountedPtr<string> cps2 = Create(string{ "C++ Programming Language" });
			cout << space_c4 << "cps2 == " << *cps2 << endl << endl;
			
			cout << space_c2 << "cps3:" << endl;
			CountedPtr<string> cps3 = CountedPtr<string> {"YYYADF-------------" };
			cout << space_c4 << "cps3 == " << *cps3 << endl << endl;

			cout << space_c2 << "cps4:" << endl;
			CountedPtr<string> cps4{ "+-+-+-+-+-+" };
			cout << space_c4 << "cps4 == " << *cps4 << endl;
			cps3 = cps4;
			cout << space_c4 << "cps3 == " << *cps3 << endl << endl;

			cout << space_c2 << "cpv:" << endl;
			vector<CountedPtr<char>> cpv(5);
			*(cpv[0]) = 'a';
			*(cpv[1]) = 'X';
			*(cpv[2]) = '~';
			*(cpv[4]) = '#';
			cout << space_c4 << "cpv[0] == '" << *(cpv[0]) << "', "
				<< space_c4 << "cpv[1] == '" << *(cpv[1]) << "', "
				<< space_c4 << "cpv[2] == '" << *(cpv[2]) << "', "
				<< space_c4 << "cpv[3] == '" << *(cpv[3]) << "', "
				<< space_c4 << "cpv[4] == '" << *(cpv[4]) << "'" << endl;


			cout << endl << endl << space_c2 << "End of 'case COUNTEDPTR'" << endl;
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

template<class T> CountedPtr<T>::CountedPtr()
{
#if SHOWDEBUGINFO
	cout << space_c8 << "Ctor of CountedPtr(): ";
#endif
	cp = new T();
	ctr = new int{ 1 };
#if SHOWDEBUGINFO
	cout << "cp == " << *cp << ", ctr == " << *ctr << endl;
#endif
}

template<class T> CountedPtr<T>::CountedPtr(T val)
{
#if SHOWDEBUGINFO
	cout << space_c8 << "Ctor of CountedPtr(" << val << "): ";
#endif
	cp = new T{ val };
	ctr = new int{ 1 };
#if SHOWDEBUGINFO
	cout << "cp == " << *cp << ", ctr == " << *ctr << endl;
#endif
}

template<class T> CountedPtr<T>::~CountedPtr()
{
#if SHOWDEBUGINFO
	cout << space_c8 << "Dtor of CountedPtr: ";
	cout << "cp == " << *cp << ", ctr == " << *ctr << " -> ";
	if ((*ctr) - 1 > 0) cout << "cp == " << *cp << ", ctr == " << *ctr - 1 << endl;
#endif
	if (--(*ctr) > 0) return;
#if SHOWDEBUGINFO
	cout << "cp == " << *cp << ", ctr == " << *ctr << endl;
#endif
	ReleaseMemory();
}

template<class T> CountedPtr<T>::CountedPtr(const CountedPtr<T>& p)
{
	cp = p.cp;
	ctr = p.ctr;
	(*ctr)++;
#if SHOWDEBUGINFO
	cout << space_c8 << "Copy ctor: cp == " << *cp << ", ctr == " << *ctr << endl;
#endif
}

template<class T> CountedPtr<T>& CountedPtr<T>::operator=(const CountedPtr<T>& p)
{
#if SHOWDEBUGINFO
	cout << space_c8 << "Copy assignment: ";
	if (this == &p) cout << "this == &p -> " << "cp == " << *cp << ", ctr == " << *ctr << endl;
	else {
		cout << "cp == " << *cp << ", ctr == " << *ctr << " -> ";
		cout << "cp == " << *p.cp << ", ctr == " << *p.ctr + 1 << endl;
	}
#endif
	if (this != &p) {
		if (--(*ctr) <= 0) ReleaseMemory();
		cp = p.cp;
		ctr = p.ctr;
		(*ctr)++;
	}
	return *this;
}

template<class T> CountedPtr<T>::CountedPtr(CountedPtr<T>&& p)
{
	cp = p.cp;
	ctr = p.ctr;
	(*ctr)++;
#if SHOWDEBUGINFO
	cout << space_c8 << "Move ctor: cp == " << *cp << ", ctr == " << *ctr << endl;
#endif
}

template<class T> CountedPtr<T>& CountedPtr<T>::operator=(CountedPtr<T>&& p)
{
#if SHOWDEBUGINFO
	cout << space_c8 << "Move assignment: ";
	if (this == &p) cout << "this == &p -> " << "cp == " << *cp << ", ctr == " << *ctr << endl;
	else {
		cout << "cp == " << *cp << ", ctr == " << *ctr << " -> ";
		cout << "cp == " << *p.cp << ", ctr == " << *p.ctr + 1 << endl;
	}
#endif
	if (this != &p) {
		if (--(*ctr) <= 0) ReleaseMemory();
		cp = p.cp;
		ctr = p.ctr;
		(*ctr)++;
	}
	return *this;
}

template<class T> void CountedPtr<T>::ReleaseMemory()
{
	delete cp;
	delete ctr;
#if SHOWDEBUGINFO
	cout << space_c8 << space_c2 << "Memory released" << endl;
#endif
}

template<class T> CountedPtr<T> Create(T val)
{
#if SHOWDEBUGINFO
	cout << space_c6 << "Create(" << val << ")\n";
#endif
	CountedPtr<T> cp{ val };
	return cp;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
