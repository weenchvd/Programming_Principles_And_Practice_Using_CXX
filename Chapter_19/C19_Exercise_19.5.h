/* Exercise 19.5 */

using namespace std;

class Int {
public:
	Int() : v{ 0 } {}
	Int(int value) : v{ value } {}
	Int(const Int& i) : v{ i.v } {}
	Int operator=(const Int& i) { v = i.v; return *this; }
	Int(Int&& i) : v{ i.v } {}
	Int operator=(Int&& i) { v = i.v; return *this; }
	Int operator+(Int i) { return Int{ this->v + i.v }; }
	Int operator-(Int i) { return Int{ this->v - i.v }; }
	Int operator*(Int i) { return Int{ this->v * i.v }; }
	Int operator/(Int i) { return Int{ this->v / i.v }; }
	friend istream& operator>>(istream& is, Int& i);
	friend ostream& operator<<(ostream& os, Int i);
private:
	int v;
};


void ClearInput(istream& is);
