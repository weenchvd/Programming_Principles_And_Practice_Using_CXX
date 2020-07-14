/* Exercise 13.1 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.1.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Arc" };

	Graph_lib::Arc arc{ Point{500, 500}, 400, 200, 30, 150 };
	arc.set_color(Color::black);
	sw.attach(arc);

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

void Arc::draw_lines() const
{
	if (color().visibility()) {
		fl_arc(point(0).x, point(0).y, w + w, h + h, a1, a2);
	}
}