/* Exercise 11.14 */

using namespace std;

struct CharClassification {
	long long int space;
	long long int letter;
	long long int upper;
	long long int lower;
	long long int digit;
	long long int control;
	long long int punct;
	long long int print;
	CharClassification()
		: space{0}, letter{0}, upper{0}, lower{0}, digit{0}, control{0}, punct{0}, print{0} { }
};

void PrintCharacterClassification(const string& inputFileName);
void ClearInput(istream& is);
