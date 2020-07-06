/* Exercise 12.8 */

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
	constexpr int tlWidth = 400;
	constexpr int tlHeight = 300;
	constexpr int radius = 100;
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Olympic rings" };
	Circle ring1{ Point{tlWidth, tlHeight}, radius };
	ring1.set_color(Color::blue);
	ring1.set_style(Line_style(Line_style::solid, 10));
	sw.attach(ring1);
	Circle ring2{ Point{tlWidth + 240, tlHeight}, radius };
	ring2.set_color(Color::black);
	ring2.set_style(Line_style(Line_style::solid, 10));
	sw.attach(ring2);
	Circle ring3{ Point{tlWidth + 480, tlHeight}, radius };
	ring3.set_color(Color::red);
	ring3.set_style(Line_style(Line_style::solid, 10));
	sw.attach(ring3);
	Circle ring4{ Point{tlWidth + 120, tlHeight + 100}, radius };
	ring4.set_color(Color::yellow);
	ring4.set_style(Line_style(Line_style::solid, 10));
	sw.attach(ring4);
	Circle ring5{ Point{tlWidth + 360, tlHeight + 100}, radius };
	ring5.set_color(Color::green);
	ring5.set_style(Line_style(Line_style::solid, 10));
	sw.attach(ring5);

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
