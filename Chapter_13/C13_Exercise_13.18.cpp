/* Exercise 13.18 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.18.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Poly" };

	Poly polygon{ Point{300, 300}, Point{400, 350}, Point{500, 800}, Point{300, 500}, Point{250, 400} };
	sw.attach(polygon);
	Poly polygon2{ Point{600, 300}, Point{650, 350}, Point{700, 300}, Point{750, 500}, Point{650, 500},
		Point{550, 400} };
	sw.attach(polygon2);

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

Poly::Poly(initializer_list<Point> list)
{
	for (auto p : list) {
		PolygonPPP2::add(p);
	}
}

void Poly::draw_lines() const
{
	PolygonPPP2::draw_lines();
}
