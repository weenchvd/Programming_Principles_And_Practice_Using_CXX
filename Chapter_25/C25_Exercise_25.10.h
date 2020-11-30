/* Exercise 25.10 */

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

	class InvalidValue{};

	struct PPN {								// R6000 Physical Page Number
		unsigned int PFN : PFNbits;				// Page Frame Number
		int : 3;								// unused
		unsigned int CCA : CCAbits;				// Cache Coherency Algorithm
		bool nonreachable : boolBits;
		bool dirty : boolBits;
		bool valid : boolBits;
		bool global : boolBits;
		PPN(unsigned int PFN, unsigned CCA, bool nonreachable, bool dirty, bool valid, bool global);
		void SetPFN(unsigned int PFN);
		void SetCCA(unsigned int CCA);
	};

	ostream& operator<<(ostream& os, const PPN& ppn);

	struct PPNint {
		unsigned int v;
		PPNint() : v{ 0 } {}
	};

	void SetPFN(PPNint& ppn, unsigned int PFN);
	void SetCCA(PPNint& ppn, unsigned int CCA);
	void SetNonreachable(PPNint& ppn, bool nonreachable);
	void SetDirty(PPNint& ppn, bool dirty);
	void SetValid(PPNint& ppn, bool valid);
	void SetGlobal(PPNint& ppn, bool global);

	ostream& operator<<(ostream& os, const PPNint& ppn);
}
