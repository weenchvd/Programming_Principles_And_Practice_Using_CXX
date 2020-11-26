/* Exercise 25.1 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

struct Node {
	int id{ 0 };
	int num{ 0 };
	Node(int id, int number) : id{ id }, num{ number } {}
};

struct Message {
	int id{ 0 };
	int num{ 0 };
	int mark{ 0 };
	Message(int id, int number, int mark) : id{ id }, num{ number }, mark{ mark } {}
};


void Encrypt();
void Decrypt();
void encipher(
	const unsigned long* const v,
	unsigned long* const w,
	const unsigned long* const k);
void decipher(
	const unsigned long* const v,
	unsigned long* const w,
	const unsigned long* const k);