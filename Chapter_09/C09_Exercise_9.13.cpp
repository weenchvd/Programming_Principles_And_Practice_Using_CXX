/* Exercise 9.13 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>
#include"C09_Exercise_9.13.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST, EQUALITY, ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION
	};
	const string actionList = "\tList of actions:\n"
	"  (1) operator==(), (2) operator+(), (3) operator-(), (4) operator*(), (5) operator/()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	bool cond{ true };
	int action;
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Incorrect input"); }
		switch (action) {
		case EQUALITY: {
			cout << "Please enter the Rational1\n";
			Numbers::Rational r1 = GetRational();
			cout << "Please enter the Rational2\n";
			Numbers::Rational r2 = GetRational();
			cout << "  Rational1 (" << r1 << "), Rational2 (" << r2 << ")\n";
			cout << "  Rational1 " << ((r1 == r2) ? "==" : "!=") << " Rational2\n";
			break;
		}
		case ADDITION: {
			cout << "Please enter the Rational1\n";
			Numbers::Rational r1 = GetRational();
			cout << "Please enter the Rational2\n";
			Numbers::Rational r2 = GetRational();
			cout << "  Rational1 (" << r1 << "), Rational2 (" << r2 << ")\n";
			cout << "  Rational1 + Rational2 == " << r1 + r2 << endl;
			break;
		}
		case SUBTRACTION: {
			cout << "Please enter the Rational1\n";
			Numbers::Rational r1 = GetRational();
			cout << "Please enter the Rational2\n";
			Numbers::Rational r2 = GetRational();
			cout << "  Rational1 (" << r1 << "), Rational2 (" << r2 << ")\n";
			cout << "  Rational1 - Rational2 == " << r1 - r2 << endl;
			break;
		}
		case MULTIPLICATION: {
			cout << "Please enter the Rational1\n";
			Numbers::Rational r1 = GetRational();
			cout << "Please enter the Rational2\n";
			Numbers::Rational r2 = GetRational();
			cout << "  Rational1 (" << r1 << "), Rational2 (" << r2 << ")\n";
			cout << "  Rational1 - Rational2 == " << r1 * r2 << endl;
			break;
		}
		case DIVISION: {
			cout << "Please enter the Rational1\n";
			Numbers::Rational r1 = GetRational();
			cout << "Please enter the Rational2\n";
			Numbers::Rational r2 = GetRational();
			cout << "  Rational1 (" << r1 << "), Rational2 (" << r2 << ")\n";
			cout << "  Rational1 - Rational2 == " << r1 / r2 << endl;
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
	catch (Numbers::Rational::Invalid& e) {
		cerr << "Rational is invalid\n";
	}
	catch (...) {
		cerr << "exception\n";
		return 1;
	}
}

namespace Numbers {
	Rational::Rational(long long int numerator, long long int denominator)
		: numerator{ numerator }, denominator{ denominator }
	{
		if (denominator == 0) throw Rational::Invalid{};
	}

	bool operator==(const Rational& a, const Rational& b)
	{
		return (a.GetNumerator() == b.GetNumerator() && a.GetDenominator() == b.GetDenominator());
	}

	Rational operator+(const Rational& a, const Rational& b)
	{
		return Rational(a.GetNumerator() * b.GetDenominator() + a.GetDenominator() * b.GetNumerator(),
			a.GetDenominator() * b.GetDenominator());
	}

	Rational operator-(const Rational& a, const Rational& b)
	{
		return Rational(a.GetNumerator() * b.GetDenominator() - a.GetDenominator() * b.GetNumerator(),
			a.GetDenominator() * b.GetDenominator());
	}

	Rational operator*(const Rational& a, const Rational& b)
	{
		return Rational(a.GetNumerator() * b.GetNumerator(), a.GetDenominator() * b.GetDenominator());
	}

	Rational operator/(const Rational& a, const Rational& b)
	{
		return Rational(a.GetNumerator() * b.GetDenominator(), a.GetDenominator() * b.GetNumerator());
	}

	ostream& operator<<(ostream& os, const Rational& r)
	{
		os << "NUM:" << r.GetNumerator() << ", DENOM:" << r.GetDenominator()
			<< ", DOUBLE:" << r.GetDouble();
		return os;
	}
} //Numbers

Numbers::Rational GetRational()
{
	long long int n;
	cout << "Please enter a numerator: ";
	if (!(cin >> n)) { ClearInput(cin); error("Incorrect input"); }
	long long int d;
	cout << "Please enter a denominator: ";
	if (!(cin >> d)) { ClearInput(cin); error("Incorrect input"); }
	return Numbers::Rational(n, d);
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
