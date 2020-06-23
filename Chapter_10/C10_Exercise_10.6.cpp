/* Exercise 10.6 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<cstdio>
#include"C10_Exercise_10.6.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }
inline int randint(int max) { return rand() % max; }
inline int randint(int min, int max) { return randint(max - min) + min; }


int main()
{
	const string errMessageInputFile = "Error. Can't open input file: ";
	const string errMessageOutputFile = "Error. Can't open output file: ";
	enum Action {
		EXIT = -1, PRINTACTIONLIST, OPINPUT, OPOUTPUT
	};
	const string actionList = "\tList of actions:\n"
	"  (1) operator>>, (2) operator<<\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	bool cond{ true };
	int action;
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case OPINPUT: {
			RomanNumerals::Roman_int r;
			cout << "Please enter a Roman: ";
			cin >> r;
			cout << "Roman " << r << " equals " << r.as_int() << endl;
			break;
		}
		case OPOUTPUT: {
			int num;
			cout << "Please enter an integer: ";
			cin >> num;
			RomanNumerals::Roman_int r(num);
			cout << "Integer " << r.as_int() << " equals " << r << endl;
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
	catch (RomanNumerals::Roman_int::Invalid& e) {
		cerr << "Error. Roman is invalid\n";
	}
	catch (...) {
		cerr << "Error. Exception\n";
		return 1;
	}
	return 0;
}

namespace RomanNumerals {
	Roman_int::Roman_int(int v)
		: value{ v }
	{
		if (v < 0 || v > int(Letter::MAX)) throw Roman_int::Invalid{};
	}

	ostream& operator<<(ostream& os, const Roman_int& r)
	{
		os << IntToRoman(r.as_int());
		return os;
	}

	string IntToRoman(const int integer)
	{
		int num = integer;
		if (num < 0 || num > int(Letter::MAX)) throw Roman_int::Invalid{};
		if (num == 0) return "N";
		string roman;
		int multiplier = 0;
		for (; num > 0; num /= 10) (multiplier > 0) ? multiplier *= 10 : multiplier = 1;
		for (; multiplier > 0; multiplier /= 10) {
			int i = integer / multiplier;
			i %= 10;
			switch (multiplier) {
			case 1000:
				roman += M[i];
				break;
			case 100:
				roman += C[i];
				break;
			case 10:
				roman += X[i];
				break;
			case 1:
				roman += I[i];
				break;
			default:
				throw Roman_int::Invalid{};
				break;
			}
		}
		return roman;
	}

	istream& operator>>(istream& is, Roman_int& r)
	{
		string roman;
		if (!(is >> roman)) { ClearInput(cin); error("Error. Incorrect input"); }
		r = Roman_int(RomanToInt(roman));
		return is;
	}

	int RomanToInt(const string& roman)
	{
		char ch;
		int num = 0;
		int temp = 0;
		Letter previous = Letter::MAX;
		for (int i = 0; i < roman.size(); i++) {
			ch = roman[i];
			switch (ch) {
			case 'M':
				// case MM, MMM
				if (previous == Letter::M && temp <= maxLettersBefore * int(Letter::M)
					&& temp >= int(Letter::M)) {
					temp += int(Letter::M);
				}
				// case CM
				else if (previous == Letter::C && temp == int(Letter::C)) {
					temp = int(Letter::M) - int(Letter::C);
					previous = Letter::M;
				}
				// case M
				else if (previous > Letter::M) {
					num += temp;
					temp = int(Letter::M);
					previous = Letter::M;
				}
				else throw Roman_int::Invalid{};
				break;
			case 'D':
				// case CD
				if (previous == Letter::C && temp == int(Letter::C)) {
					temp = int(Letter::D) - int(Letter::C);
					previous = Letter::D;
				}
				// case D
				else if (previous > Letter::D && (temp >= int(Letter::M) || temp == 0)) {
					num += temp;
					temp = int(Letter::D);
					previous = Letter::D;
				}
				else throw Roman_int::Invalid{};
				break;
			case 'C':
				// case CC, CCC
				if (previous == Letter::C && temp <= maxLettersBefore * int(Letter::C)
					&& temp >= int(Letter::C)) {
					temp += int(Letter::C);
				}
				// case DC, DCC, DCCC
				else if (previous == Letter::D && temp <= int(Letter::D) + maxLettersBefore * int(Letter::C)
					&& temp >= int(Letter::D)) {
					temp += int(Letter::C);
				}
				// case XC
				else if (previous == Letter::X && temp == int(Letter::X)) {
					temp = int(Letter::C) - int(Letter::X);
					previous = Letter::C;
				}
				// case C
				else if (previous > Letter::C && (temp >= int(Letter::M) || temp == 0)) {
					num += temp;
					temp = int(Letter::C);
					previous = Letter::C;
				}
				else throw Roman_int::Invalid{};
				break;
			case 'L':
				// case XL
				if (previous == Letter::X && temp == int(Letter::X)) {
					temp = int(Letter::L) - int(Letter::X);
					previous = Letter::L;
				}
				// case L
				else if (previous > Letter::L && (temp >= int(Letter::C) || temp == 0)) {
					num += temp;
					temp = int(Letter::L);
					previous = Letter::L;
				}
				else throw Roman_int::Invalid{};
				break;
			case 'X':
				// case XX, XXX
				if (previous == Letter::X && temp <= maxLettersBefore * int(Letter::X)
					&& temp >= int(Letter::X)) {
					temp += int(Letter::X);
				}
				// case LX, LXX, LXXX
				else if (previous == Letter::L && temp <= int(Letter::L) + maxLettersBefore * int(Letter::X)
					&& temp >= int(Letter::L)) {
					temp += int(Letter::X);
				}
				// case IX
				else if (previous == Letter::I && temp == int(Letter::I)) {
					temp = int(Letter::X) - int(Letter::I);
					previous = Letter::X;
				}
				// case X
				else if (previous > Letter::X && (temp >= int(Letter::C) || temp == 0)) {
					num += temp;
					temp = int(Letter::X);
					previous = Letter::X;
				}
				else throw Roman_int::Invalid{};
				break;
			case 'V':
				// case IV
				if (previous == Letter::I && temp == int(Letter::I)) {
					temp = int(Letter::V) - int(Letter::I);
					previous = Letter::V;
				}
				// case V
				else if (previous > Letter::V && (temp >= int(Letter::X) || temp == 0)) {
					num += temp;
					temp = int(Letter::V);
					previous = Letter::V;
				}
				else throw Roman_int::Invalid{};
				break;
			case 'I':
				// case II, III
				if (previous == Letter::I && temp <= maxLettersBefore * int(Letter::I)
					&& temp >= int(Letter::I)) {
					temp += int(Letter::I);
				}
				// case VI, VII, VIII
				else if (previous == Letter::V && temp <= int(Letter::V) + maxLettersBefore * int(Letter::I)
					&& temp >= int(Letter::V)) {
					temp += int(Letter::I);
				}
				// case I
				else if (previous > Letter::I && (temp >= int(Letter::X) || temp == 0)) {
					num += temp;
					temp = int(Letter::I);
					previous = Letter::I;
				}
				else throw Roman_int::Invalid{};
				break;
			default:
				throw Roman_int::Invalid{};
				break;
			}
		}
		num += temp;
		return num;
	}

} // RomanNumerals

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
