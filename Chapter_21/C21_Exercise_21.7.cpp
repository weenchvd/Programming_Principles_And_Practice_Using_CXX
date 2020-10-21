/* Exercise 21.7 */

#include<iostream>
#include<istream>
#include<sstream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include<iomanip>
#include"C21_Exercise_21.7.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5
	};
	const string actionList = "\tList of actions:\n"
		"  (1) BinarySearch,\n"
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
			vector<int> vi{ 3, 65, 2, 87, 2667, 87, 0, -36, 66, -265, -8, 1, -657, 0, 9 };
			sort(vi.begin(), vi.end());
			cout << sp_2 << "vi:" << endl << sp_4;
			for (int i = 0; i < vi.size(); ++i) cout << vi[i] << ' ';
			cout << endl;
			SearchAndPrint(vi, "vi", "int", 0);
			SearchAndPrint(vi, "vi", "int", -8);
			SearchAndPrint(vi, "vi", "int", -36);
			SearchAndPrint(vi, "vi", "int", -265);
			SearchAndPrint(vi, "vi", "int", -657);
			SearchAndPrint(vi, "vi", "int", 1);
			SearchAndPrint(vi, "vi", "int", 2);
			SearchAndPrint(vi, "vi", "int", 3);
			SearchAndPrint(vi, "vi", "int", 9);
			SearchAndPrint(vi, "vi", "int", 65);
			SearchAndPrint(vi, "vi", "int", 66);
			SearchAndPrint(vi, "vi", "int", 87);
			SearchAndPrint(vi, "vi", "int", 2667);
			SearchAndPrint(vi, "vi", "int", -1);
			SearchAndPrint(vi, "vi", "int", -15);
			SearchAndPrint(vi, "vi", "int", -37);
			SearchAndPrint(vi, "vi", "int", -300);
			SearchAndPrint(vi, "vi", "int", -656);
			SearchAndPrint(vi, "vi", "int", 4);
			SearchAndPrint(vi, "vi", "int", 8);
			SearchAndPrint(vi, "vi", "int", 17);
			SearchAndPrint(vi, "vi", "int", 67);
			SearchAndPrint(vi, "vi", "int", 90);
			SearchAndPrint(vi, "vi", "int", 456);
			SearchAndPrint(vi, "vi", "int", 77);
			SearchAndPrint(vi, "vi", "int", 989);
			SearchAndPrint(vi, "vi", "int", 3000);
			SearchAndPrint(vi, "vi", "int", 9999);
			vector<double> vd{ 3.1, 6.0, 0, -34.0, 1.0, -1.0, 2.55, 77.7, -4.4 };
			sort(vd.begin(), vd.end());
			cout << sp_2 << "vd:" << endl << sp_4;
			for (int i = 0; i < vd.size(); ++i) cout << vd[i] << ' ';
			cout << endl;
			SearchAndPrint(vd, "vd", "double", 3.1);
			SearchAndPrint(vd, "vd", "double", -34.0);
			SearchAndPrint(vd, "vd", "double", 77.7);
			cout << vsp_2;

			list<string> ls{ "asd", "gcc", "c++", "QWERTY", "C", "Random", "VS2019", "0xFF", "zzZZ" };
			ls.sort();
			cout << sp_2 << "ls:" << endl << sp_4;
			for (auto it = ls.begin(); it != ls.end(); ++it) cout << *it << ' ';
			cout << endl;
			SearchAndPrint(ls, "ls", "string", string{ "0xFF" });
			SearchAndPrint(ls, "ls", "string", string{ "C" });
			SearchAndPrint(ls, "ls", "string", string{ "QWERTY" });
			SearchAndPrint(ls, "ls", "string", string{ "Random" });
			SearchAndPrint(ls, "ls", "string", string{ "VS2019" });
			SearchAndPrint(ls, "ls", "string", string{ "asd" });
			SearchAndPrint(ls, "ls", "string", string{ "c++" });
			SearchAndPrint(ls, "ls", "string", string{ "gcc" });
			SearchAndPrint(ls, "ls", "string", string{ "zzZZ" });
			SearchAndPrint(ls, "ls", "string", string{ "0xFFF" });
			SearchAndPrint(ls, "ls", "string", string{ "c" });
			SearchAndPrint(ls, "ls", "string", string{ "qWERTY" });
			SearchAndPrint(ls, "ls", "string", string{ "RRandom" });
			SearchAndPrint(ls, "ls", "string", string{ "VS219" });
			SearchAndPrint(ls, "ls", "string", string{ "asdf" });
			SearchAndPrint(ls, "ls", "string", string{ "c--" });
			SearchAndPrint(ls, "ls", "string", string{ "ggc" });
			SearchAndPrint(ls, "ls", "string", string{ "ZZZZ" });
			cout << endl;
			list<char> lc{ 'a', 'c', 'F', 'X', 'x', 't', 'Y', '4', '-', ' ', '1', 'b', 'N' };
			lc.sort();
			cout << sp_2 << "lc:" << endl << sp_4;
			for (auto it = lc.begin(); it != lc.end(); ++it) cout << *it << ' ';
			cout << endl;
			SearchAndPrint(lc, "lc", "char", ' ');
			SearchAndPrint(lc, "lc", "char", 'Y');
			SearchAndPrint(lc, "lc", "char", '9');
			cout << endl;

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

template<class T> typename vector<T>::iterator BinarySearch(vector<T>& v, const T& val)
{
	if (v.size() == 0) return vector<T>::iterator{};
	vector<T>::iterator first = v.begin();
	vector<T>::iterator last = --v.end();
	while (first <= last) {
		vector<T>::iterator it = first + (last - first) / 2;
		if (val == *it) return it;
		if (val < *it) last = --it;
		else first = ++it;
	}
	return vector<T>::iterator{};
}

template<class T> typename list<T>::iterator BinarySearch(list<T>& l, const T& val)
{
	if (l.size() == 0) return list<T>::iterator{};
	list<T>::iterator first = l.begin();
	list<T>::iterator last = --l.end();
	while (true) {
		list<T>::iterator it = first;
		size_t size = 1;
		for (auto t = first; t != last; ++t) ++size;
		size = size / 2 + 1;
		while (--size > 0) ++it;
		if (val == *it) return it;
		if (first == last) break;
		if (val < *it) {
			if (it == l.begin()) break;
			last = --it;
		}
		else {
			if (it == l.end()) break;
			first = ++it;
		}
	}
	return list<T>::iterator{};
}

template<class T> void SearchAndPrint(vector<T>& v, const string& name, const string& type, const T& val)
{
	vector<T>::iterator itVec = BinarySearch(v, val);
	cout << sp_2 << "BinarySearch(" << name << ", " << type << "{ " << val << " }): ";
	if (itVec == vector<T>::iterator{}) cout << "not found";
	else cout << "position " << itVec - v.begin() + 1;
	cout << endl;
}

template<class T> void SearchAndPrint(list<T>& l, const string& name, const string& type, const T& val)
{
	list<T>::iterator itList = BinarySearch(l, val);
	cout << sp_2 << "BinarySearch(" << name << ", " << type << "{ " << val << " }): ";
	if (itList == list<T>::iterator{}) cout << "not found";
	else {
		cout << "position ";
		int pos = 0;
		for (auto it = l.begin(); it != itList; ++it) ++pos;
		cout << ++pos;
	}
	cout << endl;
}
