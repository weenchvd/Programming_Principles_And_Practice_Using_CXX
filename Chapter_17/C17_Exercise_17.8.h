/* Exercise 17.8 */

using namespace std;

struct CharArray {
	string array;

	void PushBack(char ch) { array += ch; }
};

CharArray* ReadCharacters(CharArray* ca, char limiter);
void ClearInput(istream& is);
