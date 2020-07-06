/* Exercise 12.1 */

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
	Simple_window sw{ Point{80, 0}, 1280, 800, "Rectangles" };
	RectanglePPP2 rec{ Point{50, 50}, 400, 100 };
	rec.set_color(Color::blue);
	sw.attach(rec);
	PolygonPPP2 recP;
	recP.add(Point{ 50, 200 });
	recP.add(Point{ 250, 200 });
	recP.add(Point{ 250, 500 });
	recP.add(Point{ 50, 500 });
	recP.set_color(Color::red);
	sw.attach(recP);

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
