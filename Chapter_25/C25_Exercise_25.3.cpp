/* Exercise 25.3 */

#include<iostream>
#include<sstream>
#include<iomanip>
#include<bitset>
#include"C25_Exercise_25.3.h"

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
		"  (1) Bit pattern\n"
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
			constexpr int bytesInInt = 4;
			constexpr int bitsInByte = 8;
			const size_t nBits = bitsInByte * sizeof(long int);
			static_assert(sizeof(long int) == bytesInInt, "Number of bytes in long int does not match");
			bitset<nBits> bitsAllZeros;
			bitset<nBits> bitsAllOnes{ string{"11111111111111111111111111111111"} };
			bitset<nBits> bitsAlt10{ string{"10101010101010101010101010101010"} };
			bitset<nBits> bitsAlt01{ string{"01010101010101010101010101010101"} };
			bitset<nBits> bitsAlt1100{ string{"11001100110011001100110011001100"} };
			bitset<nBits> bitsAlt0011{ string{"00110011001100110011001100110011"} };
			bitset<nBits> bitsAlt1111111100000000{ string{"11111111000000001111111100000000"} };
			bitset<nBits> bitsAlt0000000011111111{ string{"00000000111111110000000011111111"} };

			unsigned long int uAllZeros = bitsAllZeros.to_ulong();
			unsigned long int uAllOnes = bitsAllOnes.to_ulong();
			unsigned long int uAlt10 = bitsAlt10.to_ulong();
			unsigned long int uAlt01 = bitsAlt01.to_ulong();
			unsigned long int uAlt1100 = bitsAlt1100.to_ulong();
			unsigned long int uAlt0011 = bitsAlt0011.to_ulong();
			unsigned long int uAlt1111111100000000 = bitsAlt1111111100000000.to_ulong();
			unsigned long int uAlt0000000011111111 = bitsAlt0000000011111111.to_ulong();

			signed long int sAllZeros = uAllZeros;
			signed long int sAllOnes = uAllOnes;
			signed long int sAlt10 = uAlt10;
			signed long int sAlt01 = uAlt01;
			signed long int sAlt1100 = uAlt1100;
			signed long int sAlt0011 = uAlt0011;
			signed long int sAlt1111111100000000 = uAlt1111111100000000;
			signed long int sAlt0000000011111111 = uAlt0000000011111111;

			cout << sp_2 << right << setw(nBits) << "Bit pattern" << ": signed integer" << endl;
			cout << sp_2 << bitsAllZeros.to_string() << ": " << sAllZeros << endl;
			cout << sp_2 << bitsAllOnes.to_string() << ": " << sAllOnes << endl;
			cout << sp_2 << bitsAlt10.to_string() << ": " << sAlt10 << endl;
			cout << sp_2 << bitsAlt01.to_string() << ": " << sAlt01 << endl;
			cout << sp_2 << bitsAlt1100.to_string() << ": " << sAlt1100 << endl;
			cout << sp_2 << bitsAlt0011.to_string() << ": " << sAlt0011 << endl;
			cout << sp_2 << bitsAlt1111111100000000.to_string() << ": " << sAlt1111111100000000 << endl;
			cout << sp_2 << bitsAlt0000000011111111.to_string() << ": " << sAlt0000000011111111 << endl;
			cout << endl;
			
			cout << sp_2 << right << setw(nBits) << "Bit pattern" << ": unsigned integer" << endl;
			cout << sp_2 << bitsAllZeros.to_string() << ": " << uAllZeros << endl;
			cout << sp_2 << bitsAllOnes.to_string() << ": " << uAllOnes << endl;
			cout << sp_2 << bitsAlt10.to_string() << ": " << uAlt10 << endl;
			cout << sp_2 << bitsAlt01.to_string() << ": " << uAlt01 << endl;
			cout << sp_2 << bitsAlt1100.to_string() << ": " << uAlt1100 << endl;
			cout << sp_2 << bitsAlt0011.to_string() << ": " << uAlt0011 << endl;
			cout << sp_2 << bitsAlt1111111100000000.to_string() << ": " << uAlt1111111100000000 << endl;
			cout << sp_2 << bitsAlt0000000011111111.to_string() << ": " << uAlt0000000011111111 << endl;


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
