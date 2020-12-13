/* Exercise 26.4 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

/*
	Test case format:
	# (at the beginning of the line) - comment, skip to end of line
	{ L TV R T { V1 V2 V3 ... } D }
		L - <string> label, without space
		TV - <T> target value, valid value from the sequence
		R - <bool> the expected result of the search: '1' - found, '0' - not found
		T - <bool> type of ordered sequence: '1' - smallest-to-largest, '0' - largest-to-smallest
		V1, V2, V3 ... - <T> sequence of values to search for
		D - <string> description, read until it encounters a '}'
*/
template<class T> struct Test {
	string lab;								// label, mark or number
	string desc;							// description
	T val;									// valid value from the sequence
	vector<T> seq;							// element sequence
	bool res;								// result, is the value in the sequence, 1 (true) or 0 (false)
	bool typ;								// type of ordered sequence, 1 (smallest-to-largest) or 0 (largest-to-smallest)
};

template<class T> istream& operator>>(istream& is, Test<T>& t);

template<class T> int TestAll(istream& is, ostream& os, const string& description);
template<class T> void PrintFailTest(ostream& os, const Test<T>& t, const string& description);

template<class RandomAccessIterator, class T>
bool BinarySearch(RandomAccessIterator first, RandomAccessIterator last, const T& x);
template<class RandomAccessIterator, class T, class Compare>
bool BinarySearch(RandomAccessIterator first, RandomAccessIterator last, const T& x, Compare comp);
