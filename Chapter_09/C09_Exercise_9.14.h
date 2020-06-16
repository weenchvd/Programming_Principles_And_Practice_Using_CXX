/* Exercise 9.14 */

using namespace std;

namespace Finance {
	class Money {
	public:
		class Invalid{};
		Money()
			: cents{ 0 } { }
		Money(long int cents)
			: cents{ cents } { }
		Money(long int dol, long int cent);
		// nonmodifying operations:
		long int Get() const { return cents; }
		long int GetDollars() const { return cents / 100; }
		long int GetCents() const { return ((cents < 0) ? -(cents % 100) : cents % 100); }
		// modifying operations:
		
	private:
		long int cents;
	};

	Money operator+(const Money& a, const Money& b);
	Money operator-(const Money& a, const Money& b);
	Money operator*(const Money& a, const double d);
	Money operator/(const Money& a, const double d);
	istream& operator>>(istream& is, Money& m);
	ostream& operator<<(ostream& os, const Money& m);
} // Numbers

Finance::Money GetMoney();
void ClearInput(istream& is);
