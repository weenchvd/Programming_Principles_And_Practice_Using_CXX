/* Exercise 24.2 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

struct triple1 {
	void operator()(int& elem) { elem *= 3; }
};

struct triple2 {
	int operator()(const int& elem) { return elem * 3; }
};

struct triple {
	int operator()(int& elem) { return elem *= 3; }
};

class multiply {
	int mul;
public:
	multiply(int multiplier) : mul{ multiplier } {}
	int operator()(int& elem) { return elem *= mul; }
};
