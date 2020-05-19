/* Exercise 9.2 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>
#include"C09_Exercise_9.2.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }


int main()
{
	Name_pair pair;
	pair.read_names();
	pair.read_ages();
	pair.sort();
	pair.print();
	keep_window_open();
	return 0;
}

void Name_pair::read_names()
{
	cout << "Enter '-exit' to complete the input\n";
	while (cin) {
		cout << "Please enter the 'Name': ";
		string s;
		cin >> s;
		if (s == "-exit") break;
		name.push_back(s);
	}
	return;
}

void Name_pair::read_ages()
{
	if (age.size() > 0) return;
	for (int i = 0; i < name.size(); i++) {
		cout << "Please enter the 'Age' for the name '" << name[i] << "': ";
		double d;
		cin >> d;
		age.push_back(d);
	}
	return;
}

void Name_pair::sort()
{
	if (name.size() != age.size()) return;
	vector<string> copyName;
	vector<double> copyAge;
	for (int i = 0; i < name.size(); i++) {
		copyName.push_back(name[i]);
		copyAge.push_back(age[i]);
	}
	std::sort(name.begin(), name.end());
	for (int i = 0; i < name.size(); i++) {
		for (int j = 0; j < copyName.size(); j++) {
			if (name[i] == copyName[j]) {
				age[i] = copyAge[j];
				break;
			}
		}
	}
	return;
}

void Name_pair::print()
{
	if (name.size() != age.size()) return;
	cout << "Name Age:\n";
	for (int i = 0; i < name.size(); i++) {
		cout << "  " << name[i] << " " << age[i] << endl;
	}
	return;
}
