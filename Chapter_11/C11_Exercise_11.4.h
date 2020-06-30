/* Exercise 11.4 */

using namespace std;

struct Integer {
	int decNum;
	char base;		// 'h' for hexadecimal, 'o' for octal, 'd' for decimal
	Integer()
		: decNum{ 0 }, base{'d'} { }
	Integer(int decimalNumber, char base)
		: decNum{ decimalNumber }, base{ base } { }
};

Integer GetInteger(const string& s, const char base);
void ClearInput(istream& is);
