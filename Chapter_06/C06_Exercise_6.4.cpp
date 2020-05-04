/* Exercise 6.4 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

class Name_value {
public:
	string name;
	int value;
};

int main()
{
	int i;
	bool proceed;
	Name_value temp;
	vector<Name_value> nv;
	vector<bool>duplication;
	proceed = true;
	while (proceed == true) {
		cout << "Please enter the 'Name Value' pair or enter the \"NoName 0\" pair to end the input: ";
		cin >> temp.name >> temp.value;
		if (temp.name == "NoName" && temp.value == 0) {
			proceed = false;
		}
		else {
			nv.push_back(temp);
			duplication.push_back(false);
			for (i = 0; i < nv.size() - 1; i++) {
				if (nv[i].name == temp.name) {
					duplication[duplication.size() - 1] = true;
				}
			}
		}	
	}
	proceed = true;
	for (i = 0; i < duplication.size(); i++) {
		if (duplication[i] == true) {
			cout << "  Error. Name \"" << nv[i].name << "\" entered more than 1 time\n";
			proceed = false;
		}
	}
	if (proceed == true) {
		for (i = 0; i < nv.size(); i++) {
			cout << "  " << nv[i].name << " " << nv[i].value << "\n";
		}
	}
	return 0;
}
