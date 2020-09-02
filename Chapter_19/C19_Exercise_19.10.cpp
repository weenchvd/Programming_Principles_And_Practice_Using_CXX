/* Exercise 19.10 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include<cstdlib>
#include"C19_Exercise_19.10.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		UNIQUEPTR
	};
	const string actionList = "\tList of actions:\n"
	"  (1) UniquePtr()\n"
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
		case UNIQUEPTR: {
			cout << space_c2 << "upi:" << endl;
			UniquePtr<int> upi = { new int{15} };
			cout << space_c4 << "upi == " << *upi << endl << endl;

			cout << space_c2 << "upd:" << endl;
			UniquePtr<double> upd = { new double{3.14} };
			cout << space_c4 << "upd == " << *upd << endl;
			double* pd = upd.Release();
			cout << space_c4 << "pd == " << *pd << endl << endl;
			delete pd;

			cout << space_c2 << "ups:" << endl;
			UniquePtr<string> ups = { new string };
			*ups = "ABCDEFFFF";
			cout << space_c4 << "ups == " << *ups << endl;
			cout << space_c4 << "(*ups).size() == " << (*ups).size() << endl;
			cout << space_c4 << "ups->size() == " << ups->size() << endl << endl;

			cout << space_c2 << "upi2:" << endl;
			UniquePtr<int> upi2 = CreateInt();
			cout << space_c4 << "upi2 == " << *upi2 << endl;
			*upi2 = -88;
			cout << space_c4 << "upi2 == " << *upi2 << endl << endl;

			cout << space_c2 << "pupi:" << endl;
			UniquePtr<int>* pupi = { new UniquePtr<int>{ new int{555} } };
			cout << space_c4 << "upi3 == " << **pupi << endl;
			delete pupi;
			cout << endl;
			
			cout << space_c2 << "End of 'case UNIQUEPTR'" << endl;
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

template<class T> T* UniquePtr<T>::Release()
{
	T* p = up;
	up = nullptr;
	return p;
}

int* CreateInt()
{
	UniquePtr<int> upi = { new int };
	*upi = -99;
	return upi.Release();
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
