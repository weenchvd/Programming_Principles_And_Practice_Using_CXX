/* Drill 8.3 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

namespace X {
	int var;
	void print()
	{
		cout << var << endl;
		return;
	}
}

namespace Y {
	int var;
	void print()
	{
		cout << var << endl;
		return;
	}
}

namespace Z {
	int var;
	void print()
	{
		cout << var << endl;
		return;
	}
}


int main()
{
	X::var = 7;
	X::print(); // print X’s var
	using namespace Y;
	var = 9;
	print(); // print Y’s var
	{
		using Z::var;
		using Z::print;
		var = 11;
		print(); // print Z’s var
	}
	print(); // print Y’s var
	X::print(); // print X’s var
	keep_window_open();
	return 0;
}
