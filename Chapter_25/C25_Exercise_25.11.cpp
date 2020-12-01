/* Exercise 25.11 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include<bitset>
#include"C25_Exercise_25.11.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const string actionList = "\tList of actions:\n"
		"  (1) PPN (bitset)\n"
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
			Page::PPNbitset ppn01;
			// initialization
			ppn01.Set(Page::PPNType::PFN, 66789);
			ppn01.Set(Page::PPNType::CCA, 7);
			ppn01.Set(Page::PPNType::NONREACHABLE, false);
			ppn01.Set(Page::PPNType::DIRTY, true);
			ppn01.Set(Page::PPNType::VALID, true);
			ppn01.Set(Page::PPNType::GLOBAL, true);

			cout << sp_2 << "PPNbitset ppn01:" << endl;
			cout << ppn01 << endl;

			// changing
			ppn01.Set(Page::PPNType::PFN, 155);
			ppn01.Set(Page::PPNType::CCA, 2);
			ppn01.Set(Page::PPNType::NONREACHABLE, true);
			ppn01.Set(Page::PPNType::DIRTY, true);
			ppn01.Set(Page::PPNType::VALID, false);
			ppn01.Set(Page::PPNType::GLOBAL, false);

			cout << sp_2 << "PPNbitset ppn01 after change:" << endl;
			cout << ppn01 << endl;

			// changing
			ppn01.Set(Page::PPNType::PFN, 44444);
			ppn01.Set(Page::PPNType::CCA, 6);
			ppn01.Set(Page::PPNType::NONREACHABLE, false);
			ppn01.Set(Page::PPNType::DIRTY, false);
			ppn01.Set(Page::PPNType::VALID, true);
			ppn01.Set(Page::PPNType::GLOBAL, true);

			cout << sp_2 << "PPNbitset ppn01 after change:" << endl;
			cout << ppn01 << endl;

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

/* T must be 'bool' or 'unsigned int' */
template<class T> void Page::PPNbitset::Set(Page::PPNType type, T value)
{
	switch (type) {
	case PPNType::PFN: {
		unsigned int PFNnew = value;
		if (PFNnew > PFNmax) throw InvalidValue{};
		int bit = int{ PPNType::PFN };
		for (int i = 0; i < PFNbits; ++i) {
			v[bit] = static_cast<bool>(GetFirstBitOf(PFNnew));
			++bit;
			PFNnew >>= 1;
		}
		break;
	}
	case PPNType::CCA: {
		unsigned int CCAnew = value;
		if (CCAnew > CCAmax) throw InvalidValue{};
		int bit = int{ PPNType::CCA };
		for (int i = 0; i < CCAbits; ++i) {
			v[bit] = static_cast<bool>(GetFirstBitOf(CCAnew));
			++bit;
			CCAnew >>= 1;
		}
		break;
	}
	case PPNType::NONREACHABLE:
		v[int{ PPNType::NONREACHABLE }] = value;
		break;
	case PPNType::DIRTY:
		v[int{ PPNType::DIRTY }] = value;
		break;
	case PPNType::VALID:
		v[int{ PPNType::VALID }] = value;
		break;
	case PPNType::GLOBAL:
		v[int{ PPNType::GLOBAL }] = value;
		break;
	default:
		throw InvalidType{};
	}
}

/* T must be 'bool' or 'unsigned int' */
template<class T> T Page::PPNbitset::Get(Page::PPNType type) const
{
	switch (type) {
	case PPNType::PFN: {
		unsigned int PFN = 0;
		int bit = int{ PPNType::PFN } + PFNbits - 1;
		for (int i = 0; i < PFNbits; ++i) {
			PFN <<= 1;
			if (v[bit]) PFN = SetFirstBitOf(PFN);
			--bit;
		}
		return PFN;
	}
	case PPNType::CCA: {
		unsigned int CCA = 0;
		int bit = int{ PPNType::CCA } + CCAbits - 1;
		for (int i = 0; i < CCAbits; ++i) {
			CCA <<= 1;
			if (v[bit]) CCA = SetFirstBitOf(CCA);
			--bit;
		}
		return CCA;
	}
	case PPNType::NONREACHABLE:
		return v[int{ PPNType::NONREACHABLE }];
	case PPNType::DIRTY:
		return v[int{ PPNType::DIRTY }];
	case PPNType::VALID:
		return v[int{ PPNType::VALID }];
	case PPNType::GLOBAL:
		return v[int{ PPNType::GLOBAL }];
	default:
		throw InvalidType{};
	}
}

ostream& Page::operator<<(ostream& os, const Page::PPNbitset& ppn)
{
	cout << sp_4 << "PFN: " << ppn.Get<unsigned int>(Page::PPNType::PFN) << endl;
	cout << sp_4 << "CCA: " << ppn.Get<unsigned int>(Page::PPNType::CCA) << endl;
	cout << sp_4 << "nonreachable: " << boolalpha << ppn.Get<bool>(Page::PPNType::NONREACHABLE) << endl;
	cout << sp_4 << "dirty: " << ppn.Get<bool>(Page::PPNType::DIRTY) << endl;
	cout << sp_4 << "valid: " << ppn.Get<bool>(Page::PPNType::VALID) << endl;
	cout << sp_4 << "global: " << ppn.Get<bool>(Page::PPNType::GLOBAL) << noboolalpha << endl;
	return os;
}
