/* Exercise 26.3 */

#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<vector>
#include"C26_Exercise_26.3.h"

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
		"  (1) BinarySearch()\n"
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
				cout << endl << "int:" << endl;
				cout << "bool BinarySearch(RandomAccessIterator, RandomAccessIterator, const T&)" << endl;
				string fileInput{ "C26_Exercise_26.3_test_int.txt" };
				ifstream ifs{ fileInput };
				if (!ifs) error("Error. Can't open input file: ", fileInput);
				cout << sp_2 << "File: " << fileInput << endl;
				TestAll<int>(ifs, cout, TestType::COMMON);

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
					ss << "{ 8." << i << " " << x << " { ";
					for (int j = 0; j < v.size(); ++j) {
						ss << v[j] << " ";
					}
					ss << "} 1 }" << endl;
				}
				cout << sp_2 << "Sets generated using random numbers" << endl;
				TestAll<int>(ss, cout, TestType::COMMON);
			}

			{
				cout << endl << "int:" << endl;
				cout << "bool BinarySearch(RandomAccessIterator, RandomAccessIterator, const T&, Compare)" << endl;
				string fileInput{ "C26_Exercise_26.3_test_int.txt" };
				ifstream ifs{ fileInput };
				if (!ifs) error("Error. Can't open input file: ", fileInput);
				cout << sp_2 << "File: " << fileInput << endl;
				TestAll<int>(ifs, cout, TestType::COMPARELOWER);

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
					ss << "{ 8." << i << " " << x << " { ";
					for (int j = 0; j < v.size(); ++j) {
						ss << v[j] << " ";
					}
					ss << "} 1 }" << endl;
				}
				cout << sp_2 << "Sets generated using random numbers" << endl;
				TestAll<int>(ss, cout, TestType::COMPARELOWER);
			}

			{
				cout << endl << "int:" << endl;
				cout << "bool BinarySearch(RandomAccessIterator, RandomAccessIterator, const T&, Compare)" << endl;
				string fileInput{ "C26_Exercise_26.3_test_int_g.txt" };
				ifstream ifs{ fileInput };
				if (!ifs) error("Error. Can't open input file: ", fileInput);
				cout << sp_2 << "File: " << fileInput << endl;
				TestAll<int>(ifs, cout, TestType::COMPAREGREATER);

				// Test 8 "Sets generated using random numbers"
				constexpr int numberOfElements = 50;
				constexpr int spread = 20;
				stringstream ss;
				for (int i = 1; i <= 20; ++i) {
					vector<int> v;
					v.resize(numberOfElements);
					int sum = 0;
					for (int j = 0; j < v.size(); ++j) {
						sum += randint(spread);
						v[v.size() - j - 1] = sum;
					}
					int x = v[randint(v.size())];
					ss << "{ 8." << i << " " << x << " { ";
					for (int j = 0; j < v.size(); ++j) {
						ss << v[j] << " ";
					}
					ss << "} 1 }" << endl;
				}
				cout << sp_2 << "Sets generated using random numbers" << endl;
				TestAll<int>(ss, cout, TestType::COMPAREGREATER);
			}



			{
				cout << endl << "double:" << endl;
				cout << "bool BinarySearch(RandomAccessIterator, RandomAccessIterator, const T&)" << endl;
				string fileInput{ "C26_Exercise_26.3_test_double.txt" };
				ifstream ifs{ fileInput };
				if (!ifs) error("Error. Can't open input file: ", fileInput);
				cout << sp_2 << "File: " << fileInput << endl;
				TestAll<double>(ifs, cout, TestType::COMMON);

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
					ss << "{ 8." << i << " " << x << " { ";
					for (int j = 0; j < v.size(); ++j) {
						ss << v[j] << " ";
					}
					ss << "} 1 }" << endl;
				}
				cout << sp_2 << "Sets generated using random numbers" << endl;
				TestAll<double>(ss, cout, TestType::COMMON);
			}

			{
				cout << endl << "double:" << endl;
				cout << "bool BinarySearch(RandomAccessIterator, RandomAccessIterator, const T&, Compare)" << endl;
				string fileInput{ "C26_Exercise_26.3_test_double.txt" };
				ifstream ifs{ fileInput };
				if (!ifs) error("Error. Can't open input file: ", fileInput);
				cout << sp_2 << "File: " << fileInput << endl;
				TestAll<double>(ifs, cout, TestType::COMPARELOWER);

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
					ss << "{ 8." << i << " " << x << " { ";
					for (int j = 0; j < v.size(); ++j) {
						ss << v[j] << " ";
					}
					ss << "} 1 }" << endl;
				}
				cout << sp_2 << "Sets generated using random numbers" << endl;
				TestAll<double>(ss, cout, TestType::COMPARELOWER);
			}

			{
				cout << endl << "double:" << endl;
				cout << "bool BinarySearch(RandomAccessIterator, RandomAccessIterator, const T&, Compare)" << endl;
				string fileInput{ "C26_Exercise_26.3_test_double_g.txt" };
				ifstream ifs{ fileInput };
				if (!ifs) error("Error. Can't open input file: ", fileInput);
				cout << sp_2 << "File: " << fileInput << endl;
				TestAll<double>(ifs, cout, TestType::COMPAREGREATER);

				// Test 8 "Sets generated using random numbers"
				constexpr int numberOfElements = 50;
				constexpr int spread = 20;
				stringstream ss;
				for (int i = 1; i <= 20; ++i) {
					vector<double> v;
					v.resize(numberOfElements);
					double sum = 0;
					for (int j = 0; j < v.size(); ++j) {
						sum += double(randint(spread)) + double(randint(1, 99)) / 100;
						v[v.size() - j - 1] = sum;
					}
					double x = v[randint(v.size())];
					ss << "{ 8." << i << " " << x << " { ";
					for (int j = 0; j < v.size(); ++j) {
						ss << v[j] << " ";
					}
					ss << "} 1 }" << endl;
				}
				cout << sp_2 << "Sets generated using random numbers" << endl;
				TestAll<double>(ss, cout, TestType::COMPAREGREATER);
			}

			{
				cout << endl << "string:" << endl;
				cout << "bool BinarySearch(RandomAccessIterator, RandomAccessIterator, const T&)" << endl;
				string fileInput{ "C26_Exercise_26.3_test_string.txt" };
				ifstream ifs{ fileInput };
				if (!ifs) error("Error. Can't open input file: ", fileInput);
				cout << sp_2 << "File: " << fileInput << endl;
				TestAll<string>(ifs, cout, TestType::COMMON);

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
					ss << "{ 8." << i << " " << x << " { ";
					for (int j = 0; j < v.size(); ++j) {
						ss << v[j] << " ";
					}
					ss << "} 1 }" << endl;
				}
				cout << sp_2 << "Sets generated using random numbers" << endl;
				TestAll<string>(ss, cout, TestType::COMMON);
			}

			{
				cout << endl << "string:" << endl;
				cout << "bool BinarySearch(RandomAccessIterator, RandomAccessIterator, const T&, Compare)" << endl;
				string fileInput{ "C26_Exercise_26.3_test_string.txt" };
				ifstream ifs{ fileInput };
				if (!ifs) error("Error. Can't open input file: ", fileInput);
				cout << sp_2 << "File: " << fileInput << endl;
				TestAll<string>(ifs, cout, TestType::COMPARELOWER);

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
					ss << "{ 8." << i << " " << x << " { ";
					for (int j = 0; j < v.size(); ++j) {
						ss << v[j] << " ";
					}
					ss << "} 1 }" << endl;
				}
				cout << sp_2 << "Sets generated using random numbers" << endl;
				TestAll<string>(ss, cout, TestType::COMPARELOWER);
			}

			{
				cout << endl << "string:" << endl;
				cout << "bool BinarySearch(RandomAccessIterator, RandomAccessIterator, const T&, Compare)" << endl;
				string fileInput{ "C26_Exercise_26.3_test_string_g.txt" };
				ifstream ifs{ fileInput };
				if (!ifs) error("Error. Can't open input file: ", fileInput);
				cout << sp_2 << "File: " << fileInput << endl;
				TestAll<string>(ifs, cout, TestType::COMPAREGREATER);

				// Test 8 "Sets generated using random numbers"
				constexpr int numberOfLetters = 'z' - 'a' + 1;
				constexpr int maxLetters = 5;
				constexpr char firstLetter = 'a';
				stringstream ss;
				for (int i = 1; i <= 20; ++i) {
					vector<string> v;
					v.resize(numberOfLetters);
					string s;
					for (int j = 0; j < v.size(); ++j) {
						s = "";
						s += firstLetter + j;
						for (int k = 1; k < maxLetters; ++k) {
							s += char(randint('a', 'z' + 1));
						}
						v[v.size() - j - 1] = s;
					}
					string x = v[randint(v.size())];
					ss << "{ 8." << i << " " << x << " { ";
					for (int j = 0; j < v.size(); ++j) {
						ss << v[j] << " ";
					}
					ss << "} 1 }" << endl;
				}
				cout << sp_2 << "Sets generated using random numbers" << endl;
				TestAll<string>(ss, cout, TestType::COMPAREGREATER);
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
	/*
		format: { N TV { V1 V2 V3 ...  } B }
		N - <string> test number
		TV - <T> target value
		V1, V2, V3 ... - <T> sequence of values to search for
		B - <bool> ('0' or '1') the expected result of the search
	*/
	Test<T> test;
	// cb - curly brace
	constexpr char cbLeft{ '{' };
	constexpr char cbRigth{ '}' };
	char ch1, ch2;
	is >> ch1 >> test.label >> test.val >> ch2;
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
	is >> test.res;
	if (!is) return is;
	char ch4;
	is >> ch4;
	if (!is) return is;
	if (ch4 != cbRigth) {
		is.setstate(ios::failbit);
		return is;
	}
	t = test;
	return is;
}

