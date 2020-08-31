/* Exercise 19.6 */

using namespace std;

template<class T> class Number {
public:
	Number() : v{ 0 } {}
	Number(T value) : v{ value } {}
	Number(const Number& n) : v{ n.v } {}
	Number operator=(const Number& n) { v = n.v; return *this; }
	Number(Number&& n) : v{ n.v } {}
	Number operator=(Number&& n) { v = n.v; return *this; }
	Number operator+(Number n) { return Number{ this->v + n.v }; }
	Number operator-(Number n) { return Number{ this->v - n.v }; }
	Number operator*(Number n) { return Number{ this->v * n.v }; }
	Number operator/(Number n) { return Number{ this->v / n.v }; }
	Number operator%(Number n) { return Number{ this->v % n.v }; }
	template<class T> friend istream& operator>>(istream& is, Number<T>& n);
	template<class T> friend ostream& operator<<(ostream& os, Number<T> n);
private:
	T v;
};

void ClearInput(istream& is);
