/* Exercise 26.5 */

#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<vector>
#include"C26_Exercise_26.5.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }
inline int randint(int max) { return rand() % max; }
inline int randint(int min, int max) { return randint(max - min) + min; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Test BinarySearch()\n"
		"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case CASE1: {
			cout << endl;
			{
				string fileInput{ "C26_Exercise_26.4_test_int.txt" };
				ifstream ifs{ fileInput };
				if (!ifs) error("Error. Can't open input file: ", fileInput);
				TestAll<int>(ifs, cout, fileInput);

				// Test 8 "Sets generated using random numbers"
				constexpr int numberOfElements = 50;
				constexpr int spread = 20;
				stringstream ss;
				for (int i = 1; i <= 20; ++i) {
					vector<int> v;
					int sum = 0;
					for (int j = 0; j < numberOfElements; ++j) {
						sum += randint(spread);
						v.push_back(sum);
					}
					int x = v[randint(v.size())];
					ss << "{ 8." << i << " " << x << " 1 1 { ";
					for (int j = 0; j < v.size(); ++j) {
						ss << v[j] << " ";
					}
					ss << "} random ints }" << endl;
				}
				TestAll<int>(ss, cout, "Sets generated using random numbers");
			}
			
			{
				string fileInput{ "C26_Exercise_26.4_test_double.txt" };
				ifstream ifs{ fileInput };
				if (!ifs) error("Error. Can't open input file: ", fileInput);
				TestAll<double>(ifs, cout, fileInput);

				// Test 8 "Sets generated using random numbers"
				constexpr int numberOfElements = 50;
				constexpr int spread = 20;
				stringstream ss;
				for (int i = 1; i <= 20; ++i) {
					vector<double> v;
					double sum = 0;
					for (int j = 0; j < numberOfElements; ++j) {
						sum += double(randint(spread)) + double(randint(1, 99)) / 100;
						v.push_back(sum);
					}
					double x = v[randint(v.size())];
					ss << "{ 8." << i << " " << x << " 1 1 { ";
					for (int j = 0; j < v.size(); ++j) {
						ss << v[j] << " ";
					}
					ss << "} random doubles }" << endl;
				}
				TestAll<double>(ss, cout, "Sets generated using random numbers");
			}
			
			{
				string fileInput{ "C26_Exercise_26.4_test_string.txt" };
				ifstream ifs{ fileInput };
				if (!ifs) error("Error. Can't open input file: ", fileInput);
				TestAll<string>(ifs, cout, fileInput);

				// Test 8 "Sets generated using random numbers"
				constexpr int numberOfLetters = 'z' - 'a' + 1;
				constexpr int maxLetters = 5;
				constexpr char firstLetter = 'a';
				stringstream ss;
				for (int i = 1; i <= 20; ++i) {
					vector<string> v;
					string s;
					for (int j = 0; j < numberOfLetters; ++j) {
						s = "";
						s += firstLetter + j;
						for (int k = 1; k < maxLetters; ++k) {
							s += char(randint('a', 'z' + 1));
						}
						v.push_back(s);
					}
					string x = v[randint(v.size())];
					ss << "{ 8." << i << " " << x << " 1 1 { ";
					for (int j = 0; j < v.size(); ++j) {
						ss << v[j] << " ";
					}
					ss << "} random strings }" << endl;
				}
				TestAll<string>(ss, cout, "Sets generated using random numbers");
			}
			
			cout << vsp_2;
			break;
		}
		case PRINTACTIONLIST:
			cout << actionList;
			break;
		case EXIT:
			cond = false;
			break;
		default:
			error("Error. Incorrect action number");
			break;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Error. Exception\n";
		return 1;
	}
	return 0;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}

template<class T> istream& operator>>(istream& is, Test<T>& t)
{
	Test<T> test;
	constexpr char cbLeft{ '{' };			// cb - curly brace
	constexpr char cbRigth{ '}' };			// cb - curly brace
	char ch1, ch2;
	while (true) {
		is >> ch1;
		if (!is) return is;
		if (ch1 == '#') {
			string s;
			getline(is, s);
		}
		else break;
	}
	is >> test.lab >> test.val >> test.res >> test.typ >> ch2;
	if (!is) return is;
	if (ch1 != cbLeft || ch2 != cbLeft) {
		is.setstate(ios::failbit);
		return is;
	}
	while (true) {
		char ch3;
		is >> ch3;
		if (!is) return is;
		if (ch3 == cbRigth) break;
		is.unget();
		T val;
		is >> val;
		if (!is) return is;
		test.seq.push_back(val);
	}
	while (true) {
		string s;
		is >> s;
		if (!is) return is;
		if (s.size() == 1 && s[0] == cbRigth) break;
		test.desc += ((test.desc.size() > 0) ? (" " + s) : s);
	}
	t = test;
	return is;
}

