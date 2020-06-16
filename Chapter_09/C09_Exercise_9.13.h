/* Exercise 9.13 */

using namespace std;

namespace Numbers {
	class Rational {
	public:
		class Invalid{};
		Rational()
			: numerator{ 0 }, denominator{ 1 } { }
		Rational(long long int numerator, long long int denominator);
		// nonmodifying operations:
		double GetDouble() const { return double(numerator) / denominator; }
		long long int GetNumerator() const { return numerator; }
		long long int GetDenominator() const { return denominator; }
		// modifying operations:
		
	private:
		long long int numerator;
		long long int denominator;
	};

	bool operator==(const Rational& a, const Rational& b);
	Rational operator+(const Rational& a, const Rational& b);
	Rational operator-(const Rational& a, const Rational& b);
	Rational operator*(const Rational& a, const Rational& b);
	Rational operator/(const Rational& a, const Rational& b);
	ostream& operator<<(ostream& os, const Rational& r);
} // Numbers

Numbers::Rational GetRational();
void ClearInput(istream& is);
