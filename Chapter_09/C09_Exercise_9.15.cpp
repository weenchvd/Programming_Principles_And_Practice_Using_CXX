/* Exercise 9.15 */
/* Exercise 9.16 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>
#include"C09_Exercise_9.15.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST, CURRENCIESLIST, ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION
	};
	const string actionList = "\tList of actions:\n"
	"  (1) List of currencies, (2) operator+(), (3) operator-(), (4) operator*(), (5) operator/()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	bool cond{ true };
	int action;
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Incorrect input"); }
		switch (action) {
		case CURRENCIESLIST:
			for (int i = 0; i < Finance::curName.size(); i++) {
				cout << Finance::curName[i] << " ";
			}
			cout << endl;
			break;
		case ADDITION: {
			cout << "Please enter the Money1\n";
			Finance::Money m1 = GetMoney();
			cout << "Please enter the Money2\n";
			Finance::Money m2 = GetMoney();
			cout << "  " << m1 << " + " << m2 << " == " << m1 + m2 << endl;
			break;
		}
		case SUBTRACTION: {
			cout << "Please enter the Money1\n";
			Finance::Money m1 = GetMoney();
			cout << "Please enter the Money2\n";
			Finance::Money m2 = GetMoney();
			cout << "  " << m1 << " - " << m2 << " == " << m1 - m2 << endl;
			break;
		}
		case MULTIPLICATION: {
			cout << "Please enter the Money1\n";
			Finance::Money m1 = GetMoney();
			double d;
			cout << "Please enter a multiplier: ";
			if (!(cin >> d)) { ClearInput(cin); error("Incorrect input"); }
			cout << "  " << m1 << " * " << d << " == " << m1 * d << endl;
			break;
		}
		case DIVISION: {
			cout << "Please enter the Money1\n";
			Finance::Money m1 = GetMoney();
			double d;
			cout << "Please enter a divisor: ";
			if (!(cin >> d)) { ClearInput(cin); error("Incorrect input"); }
			cout << "  " << m1 << " / " << d << " == " << m1 / d << endl;
			break;
		}
		case PRINTACTIONLIST:
			cout << actionList;
			break;
		case EXIT:
			cond = false;
			break;
		default:
			error("Incorrect action number");
			break;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	catch (Finance::Money::Invalid& e) {
		cerr << "Money is invalid\n";
	}
	catch (...) {
		cerr << "exception\n";
		return 1;
	}
}

namespace Finance {
	Money::Money(long int dol, long int cent, Currency currency)
		: cents{ dol * 100 }, cur{ currency }
	{
		if (dol < 0 || cent < 0) throw Invalid{};
		while (cent > 99) {
			if (cent > 999) cent /= 10;
			else {
				int remainder{ cent % 10 };
				cent = cent / 10;
				if (remainder >= 5) cent++;
				break;
			}
		}
		cents += cent;
	}

	Money operator+(const Money& a, const Money& b)
	{
		if (a.GetCurrency() != b.GetCurrency()) error("The currencies are not identical");
		return Money(a.Get() + b.Get(), a.GetCurrency());
	}

	Money operator-(const Money& a, const Money& b)
	{
		if (a.GetCurrency() != b.GetCurrency()) error("The currencies are not identical");
		return Money(a.Get() - b.Get(), a.GetCurrency());
	}

	Money operator*(const Money& a, const double d)
	{
		double product = double(a.Get()) * d;
		long int ret = product;
		product *= 10;
		int remainder = int(product) - ret * 10;
		if (remainder >= 5) ret++;
		return Money(ret, a.GetCurrency());
	}

	Money operator/(const Money& a, const double d)
	{
		if (d == 0) error("Division by 0");
		double quotient = double(a.Get()) / d;
		long int ret = quotient;
		quotient *= 10;
		int remainder = int(quotient) - ret * 10;
		if (remainder >= 5) ret++;
		return Money(ret, a.GetCurrency());
	}

	istream& operator>>(istream& is, Money& m)
	{
		char ch1, ch2, ch3, ch4;
		long int dol, cent;
		if (!(is >> ch1 >> ch2 >> ch3 >> dol >> ch4 >> cent)) { ClearInput(is); error("Incorrect input"); }
		if (ch4 != '.') { ClearInput(is); error("Incorrect input"); }
		string s;
		s = ((s + ch1) + ch2) + ch3;
		Currency cur;
		int i;
		for (i = 0; i < curName.size(); i++) {
			if (s == curName[i]) {
				cur = Currency(i);
				break;
			}
		}
		if (i >= curName.size()) error("Incorrect the currency");
		m = Money(dol, cent, cur);
		return is;
	}

	ostream& operator<<(ostream& os, const Money& m)
	{
		os << curName[int(m.GetCurrency())] << m.GetIntegerPart()<< "." << m.GetFractionalPart();
		return os;
	}
} //Finance

Finance::Money GetMoney()
{
	Finance::Money m;
	cout << "Please enter the amount of money (example, \"USD12.0\" or \"RUB1499.99\"): ";
	if (!(cin >> m)) { ClearInput(cin); error("Incorrect input"); }
	return m;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
