/* Chapter 3.4 | Operators */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	cout << "Please enter a floating-point value: ";
	double n;
	cin >> n;
	cout << "n == " << n
		<< "\nn + 1 == " << n + 1
		<< "\nthree times n == " << n * 3
		<< "\ntwice n == " << n + n
		<< "\nn squared == " << n * n
		<< "\nhalf of n == " << n / 2
		<< "\nsquare root of n == " << sqrt(n)
		<< '\n';
	int x = 7;
	cout << "\nx == " << x << " is an integer"
		<< "\nx / 2 == " << x / 2
		<< "\nx % 2 == " << x % 2
		<< "\nx / 2 * 2 + x % 2 == " << x / 2 * 2 + x % 2
		<< "\nx -= 4, x == " << (x -= 4)
		<< "\nx += 6, x == " << (x += 6)
		<< "\nx *= 4, x == " << (x *= 4)
		<< "\nx /= 2, x == " << (x /= 2)
		<< "\nx %= 11, x == " << (x %= 11)
		<< "\nx++, x == " << x++
		<< "\nx--, x == " << x--
		<< "\n";
	string s1 = "C";
	string s2 = "++";
	string s3, s4, s5;
	s3 = s1 + s2;
	cout << "\ns1 == " << s1
		<< "\ns2 == " << s2
		<< "\ns3 = s1 + s2, s3 == " << s3 << "\n";
	s4 = s1;
	cout << "s4 = s1, s4 == " << s4 << "\n";
	s4 = s2;
	cout << "s4 = s2, s4 == " << s4 << "\n";
	s4 = s3;
	cout << "s4 = s3, s4 == " << s4 << "\n";
	s5 = s3;
	cout << "s5 = s3, s5 == " << s5 << "\n";
	s5 = s1;
	cout << "s5 = s1, s5 == " << s5 << "\n";
	s5 = s2;
	cout << "s5 = s2, s5 == " << s5 << "\n";
	s1 += s2;
	cout << "s1 += s2, s1 == " << s1 << "\n";
	s2 += s1;
	cout << "s2 += s1, s2 == " << s2 << "\n";
	return 0;
}
