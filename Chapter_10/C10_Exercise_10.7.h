/* Exercise 10.7 */

using namespace std;

class EndOfFile{};

namespace RomanNumerals {
	static constexpr int maxLettersBefore = 2;

	enum class Letter {
		I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000, MAX = 3999		// MAX - max number
	};

	static const vector<char> letters = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };

	static const string M[] = { "", "M", "MM", "MMM" };
	static const string C[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
	static const string X[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
	static const string I[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

	class Roman_int {
	public:
		class Invalid {};
		Roman_int()
			: value{ 0 } { }
		Roman_int(int v);
		int as_int() const { return value; }
		friend ostream& operator<<(ostream& os, const Roman_int& r);
		friend istream& operator>>(istream& is, Roman_int& r);
	private:
		int value;
	};
	
	string IntToRoman(const int integer);
	int RomanToInt(const string& roman);
}

void ClearInput(istream& is);