template<class T> int TestAll(istream& is, ostream& os, TestType type)
{
	int testCount = 0;
	int errorCount = 0;
	os << boolalpha;
	for (Test<T> t; is >> t; ) {
		switch (type) {
		case TestType::COMMON: {
			bool r = BinarySearch(t.seq.begin(), t.seq.end(), t.val);
			if (r != t.res) {
				os << sp_4 << "Failure: test { " << t.label << " }; BinarySearch(): sequence { ";
				for (const T& x : t.seq) {
					os << x << ' ';
				}
				os << "} " << t.seq.size() << " elements; Target value { " << t.val
					<< " } -> { " << t.res << " }" << endl;
				++errorCount;
			}
			++testCount;
			break;
		}
		case TestType::COMPARELOWER: {
			bool r = BinarySearch(t.seq.begin(), t.seq.end(), t.val, [](const T& x, const T& y) { return (x < y); });
			if (r != t.res) {
				os << sp_4 << "Failure: test { " << t.label << " }; BinarySearch(x < y): sequence { ";
				for (const T& x : t.seq) {
					os << x << ' ';
				}
				os << "} " << t.seq.size() << " elements; Target value { " << t.val
					<< " } -> { " << t.res << " }" << endl;
				++errorCount;
			}
			++testCount;
			break;
		}
		case TestType::COMPAREGREATER: {
			bool r = BinarySearch(t.seq.begin(), t.seq.end(), t.val, [](const T& x, const T& y) { return (x > y); });
			if (r != t.res) {
				os << sp_4 << "Failure: test { " << t.label << " }; BinarySearch(x > y): sequence { ";
				for (const T& x : t.seq) {
					os << x << ' ';
				}
				os << "} " << t.seq.size() << " elements; Target value { " << t.val
					<< " } -> { " << t.res << " }" << endl;
				++errorCount;
			}
			++testCount;
			break;
		}
		}
	}
	if (!is && !is.eof()) os << sp_6 << "Invalid test" << endl;
	os << noboolalpha;
	os << sp_8 << "Number of tests:  " << testCount << endl;
	os << sp_8 << "Number of errors: " << errorCount << endl;
	return errorCount;
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
