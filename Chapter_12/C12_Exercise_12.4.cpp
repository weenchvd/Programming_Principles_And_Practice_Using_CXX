/* Exercise 12.4 */

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
	Simple_window sw{ Point{80, 0}, 640, 480, "tic-tac-toe" };
	RectanglePPP2 square1{ Point{0, 0}, 100, 100 };
	square1.set_color(Color::dark_red);
	square1.set_style(Line_style(Line_style::solid, 5));
	RectanglePPP2 square2{ Point{0, 0}, 100, 100 };
	square2.set_color(Color::white);
	square2.set_style(Line_style(Line_style::solid, 5));
	RectanglePPP2 square3{ Point{0, 0}, 100, 100 };
	square3.set_color(Color::dark_red);
	square3.set_style(Line_style(Line_style::solid, 5));
	RectanglePPP2 square4{ Point{0, 0}, 100, 100 };
	square4.set_color(Color::white);
	square4.set_style(Line_style(Line_style::solid, 5));
	RectanglePPP2 square5{ Point{0, 0}, 100, 100 };
	square5.set_color(Color::dark_red);
	square5.set_style(Line_style(Line_style::solid, 5));
	RectanglePPP2 square6{ Point{0, 0}, 100, 100 };
	square6.set_color(Color::white);
	square6.set_style(Line_style(Line_style::solid, 5));
	RectanglePPP2 square7{ Point{0, 0}, 100, 100 };
	square7.set_color(Color::dark_red);
	square7.set_style(Line_style(Line_style::solid, 5));
	RectanglePPP2 square8{ Point{0, 0}, 100, 100 };
	square8.set_color(Color::white);
	square8.set_style(Line_style(Line_style::solid, 5));
	RectanglePPP2 square9{ Point{0, 0}, 100, 100 };
	square9.set_color(Color::dark_red);
	square9.set_style(Line_style(Line_style::solid, 5));
	square1.move(100, 100);
	square2.move(205, 100);
	square3.move(310, 100);
	square4.move(100, 205);
	square5.move(205, 205);
	square6.move(310, 205);
	square7.move(100, 310);
	square8.move(205, 310);
	square9.move(310, 310);
	sw.attach(square1);
	sw.attach(square2);
	sw.attach(square3);
	sw.attach(square4);
	sw.attach(square5);
	sw.attach(square6);
	sw.attach(square7);
	sw.attach(square8);
	sw.attach(square9);

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
