/* Exercise 25.10 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include"C25_Exercise_25.10.h"

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
		"  (1) PPN (bitfield), (2) PPN (unsigned int)\n"
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
			Page::PPN ppn01{ 66789, 7, true, true, true, false };
			cout << sp_2 << "PPN ppn01:" << endl;
			cout << ppn01 << endl;

			ppn01.SetPFN(155);
			ppn01.CCA = 2;
			ppn01.nonreachable = false;
			ppn01.dirty = false;
			ppn01.valid = false;
			ppn01.global = true;

			cout << sp_2 << "PPN ppn01 after change:" << endl;
			cout << ppn01 << endl;

			cout << vsp_2;
			break;
		}
		case CASE2: {
			cout << endl;
			Page::PPNint ppn02;
			// initialization
			Page::SetPFN(ppn02, 66789);
			Page::SetCCA(ppn02, 7);
			Page::SetNonreachable(ppn02, false);
			Page::SetDirty(ppn02, true);
			Page::SetValid(ppn02, true);
			Page::SetGlobal(ppn02, true);

			cout << sp_2 << "PPNint ppn02:" << endl;
			cout << ppn02 << endl;

			// changing
			Page::SetPFN(ppn02, 155);
			Page::SetCCA(ppn02, 2);
			Page::SetNonreachable(ppn02, true);
			Page::SetDirty(ppn02, true);
			Page::SetValid(ppn02, false);
			Page::SetGlobal(ppn02, false);

			cout << sp_2 << "PPNint ppn02 after change:" << endl;
			cout << ppn02 << endl;

			// changing
			Page::SetPFN(ppn02, 44444);
			Page::SetCCA(ppn02, 6);
			Page::SetNonreachable(ppn02, false);
			Page::SetDirty(ppn02, false);
			Page::SetValid(ppn02, true);
			Page::SetGlobal(ppn02, true);

			cout << sp_2 << "PPNint ppn02 after change:" << endl;
			cout << ppn02 << endl;

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

Page::PPN::PPN(unsigned int PFN, unsigned CCA, bool nonreachable, bool dirty, bool valid, bool global)
	: nonreachable{ nonreachable }, dirty{ dirty }, valid{ valid }, global{ global }
{
	if (PFN > PFNmax) throw InvalidValue{};
	if (CCA > CCAmax) throw InvalidValue{};
	this->PFN = PFN;
	this->CCA = CCA;
}

void Page::PPN::SetPFN(unsigned int PFN)
{
	if (PFN > PFNmax) throw InvalidValue{};
	this->PFN = PFN;
}

void Page::PPN::SetCCA(unsigned int CCA)
{
	if (CCA > CCAmax) throw InvalidValue{};
	this->CCA = CCA;
}

ostream& Page::operator<<(ostream& os, const PPN& ppn)
{
	cout << sp_4 << "PFN: " << ppn.PFN << endl;
	cout << sp_4 << "CCA: " << ppn.CCA << endl;
	cout << sp_4 << "nonreachable: " << boolalpha << ppn.nonreachable << endl;
	cout << sp_4 << "dirty: " << ppn.dirty << endl;
	cout << sp_4 << "valid: " << ppn.valid << endl;
	cout << sp_4 << "global: " << ppn.global << noboolalpha << endl;
	return os;
}

void Page::SetPFN(PPNint& ppn, unsigned int PFN)
{
	if (PFN > PFNmax) throw InvalidValue{};
	constexpr int shift = 10;
	// erase old CCA
	unsigned int bits = PFNmax << shift;
	bits = ~bits;
	ppn.v &= bits;
	// assign new CCA
	PFN <<= shift;
	ppn.v |= PFN;
}

void Page::SetCCA(PPNint& ppn, unsigned int CCA)
{
	if (CCA > CCAmax) throw InvalidValue{};
	constexpr int shift = 4;
	// erase old CCA
	unsigned int bits = CCAmax << shift;
	bits = ~bits;
	ppn.v &= bits;
	// assign new CCA
	CCA <<= shift;
	ppn.v |= CCA;
}

void Page::SetNonreachable(PPNint& ppn, bool nonreachable)
{
	unsigned int bit = 0x8;
	if (nonreachable) ppn.v |= bit;
	else ppn.v &= ~bit;
}

void Page::SetDirty(PPNint& ppn, bool dirty)
{
	unsigned int bit = 0x4;
	if (dirty) ppn.v |= bit;
	else ppn.v &= ~bit;
}

void Page::SetValid(PPNint& ppn, bool valid)
{
	unsigned int bit = 0x2;
	if (valid) ppn.v |= bit;
	else ppn.v &= ~bit;
}

void Page::SetGlobal(PPNint& ppn, bool global)
{
	unsigned int bit = 0x1;
	if (global) ppn.v |= bit;
	else ppn.v &= ~bit;
}

ostream& Page::operator<<(ostream& os, const PPNint& ppn)
{
	constexpr int shiftPFN = 10;
	cout << sp_4 << "PFN: " << (ppn.v >> shiftPFN) << endl;
	constexpr int shiftCCA = 4;
	cout << sp_4 << "CCA: " << ((ppn.v >> shiftCCA) & CCAmax) << endl;
	constexpr int shiftNonreachable = 3;
	cout << sp_4 << "nonreachable: " << boolalpha <<  static_cast<bool>(ppn.v & 0x8) << endl;
	constexpr int shiftDirty = 2;
	cout << sp_4 << "dirty: " << static_cast<bool>(ppn.v & 0x4) << endl;
	constexpr int shiftValid = 1;
	cout << sp_4 << "valid: " << static_cast<bool>(ppn.v & 0x2) << endl;
	cout << sp_4 << "global: " << static_cast<bool>(ppn.v & 0x1) << noboolalpha << endl;
	return os;
}
