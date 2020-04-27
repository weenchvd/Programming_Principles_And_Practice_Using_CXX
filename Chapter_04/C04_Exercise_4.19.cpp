/* Exercise 4.19 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	int i, tempValue;
	bool proceed;
	string tempName;
	vector<string> name;
	vector<int>value;
	vector<bool>duplication;
	proceed = true;
	while (proceed == true) {
		cout << "Please enter the 'Name Value' pair or enter the \"NoName 0\" pair to end the input: ";
		cin >> tempName >> tempValue;
		if (tempName == "NoName" && tempValue == 0) {
			proceed = false;
		}
		else {
			name.push_back(tempName);
			value.push_back(tempValue);
			duplication.push_back(false);
			for (i = 0; i < name.size() - 1; i++) {
				if (name[i] == tempName) {
					duplication[duplication.size() - 1] = true;
				}
			}
		}	
	}
	proceed = true;
	for (i = 0; i < duplication.size(); i++) {
		if (duplication[i] == true) {
			cout << "  Error. Name \"" << name[i] << "\" entered more than 1 time\n";
			proceed = false;
		}
	}
	if (proceed == true) {
		for (i = 0; i < name.size(); i++) {
			cout << "  " << name[i] << " " << value[i] << "\n";
		}
	}
	return 0;
}
