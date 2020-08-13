/* Exercise 17.7 */

using namespace std;

struct CharArray {
	CharArray();
	char* array;
	int curSize;
	int maxSize;

	static const int increment = 1024;							// 1 KB

	void PushBack(char ch);
};

CharArray* ReadCharacters(CharArray* ca, char limiter);
void ClearInput(istream& is);
