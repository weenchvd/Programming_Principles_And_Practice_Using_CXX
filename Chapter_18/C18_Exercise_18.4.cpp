/* Exercise 18.4 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C18_Exercise_18.4.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

const string errMessageInputFile = "Error. Can't open input file: ";
const string errMessageOutputFile = "Error. Can't open output file: ";

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		BADSTRINGDUPLICATE, BADFIND, BADSTRINGCOMPARE, STRINGDUPLICATE, FIND, STRINGCOMPARE
	};
	const string actionList = "\tList of actions:\n"
	"  (1) strdup(bad c-string), (2) findx(bad c-string), (3) strcmp(bad c-string),"
	"  (4) strdup(), (5) findx(), (6) strcmp()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	const char* space2 = "  ";
	const char* space4 = "    ";
	int max = numeric_limits<int>::max();
	int min = numeric_limits<int>::min();
	int integers[] = { max - 4, max - 55 , min + 134, min + 15 };
	char* ci = reinterpret_cast<char*>(integers);
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case BADSTRINGDUPLICATE: {
			cout << "\nPlease enter the string in English (only ASCII): ";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cs = new char[s.size()];
			int i;
			for (i = 0; i < s.size(); i++) cs[i] = s[i]; // without "cs[i] = '\0';"
			char* di = str_dup(ci);
			char* ds = str_dup(cs);
			cout << space2 << "char pointer to array of integers:" << endl;
			cout << space4 << "Address " << static_cast<void*>(ci) << ": " << static_cast<char*>(ci) << endl;
			cout << space4 << "Address " << static_cast<void*>(di) << ": " << static_cast<char*>(di) << endl;
			cout << space2 << "char pointer to non-zero-terminated array:" << endl;
			cout << space4 << "Address " << static_cast<void*>(cs) << ": " << static_cast<char*>(cs) << endl;
			cout << space4 << "Address " << static_cast<void*>(ds) << ": " << static_cast<char*>(ds) << endl;
			delete[] cs;
			delete[] di;
			delete[] ds;
			break;
		}
		case BADFIND: {
			cout << "\nPlease enter the original string in English (only ASCII): ";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cs = new char[s.size()];
			int i;
			for (i = 0; i < s.size(); i++) cs[i] = s[i]; // without "cs[i] = '\0';"
			cout << "Please enter the search string in English (only ASCII): ";
			string x;
			if (!getline(cin, x)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cx = new char[x.size()];
			for (i = 0; i < x.size(); i++) cx[i] = x[i]; // without "cx[i] = '\0';"
			
			char* result1 = find_x(ci, cx);
			cout << endl << space2 << "char pointer to array of integers:" << endl;
			if (result1 == nullptr) cout << space4 << "The search string was not found" << endl;
			else {
				cout << space4 << "Address of the origin string: " << static_cast<void*>(cs) << endl
					<< space4 << "The origin string: " << cs << endl;
				cout << space4 << "Address of the first occurrence of the search string in the origin string: "
					<< static_cast<void*>(result1) << endl
					<< space4 << "The origin string from the place where the search string occurs: "
					<< result1 << endl;
			}

			char* result2 = find_x(cs, cx);
			cout << endl << space2 << "char pointer to non-zero-terminated array:" << endl;
			if (result2 == nullptr) cout << space4 << "The search string was not found" << endl;
			else {
				cout << space4 << "Address of the origin string: " << static_cast<void*>(cs) << endl
					<< space4 << "The origin string: " << cs << endl;
				cout << space4 << "Address of the first occurrence of the search string in the origin string: "
					<< static_cast<void*>(result2) << endl
					<< space4 << "The origin string from the place where the search string occurs: "
					<< result2 << endl;
			}
			delete[] cs;
			delete[] cx;
			break;
		}
		case BADSTRINGCOMPARE: {
			cout << "\nPlease enter the first string in English (only ASCII): ";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* s1 = new char[s.size()];
			int i;
			for (i = 0; i < s.size(); i++) s1[i] = s[i]; // without "s1[i] = '\0';"
			cout << "Please enter the second string in English (only ASCII): ";
			string x;
			if (!getline(cin, x)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* s2 = new char[x.size()];
			for (i = 0; i < x.size(); i++) s2[i] = x[i]; // without "s2[i] = '\0';"

			int result1 = str_cmp(ci, s2);
			cout << endl << space2 << "char pointer to array of integers:" << endl;
			if (result1 == 0) cout << space4 << "The strings are equal" << endl;
			else if (result1 < 0) cout << space4 << "The first string is lexicographically before the second string" << endl;
			else cout << space4 << "The first string is lexicographically after the second string" << endl;

			int result2 = str_cmp(s1, s2);
			cout << endl << space2 << "char pointer to non-zero-terminated array:" << endl;
			if (result2 == 0) cout << space4 << "The strings are equal" << endl;
			else if (result2 < 0) cout << space4 << "The first string is lexicographically before the second string" << endl;
			else cout << space4 << "The first string is lexicographically after the second string" << endl;
			delete[] s1;
			delete[] s2;
			break;
		}
		case STRINGDUPLICATE: {
			constexpr int n = 5;
			cout << "\nPlease enter the string in English (only ASCII): ";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cs = new char[s.size() + 1];
			int i;
			for (i = 0; i < s.size(); i++) cs[i] = s[i];
			cs[i] = '\0';
			char* ds1 = str_dup(cs);
			char* ds2 = str_dup(cs, n);
			cout << space2 << "Address " << static_cast<void*>(cs) << ": " << static_cast<char*>(cs) << endl;
			cout << space2 << "Address " << static_cast<void*>(ds1) << ": " << static_cast<char*>(ds1) << endl;
			cout << space2 << "Address " << static_cast<void*>(ds2) << ", n == " << n << ": " << static_cast<char*>(ds2) << endl;
			delete[] cs;
			delete[] ds1;
			delete[] ds2;
			break;
		}
		case FIND: {
			constexpr int n = 5;
			cout << "\nPlease enter the original string in English (only ASCII): ";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cs = new char[s.size() + 1];
			int i;
			for (i = 0; i < s.size(); i++) cs[i] = s[i];
			cs[i] = '\0';
			cout << "Please enter the search string in English (only ASCII): ";
			string x;
			if (!getline(cin, x)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* cx = new char[x.size() + 1];
			for (i = 0; i < x.size(); i++) cx[i] = x[i];
			cx[i] = '\0';

			char* result1 = find_x(cs, cx);
			if (result1 == nullptr) cout << endl << space2 << "The search string was not found" << endl;
			else {
				cout << endl << space2 << "Address of the origin string: " << static_cast<void*>(cs) << endl
					<< space2 << "The origin string: " << cs << endl;
				cout << space2 << "Address of the first occurrence of the search string in the origin string: "
					<< static_cast<void*>(result1) << endl
					<< space2 << "The origin string from the place where the search string occurs: "
					<< result1 << endl;
			}

			char* result2 = find_x(cs, cx, n);
			if (result2 == nullptr) cout << endl << space2 << "The search string was not found" << endl;
			else {
				cout << endl << space2 << "Address of the origin string: " << static_cast<void*>(cs) << endl
					<< space2 << "The origin string: " << cs << endl;
				cout << space2 << "Address of the first occurrence of the search string in the origin string: "
					<< static_cast<void*>(result2) << endl
					<< space2 << "The origin string from the place where the search string occurs: "
					<< result2 << endl;
			}
			delete[] cs;
			delete[] cx;
			break;
		}
		case STRINGCOMPARE: {
			constexpr int n = 5;
			cout << "\nPlease enter the first string in English (only ASCII): ";
			string s;
			if (!getline(cin, s)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* s1 = new char[s.size() + 1];
			int i;
			for (i = 0; i < s.size(); i++) s1[i] = s[i];
			s1[i] = '\0';
			cout << "Please enter the second string in English (only ASCII): ";
			string x;
			if (!getline(cin, x)) { ClearInput(cin); error("Error. Incorrect input"); }
			char* s2 = new char[x.size() + 1];
			for (i = 0; i < x.size(); i++) s2[i] = x[i];
			s2[i] = '\0';

			int result1 = str_cmp(s1, s2);
			cout << endl;
			if (result1 == 0) cout << space2 << "The strings are equal" << endl;
			else if (result1 < 0) cout << space2 << "The first string is lexicographically before the second string" << endl;
			else cout << space2 << "The first string is lexicographically after the second string" << endl;
			
			int result2 = str_cmp(s1, s2, n);
			cout << endl;
			if (result2 == 0) cout << space2 << "The strings are equal" << endl;
			else if (result2 < 0) cout << space2 << "The first string is lexicographically before the second string" << endl;
			else cout << space2 << "The first string is lexicographically after the second string" << endl;
			delete[] s1;
			delete[] s2;
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

char* str_dup(const char* s, int n)
{
	if (s == nullptr) return nullptr;
	char* ss;
	int size;
	for (ss = const_cast<char*>(s), size = 0; *ss != '\0' && size < n; ss++, size++);
	char* duplicate = new char[++size];
	ss = const_cast<char*>(s);
	char* dd;
	for (dd = duplicate, size = 0; *ss != '\0' && size < n; ss++, dd++, size++) *dd = *ss;
	*dd = '\0';
	return duplicate;
}

char* find_x(const char* s, const char* x, int n)
{
	if (s == nullptr || x == nullptr) return nullptr;
	char* ret = nullptr;
	char* ss = const_cast<char*>(s);
	char* xx = const_cast<char*>(x);
	int size = 0;
	for (; size < n  && *ss != '\0'; ss++, size++) {
		if (*ss == *xx) {
			ret = ss;
			char* tss = ss + 1;
			char* txx = xx + 1;
			int tsize = size + 1;
			for (; tsize < n && *tss == *txx && *tss != '\0'; tss++, txx++, tsize++);
			if (tsize == n) return ret;
			if (*tss == *txx || *txx == '\0') return ret;
			if (*tss == '\0') break;
		}
	}
	return nullptr;
}

int str_cmp(const char* s1, const char* s2, int n)
{
	char* ps1 = const_cast<char*>(s1);
	char* ps2 = const_cast<char*>(s2);
	int size = 0;
	while (size < n && *ps1 == *ps2 && *ps1 != '\0') {
		size++;
		ps1++;
		ps2++;
	}
	if (size == n) return 0;
	return *ps1 - *ps2;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
