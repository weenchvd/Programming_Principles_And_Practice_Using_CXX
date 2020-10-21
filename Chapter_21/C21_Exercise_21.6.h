/* Exercise 21.6 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

struct Fruit {
	string name;
	int count;
	double unitPrice;

	Fruit(const string& name) : name{ name }, count{ 0 }, unitPrice{ 0.0 } {}
	Fruit(const string& name, int count, double unitPrice)
		: name{ name }, count{ count }, unitPrice{ unitPrice } {}
};

struct FruitComparison {
	bool operator() (const Fruit* a, const Fruit* b) const { return a->name < b->name; }
};

ostream& operator<<(ostream& os, const Fruit& f);
