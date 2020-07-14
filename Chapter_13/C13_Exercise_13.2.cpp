/* Exercise 13.2 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.2.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Box" };

	Box box{ Point{200, 200}, 400, 300, 50 };
	sw.attach(box);
	Box box2{ Point{250, 250}, 300, 100, 20 };
	sw.attach(box2);
	Box box3{ Point{270, 270}, 200, 50, 10 };
	sw.attach(box3);
	Box box4{ Point{280, 280}, 1, 1, 1 };
	sw.attach(box4);

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

Box::Box(Point p, int width, int height, int radius)
	: w{ width }, h{ height }, r{ radius }
{
	add(p);
	if (radius < 5) r = 5;
	if (width < r * 2 + 20) w = r * 2 + 20;
	if (height < r * 2 + 10) h = r * 2 + 10;
}

void Box::draw_lines() const
{
	Point p = point(0);
	fl_arc(p.x, p.y, r + r, r + r, 90, 180);							// top left corner
	fl_arc(p.x + w - r * 2, p.y, r + r, r + r, 0, 90);					// top right corner
	fl_arc(p.x + w - r * 2, p.y + h - r * 2, r + r, r + r, 270, 360);	// bottom right corner
	fl_arc(p.x, p.y + h - r * 2, r + r, r + r, 180, 270);				// bottom left corner
	fl_line(p.x + r, p.y, p.x + w - r, p.y);							// top edge
	fl_line(p.x + w, p.y + r, p.x + w, p.y + h - r);					// right edge
	fl_line(p.x + r, p.y + h, p.x + w - r, p.y + h);					// bottom edge
	fl_line(p.x, p.y + r, p.x, p.y + h - r);							// left edge
}