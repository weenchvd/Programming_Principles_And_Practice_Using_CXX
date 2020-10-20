/* Exercise 21.4 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

//class GreaterThan {
//	int val;
//public:
//	GreaterThan(const int value) : val{ value } {}
//	bool operator()(const int x) const { return x > val; }
//};

template<class T> class GreaterThan {
	T val;
public:
	GreaterThan(const T& value) : val{ value } {}
	bool operator()(const T& x) const { return x > val; }
};

template<class T> class LowerThan {
	T val;
public:
	LowerThan(const T& value) : val{ value } {}
	bool operator()(const T& x) const { return x < val; }
};

template<class T> class NotEqual {
	T val;
public:
	NotEqual(const T& value) : val{ value } {}
	bool operator()(const T& x) const { return x != val; }
};

template<class InputIterator, class UnaryPredicate>
unsigned long long int CountIf(InputIterator first, InputIterator last, UnaryPredicate pred);
