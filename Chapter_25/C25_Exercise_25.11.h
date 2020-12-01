/* Exercise 25.11 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

namespace Page {
	constexpr unsigned int CalculateMax(int numberOfBits)
	{
		if (numberOfBits <= 0) return 0;
		unsigned int max = 1;
		for (int i = 1; i < numberOfBits; ++i) {
			max <<= 1;
			max |= 1;
		}
		return max;
	}

	constexpr int PFNbits = 22;
	constexpr int CCAbits = 3;
	constexpr int boolBits = 1;

	constexpr unsigned int PFNmax = CalculateMax(PFNbits);
	constexpr unsigned int CCAmax = CalculateMax(CCAbits);

	constexpr int bitsInByte = 8;
	constexpr int firstBit = 0x1;

	class InvalidValue{};
	class InvalidType{};

	enum class PPNType {
		GLOBAL, VALID, DIRTY, NONREACHABLE, CCA, PFN = 10		// type and number the first bit
	};

	class PPNbitset {
		bitset<bitsInByte * sizeof(unsigned int)> v;
	public:
		template<class T> void Set(PPNType type, T value);
		template<class T> T Get(PPNType type) const;
	};

	ostream& operator<<(ostream& os, const PPNbitset& ppn);
	inline unsigned int GetFirstBitOf(unsigned int value) { return value & 0x1; }
	inline unsigned int SetFirstBitOf(unsigned int value) { return value | 0x1; }
}
