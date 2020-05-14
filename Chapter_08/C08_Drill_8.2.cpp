/* Drill 8.2 */

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

void swap_v(int a, int b);
void swap_r(int& a, int& b);
//void swap_cr(const int& a, const int& b);

int main()
{
	int x = 7;
	int y = 9;
	cout << "x == " << x << ", y == " << y << endl;
	swap_v(x, y);
	cout << "swap_v(x, y): x == " << x << ", y == " << y << endl;
	swap_r(x, y);
	cout << "swap_r(x, y): x == " << x << ", y == " << y << endl;
	swap_v(7, 9);
	cout << "swap_v(7, 9): x == " << x << ", y == " << y << endl;
	//swap_r(7, 9); //not compiled, literal arguments cannot be exchanged
	const int cx = 7;
	const int cy = 9;
	cout << "cx == " << cx << ", cy == " << cy << endl;
	swap_v(cx, cy);
	cout << "swap_v(cx, cy): cx == " << cx << ", cy == " << cy << endl;
	//swap_r(cx, cy); //not compiled, const arguments cannot be changed
	swap_v(7.7, 9.9);
	cout << "swap_v(7.7, 9.9): cx == " << cx << ", cy == " << cy << endl;
	//swap_r(7.7, 9.9); //not compiled, literal arguments cannot be exchanged
	double dx = 7.7;
	double dy = 9.9;
	cout << "dx == " << dx << ", dy == " << dy << endl;
	swap_v(dx, dy);
	cout << "swap_v(dx, dy): dx == " << dx << ", dy == " << dy << endl;
	//swap_r(dx, dy); //not compiled, invalid argument types
	swap_v(7.7, 9.9);
	cout << "swap_v(7.7, 9.9): dx == " << dx << ", dy == " << dy << endl;
	//swap_r(7.7, 9.9); //not compiled, literal arguments cannot be exchanged
	keep_window_open();
	return 0;
}

void swap_v(int a, int b)
{
	int temp;
	temp = a, a = b;
	b = temp;
	return;
}

void swap_r(int& a, int& b)
{
	int temp;
	temp = a, a = b;
	b = temp;
	return;
}

//not compiled, const arguments cannot be changed
/*void swap_cr(const int& a, const int& b)
{
	int temp;
	temp = a, a = b;
	b = temp;
	return;
}*/
