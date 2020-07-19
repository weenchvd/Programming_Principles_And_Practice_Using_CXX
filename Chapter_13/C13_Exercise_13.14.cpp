/* Exercise 13.14 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.14.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Right triangle" };

	constexpr int legShort = 50;
	constexpr int legLong = 120;
	Point center{ 500, 500 };
	RightTriangle rt1{ center, legShort, legLong, 180 };
	rt1.set_fill_color(Color::red);
	rt1.set_color(Color::black);
	rt1.move(0, -legLong);
	sw.attach(rt1);
	RightTriangle rt2{ center, legLong, legShort, -90 };
	rt2.set_fill_color(Color::dark_cyan);
	rt2.set_color(Color::black);
	rt2.move(0, -legLong);
	sw.attach(rt2);
	RightTriangle rt3{ center, legLong, legShort, 90 };
	rt3.set_fill_color(Color::dark_blue);
	rt3.set_color(Color::black);
	rt3.move(-legShort, 0);
	sw.attach(rt3);
	RightTriangle rt4{ center, legLong, legShort, 90 };
	rt4.set_fill_color(Color::dark_magenta);
	rt4.set_color(Color::black);
	sw.attach(rt4);
	RightTriangle rt5{ center, legLong, legShort, -90 };
	rt5.set_fill_color(Color::dark_green);
	rt5.set_color(Color::black);
	sw.attach(rt5);
	RightTriangle rt6{ center, legLong, legShort, 90 };
	rt6.set_fill_color(Color::dark_red);
	rt6.set_color(Color::black);
	rt6.move(0, legLong);
	sw.attach(rt6);
	RightTriangle rt7{ center, legLong, legShort, -90 };
	rt7.set_fill_color(Color::dark_yellow);
	rt7.set_color(Color::black);
	rt7.move(legShort, 0);
	sw.attach(rt7);
	RightTriangle rt8{ center, legShort, legLong };
	rt8.set_fill_color(Color::blue);
	rt8.set_color(Color::black);
	rt8.move(0, legLong);
	sw.attach(rt8);

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

Point GetPointOnCircle(Point center, int radius, int angleDegree)
{
	double angleRadian = angleDegree * M_PI / 180.0;
	int x = center.x + radius * cos(angleRadian);
	int y = center.y - radius * sin(angleRadian);
	return { x, y };
}

Point GetPointOnEllipse(Point center, int halfWidth, int halfHeight, int angleDegree)
{
	double anglePsiRadian = angleDegree * M_PI / 180.0;
	double anglePhiRadian = atan2(halfWidth * sin(anglePsiRadian), halfHeight * cos(anglePsiRadian));
	int x = center.x + halfWidth * cos(anglePhiRadian);
	int y = center.y - halfHeight * sin(anglePhiRadian);
	return { x, y };
}

RightTriangle::RightTriangle(Point point, int legRightLength, int legDownLength, int rotationAngleDeg)
	: p{ point }, lr{ legRightLength }, ld{ legDownLength }, a{ rotationAngleDeg }
{
	if (lr <= 0 || ld <= 0) error("The leg length of a right triangle must be greater than 0");
	Point p2{ p.x + lr, p.y };
	Point p3{ p.y, p.y + ld };
	if (a != 0) {
		p2 = GetPointOnCircle(p, p2.x - p.x, a);
		p3 = GetPointOnCircle(p, p3.y - p.y, a - 90);
	}
	add(p);
	add(p2);
	add(p3);
}

void RightTriangle::draw_lines() const
{
	Closed_polyline::draw_lines();
}
