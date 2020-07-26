/* Exercise 14.16 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C14_Exercise_14.16.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Controller" };

	TestController tc;
	Text* pt1 = tc.show(Point{ 50, 50 });
	sw.attach(*pt1);
	sw.wait_for_button();
	
	tc.on();
	tc.set_level(100);
	Text* pt2 = tc.show(Point{ 50, 70 });
	sw.attach(*pt2);
	sw.wait_for_button();
	
	tc.off();
	tc.set_level(10);
	Text* pt3 = tc.show(Point{ 50, 90 });
	sw.attach(*pt3);
	sw.wait_for_button();

	RectanglePPP2 rect{ Point{500, 200}, 300, 100 };
	sw.attach(rect);
	rect.set_color(Color::magenta);

	ShapeController sc{ rect };
	Text* pt11 = sc.show(Point{ 50, 200 });
	sw.attach(*pt11);
	sw.wait_for_button();

	sc.on();
	sc.set_level(155);
	Text* pt12 = sc.show(Point{ 50, 220 });
	sw.attach(*pt12);
	sw.wait_for_button();

	sc.set_level(255);
	Text* pt13 = sc.show(Point{ 50, 240 });
	sw.attach(*pt13);
	sw.wait_for_button();

	sc.on();
	sc.set_level(40);
	Text* pt14 = sc.show(Point{ 50, 260 });
	sw.attach(*pt14);
	sw.wait_for_button();

	sc.off();
	sc.set_level(200);
	Text* pt15 = sc.show(Point{ 50, 280 });
	sw.attach(*pt15);
	sw.wait_for_button();

	sc.off();
	sc.set_level(50);
	Text* pt16 = sc.show(Point{ 50, 300 });
	sw.attach(*pt16);
	sw.wait_for_button();

	sc.on();
	sc.set_level(220);
	Text* pt17 = sc.show(Point{ 50, 320 });
	sw.attach(*pt17);
	sw.wait_for_button();

	sc.set_level(120);
	Text* pt18 = sc.show(Point{ 50, 340 });
	sw.attach(*pt18);
	sw.wait_for_button();

	sc.on();
	sc.set_level(255);
	Text* pt19 = sc.show(Point{ 50, 360 });
	sw.attach(*pt19);
	sw.wait_for_button();


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

Text* TestController::show(Point p) const
{
	ostringstream oss;
	oss << "State: " << ((isOn) ? "ON" : "OFF") << ". Level: " << lvl;
	string s = oss.str();
	return new Text{ p, s };
}

ShapeController::ShapeController(Shape& shape)
	: sh{ shape }, col{ shape.color() }, isOn{ false }, lvl{ 0 } { }

ShapeController::ShapeController(Shape& shape, int level, bool isOn)
	: sh{ shape }, col{ shape.color() }, isOn{ isOn }
{
	if (level < 0 || level > 255) error("level must be in the range [0, 255]");
	lvl = level;
	if (isOn) {
		sh.set_color(Color(fl_color_cube(lvl * (FL_NUM_RED - 1) / 255,
			lvl * (FL_NUM_GREEN - 1) / 255, lvl * (FL_NUM_BLUE - 1) / 255)));
	}
}

void ShapeController::on()
{
	if (!isOn) {
		isOn = true;
		col = sh.color();
		sh.set_color(Color(fl_color_cube(lvl * (FL_NUM_RED - 1) / 255,
			lvl * (FL_NUM_GREEN - 1) / 255, lvl * (FL_NUM_BLUE - 1) / 255)));
	}
}

void ShapeController::off()
{
	if (isOn) {
		isOn = false;
		sh.set_color(col);
	}
}

void ShapeController::set_level(int level)
{
	if (level < 0 || level > 255) error("level must be in the range [0, 255]");
	lvl = level;
	if (isOn) {
		sh.set_color(Color(fl_color_cube(lvl * (FL_NUM_RED - 1) / 255,
			lvl * (FL_NUM_GREEN - 1) / 255, lvl * (FL_NUM_BLUE - 1) / 255)));
	}
}

Text* ShapeController::show(Point p) const
{
	ostringstream oss;
	oss << "State: " << ((isOn) ? "ON" : "OFF") << ". Level: " << lvl;
	string s = oss.str();
	return new Text{ p, s };
}
