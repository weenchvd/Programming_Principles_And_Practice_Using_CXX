/* Exercise 19.3 */

using namespace std;

template<class T, class U> struct Pair {
	Pair(T value1, U value2) : val1{ value1 }, val2{ value2 } {}
	T val1;
	U val2;
};

void ClearInput(istream& is);
