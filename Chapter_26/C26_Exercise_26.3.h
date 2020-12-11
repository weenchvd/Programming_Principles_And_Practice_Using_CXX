/* Exercise 26.3 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

template<class T> struct Test {
	string label;
	T val;
	vector<T> seq;
	bool res;
};

template<class T> istream& operator>>(istream& is, Test<T>& t);

enum class TestType {
	COMMON, COMPARELOWER, COMPAREGREATER
};

template<class T> int TestAll(istream& is, ostream& os, TestType type);

template<class RandomAccessIterator, class T>
bool BinarySearch(RandomAccessIterator first, RandomAccessIterator last, const T& x);


