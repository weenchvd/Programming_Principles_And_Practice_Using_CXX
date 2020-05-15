/* Exercise 8.7 */

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

void print(const vector<string>& s, const vector<double> d);


int main()
{
	vector<string> name;
	vector<double> age;
	cout << "Enter '-exit 0' as the 'Name Age' to exit\n";
	while (true) {
		string s;
		double d;
		cout << "Please enter the 'Name Age' pair: ";
		cin >> s >> d;
		if (s == "-exit") break;
		name.push_back(s);
		age.push_back(d);
	}
	vector<string> nameCopy;
	for (int i = 0; i < name.size(); i++) {
		nameCopy.push_back(name[i]);
	}
	sort(name.begin(), name.end());
	vector<double> ageSorted;
	for (int i = 0; i < name.size(); i++) {
		for (int j = 0; j < nameCopy.size(); j++) {
			if (name[i] == nameCopy[j]) {
				ageSorted.push_back(age[j]);
				break;
			}
		}
	}
	cout << "Name Age:\n";
	print(name, ageSorted);
	keep_window_open();
	return 0;
}

void print(const vector<string>& s, const vector<double> d)
{
	if (s.size() != d.size()) return;
	for (int i = 0; i < s.size(); i++) {
		cout << "  " << s[i] << " " << d[i] << endl;
	}
	return;
}
