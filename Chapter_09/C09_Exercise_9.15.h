/* Exercise 9.15 */
/* Exercise 9.16 */

using namespace std;

namespace Finance {
	enum class Currency {
		USD, EUR, JPY, GBP, CHF, RUB
	};

	vector<string> curName = { "USD", "EUR", "JPY", "GBP", "CHF", "RUB" };

	class Money {
	public:
		class Invalid{};
		Money()
			: cents{ 0 }, cur{ Currency::USD } { }
		Money(long int cents, Currency currency)
			: cents{ cents }, cur{ currency } { }
		Money(long int dol, long int cent, Currency currency);
		// nonmodifying operations:
		long int Get() const { return cents; }
		long int GetIntegerPart() const { return cents / 100; }
		long int GetFractionalPart() const { return ((cents < 0) ? -(cents % 100) : cents % 100); }
		Currency GetCurrency() const { return cur; }
		// modifying operations:
		
	private:
		long int cents;
		Currency cur;
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
