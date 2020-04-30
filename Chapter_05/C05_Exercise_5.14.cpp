/* Exercise 5.14 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

void error(string s) { throw runtime_error(s); }

int main()
{
	try {
		bool proceed;
		int reject, value, sum;
		string day;
		vector<int>monday;
		vector<int>tuesday;
		vector<int>wednesday;
		vector<int>thursday;
		vector<int>friday;
		vector<int>saturday;
		vector<int>sunday;
		cout << "Please enter 'day-of-the-week value' pairs (enter '| 0' to finish):\n";
		proceed = true;
		reject = 0;
		while (proceed == true) {
			cin >> day >> value;
			if (!cin) {
				error("Incorrect input\n");
			}
			if (day == "Monday" || day == "Mon" || day == "monday" || day == "MON") {
				monday.push_back(value);
			}
			else if (day == "Tuesday" || day == "Tue" || day == "tuesday" || day == "TUE") {
				tuesday.push_back(value);
			}
			else if (day == "Wednesday" || day == "Wed" || day == "wednesday" || day == "WED") {
				wednesday.push_back(value);
			}
			else if (day == "Thursday" || day == "Thu" || day == "thursday" || day == "THU") {
				thursday.push_back(value);
			}
			else if (day == "Friday" || day == "Fri" || day == "friday" || day == "FRI") {
				friday.push_back(value);
			}
			else if (day == "Saturday" || day == "Sat" || day == "saturday" || day == "SAT") {
				saturday.push_back(value);
			}
			else if (day == "Sunday" || day == "Sun" || day == "sunday" || day == "SUN") {
				sunday.push_back(value);
			}
			else if (day == "|") {
				proceed = false;
			}
			else {
				reject++;
			}
		}
		cout << "Monday: ";
		sum = 0;
		for (int x : monday) {
			cout << x << " ";
			sum += x;
		}
		cout << "\nSum of Monday: " << sum << "\n";
		cout << "Tuesday: ";
		sum = 0;
		for (int x : tuesday) {
			cout << x << " ";
			sum += x;
		}
		cout << "\nSum of Tuesday: " << sum << "\n";
		cout << "Wednesday: ";
		sum = 0;
		for (int x : wednesday) {
			cout << x << " ";
			sum += x;
		}
		cout << "\nSum of Wednesday: " << sum << "\n";
		cout << "Thursday: ";
		sum = 0;
		for (int x : thursday) {
			cout << x << " ";
			sum += x;
		}
		cout << "\nSum of Thursday: " << sum << "\n";
		cout << "Friday: ";
		sum = 0;
		for (int x : friday) {
			cout << x << " ";
			sum += x;
		}
		cout << "\nSum of Friday: " << sum << "\n";
		cout << "Saturday: ";
		sum = 0;
		for (int x : saturday) {
			cout << x << " ";
			sum += x;
		}
		cout << "\nSum of Saturday: " << sum << "\n";
		cout << "Sunday: ";
		sum = 0;
		for (int x : sunday) {
			cout << x << " ";
			sum += x;
		}
		cout << "\nSum of Sunday: " << sum << "\n";
		cout << "The number of rejected values: " << reject << "\n";
		return 0;
	}
	catch (runtime_error& e) {
		cerr << "\n\t| RUNTIME ERROR | " << e.what() << "\n";
		return -1;
	}
	catch (...) {
		cerr << "\n\t| UNKNOWN EXCEPTION |\n";
		return -2;
	}
}
