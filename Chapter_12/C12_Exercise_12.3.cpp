/* Exercise 12.3 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;

int main()
try {
	Simple_window sw{ Point{100, 0}, 640, 480, "Initials" };
	Open_polyline firstName;
	firstName.add(Point{ 0, 0 });
	firstName.add(Point{ 50, 150 });
	firstName.add(Point{ 100, 0 });
	firstName.set_color(Color::dark_blue);
	firstName.set_style(Line_style(Line_style::solid, 5));
	firstName.move(200, 170);
	sw.attach(firstName);
	Closed_polyline lastName;
	lastName.add(Point{ 0, 0 });
	lastName.add(Point{ 80, 0 });
	lastName.add(Point{ 100, 20 });
	lastName.add(Point{ 100, 130 });
	lastName.add(Point{ 80, 150 });
	lastName.add(Point{ 0, 150 });
	lastName.set_color(Color::dark_green);
	lastName.set_style(Line_style(Line_style::solid, 5));
	lastName.move(320, 170);
	sw.attach(lastName);

	sw.wait_for_button();
	return 0;
}
catch (runtime_error& e) {
	cerr << e.what() << endl;
}
catch (...) {
	cerr << "Error. Exception\n";
	return 1;
}
