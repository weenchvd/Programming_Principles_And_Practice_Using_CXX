/* Exercise 14.5 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C14_Exercise_14.5.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Striped rectangle" };

	Striped_rectangle sRect{ Point{100, 100}, 100, 200, 1 };
	sw.attach(sRect);
	Striped_rectangle sRect2{ Point{100, 400}, 600, 300, 4 };
	sw.attach(sRect2);

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

void Striped_rectangle::draw_lines() const
{
	if (color().visibility()) {
		RectanglePPP2::draw_lines();
		const int height = RectanglePPP2::height();
		const Point topLeft = RectanglePPP2::point(0);
		const int xLeft = topLeft.x;
		const int xRight = topLeft.x + RectanglePPP2::width() - 1;
		for (int y = topLeft.y + ls + 1; y < topLeft.y + height; y += ls + 1) {
			fl_line(xLeft, y, xRight, y);
		}
	}
}