template<class T> int TestAll(istream& is, ostream& os, const string& description)
{
	os << sp_2 << description << endl;
	int testCount = 0;
	int errorCount = 0;
	for (Test<T> t; is >> t; ) {
		vector<T> seq2(t.seq.size());
		for (int i = 0; i < t.seq.size(); ++i) {
			seq2[seq2.size() - i - 1] = t.seq[i];
		}
		vector<T> copy1(t.seq.size());
		copy(t.seq.begin(), t.seq.end(), copy1.begin());
		vector<T> copy2(t.seq.size());
		copy(seq2.begin(), seq2.end(), copy2.begin());

		vector<T>* forward = nullptr;
		vector<T>* reverse = nullptr;
		vector<T>* forwardCopy = nullptr;
		vector<T>* reverseCopy = nullptr;
		if (t.typ) {
			forward = &t.seq;
			reverse = &seq2;
			forwardCopy = &copy1;
			reverseCopy = &copy2;
		}
		else {
			forward = &seq2;
			reverse = &t.seq;
			forwardCopy = &copy2;
			reverseCopy = &copy1;
		}

		bool r = BinarySearch(forward->begin(), forward->end(), t.val);
		if (r != t.res) {
			PrintFailTest(os, t, "BinarySearch()");
			++errorCount;
		}
		r = BinarySearch(forward->begin(), forward->end(), t.val,
			[](const T& x, const T& y) { return (x < y); });
		if (r != t.res) {
			PrintFailTest(os, t, "BinarySearch(Compare(x < y))");
			++errorCount;
		}
		r = BinarySearch(reverse->begin(), reverse->end(), t.val,
			[](const T& x, const T& y) { return (x > y); });
		if (r != t.res) {
			PrintFailTest(os, t, "BinarySearch(Compare(x > y))");
			++errorCount;
		}
		bool match = true;
		for (auto it = forward->begin(), itCopy = forwardCopy->begin(); it != forward->end(); ++it, ++itCopy) {
			if (*it != *itCopy) {
				++errorCount;
				match = false;
				break;
			}
		}
		for (auto it = reverse->begin(), itCopy = reverseCopy->begin(); it != reverse->end(); ++it, ++itCopy) {
			if (*it != *itCopy) {
				++errorCount;
				match = false;
				break;
			}
		}
		if (match == false) {
			os << "Test " << t.lab << " ";
			if (t.desc.size() > 0) os << "(" << t.desc << ") ";
			os << "modifies the sequence" << endl;
		}
		++testCount;
	}
	if (!is && !is.eof()) os << sp_6 << "Invalid test" << endl;
	os << sp_4 << errorCount << " error(s), " << testCount << " test(s)" << endl;
	return errorCount;
}

template<class T> void PrintFailTest(ostream& os, const Test<T>& t, const string& description)
{
	if (description.size() > 0) os << description;
	else os << "Test";
	os << " failed: " << t.lab << " ";
	if (t.desc.size() > 0) os << "(" << t.desc << ") ";
	os << "Sequence { ";
	for (const T& x : t.seq) os << x << ' ';
	os << "} Target value { " << t.val << " } Is the value in the sequence { "
		<< boolalpha << t.res << noboolalpha << " }" << endl;
}

template<class RandomAccessIterator, class T>
bool BinarySearch(RandomAccessIterator first, RandomAccessIterator last, const T& x)
{
	using Iter = RandomAccessIterator;
	if (first == last) return false;
	--last;
	while (first <= last) {
		Iter middle = (last - first) / 2 + first;
		if (*middle == x) return true;
		else if (*middle > x) last = middle - 1;
		else first = middle + 1;								// *middle < x
	}
	return false;
}

template<class RandomAccessIterator, class T, class Compare>
bool BinarySearch(RandomAccessIterator first, RandomAccessIterator last, const T& x, Compare comp)
{
	using Iter = RandomAccessIterator;
	if (first == last) return false;
	--last;
	while (first <= last) {
		Iter middle = (last - first) / 2 + first;
		if (comp(x, *middle)) last = middle - 1;
		else if (comp(*middle, x)) first = middle + 1;
		else return true;
	}
	return false;
}
