﻿/* Exercise 19.7 */

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
	operator double() const { return double(v); }
	template<class T> friend istream& operator>>(istream& is, Number<T>& n);
	template<class T> friend ostream& operator<<(ostream& os, Number<T> n);
private:
	T v;
};

template<class T, class U> long double Sum(const vector<T>& vt, const vector<U>& vu);
void ClearInput(istream& is);
