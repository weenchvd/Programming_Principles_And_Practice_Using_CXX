/* Exercise 14.10 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C14_Exercise_14.10.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Pseudo window" };

	Pseudo_window pw{ Point{100, 50}, 500, 400, "Real pseudo window" };
	sw.attach(pw);

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

Pseudo_window::Pseudo_window(Point topLeft, int width, int height, const string& string)
	: w{ width }, h{ height }, lab{ string }, fnt{ fl_font() }, fnt_sz{ 14 }
{
	add(topLeft);
	if (width < minWidth) w = minWidth;
	if (height < minHeight) h = minHeight;
}

void Pseudo_window::draw_lines() const
{
	const int ww = w - roundingRadius * 2;
	const int hh = h - roundingRadius * 2;
	Point topLeft = point(0);
	fl_line(topLeft.x + roundingRadius, topLeft.y, topLeft.x + roundingRadius + ww, topLeft.y);
	fl_line(topLeft.x + w, topLeft.y + roundingRadius, topLeft.x + w, topLeft.y + roundingRadius + hh);
	fl_line(topLeft.x + roundingRadius, topLeft.y + h, topLeft.x + roundingRadius + ww, topLeft.y + h);
	fl_line(topLeft.x, topLeft.y + roundingRadius, topLeft.x, topLeft.y + roundingRadius + hh);
	fl_line(topLeft.x, topLeft.y + headerHeight, topLeft.x + w, topLeft.y + headerHeight);
	fl_arc(topLeft.x, topLeft.y, roundingRadius * 2, roundingRadius * 2, 90, 180);
	fl_arc(topLeft.x + ww, topLeft.y, roundingRadius * 2, roundingRadius * 2, 0, 90);
	fl_arc(topLeft.x + ww, topLeft.y + hh, roundingRadius * 2, roundingRadius * 2, 270, 360);
	fl_arc(topLeft.x, topLeft.y + hh, roundingRadius * 2, roundingRadius * 2, 180, 270);
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(fnt.as_int(), fnt_sz);
	fl_draw(lab.c_str(), topLeft.x + roundingRadius, topLeft.y + headerHeight - 4);
	fl_font(ofnt, osz);
	Point topRight{ topLeft.x + w, topLeft.y };
	constexpr int buttonWidth = headerHeight;
	constexpr int buttonHeight = headerHeight;
	// CLOSE button
	fl_line(topRight.x - buttonWidth + buttonWidth / 4, topRight.y + buttonWidth / 4,
		topRight.x - buttonWidth + buttonWidth * 3 / 4, topRight.y + buttonWidth * 3 / 4);
	fl_line(topRight.x - buttonWidth + buttonWidth / 4, topRight.y + buttonWidth * 3 / 4,
		topRight.x - buttonWidth + buttonWidth * 3 / 4, topRight.y + buttonWidth / 4);
	// MAXIMIZE button
	fl_line(topRight.x - 2 * buttonWidth + buttonWidth / 4, topRight.y + buttonWidth / 4,
		topRight.x - 2 * buttonWidth + buttonWidth * 3 / 4, topRight.y + buttonWidth / 4);
	fl_line(topRight.x - 2 * buttonWidth + buttonWidth / 4, topRight.y + buttonWidth / 4,
		topRight.x - 2 * buttonWidth + buttonWidth / 4, topRight.y + buttonWidth * 3 / 4);
	fl_line(topRight.x - 2 * buttonWidth + buttonWidth / 4, topRight.y + buttonWidth * 3 / 4,
		topRight.x - 2 * buttonWidth + buttonWidth * 3 / 4, topRight.y + buttonWidth * 3 / 4);
	fl_line(topRight.x - 2 * buttonWidth + buttonWidth * 3 / 4, topRight.y + buttonWidth / 4,
		topRight.x - 2 * buttonWidth + buttonWidth * 3 / 4, topRight.y + buttonWidth * 3 / 4);
	// MINIMIZE button
	fl_line(topRight.x - 3 * buttonWidth + buttonWidth / 4, topRight.y + buttonWidth / 2,
		topRight.x - 3 * buttonWidth + buttonWidth * 3 / 4, topRight.y + buttonWidth / 2);
}
