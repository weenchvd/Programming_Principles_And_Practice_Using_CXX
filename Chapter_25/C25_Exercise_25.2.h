/* Exercise 25.2 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

struct Conforming {
	const char hex;
	const char letter;
	Conforming(char hexNotation, char letter) : hex{ hexNotation }, letter{ letter } {}
};
