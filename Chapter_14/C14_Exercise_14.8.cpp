/* Exercise 14.8 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C14_Exercise_14.8.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Regular octagon" };

	const Point center{ 400, 500 };
	const int radius = 300;
	Regular_octagon oct{ center, radius };
	sw.attach(oct);

	if (oct.GetCenter() != center) error("Test 'center' failed");
	if (oct.GetRadius() != radius) error("Test 'radius' failed");
	const int numberOfPoints = 8;
	if (oct.number_of_points() != numberOfPoints) error("Test 'numberOfPoints' failed");
	const Point first = oct.point(0);
	oct.move(400, 50);
	if (oct.point(0) == first) error("Test 'move' failed");
	if (oct.GetCenter() == center) error("Test 'move' failed");
	
	const int color = int(Color::dark_magenta);
	const char visibility = char(Color::visible);
	oct.set_color(Color(Color::Color_type(color), Color::Transparency(visibility)));
	if (oct.color().as_int() != color) error("Test 'color' failed");
	if (oct.color().visibility() != visibility) error("Test 'visibility' failed");
	const int lineStyleWidth = 5;
	const int lineStyleType = int(Line_style::Line_style_type::dot);
	oct.set_style(Line_style(Line_style::Line_style_type::dot, lineStyleWidth));
	if (oct.style().style() != lineStyleType) error("Test 'lineStyleType' failed");
	if (oct.style().width() != lineStyleWidth) error("Test 'lineStyleWidth' failed");
	const int fillColor = int(Color::dark_yellow);
	oct.set_fill_color(Color(fillColor));
	if (oct.fill_color().as_int() != fillColor) error("Test 'fillColor' failed");


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

Regular_octagon::Regular_octagon(Point center, int radius)
	: c{ center }, r{ radius }
{
	constexpr int firstAngleDeg = 90;
	constexpr int rotationAngleDeg = 45;
	for (int i = firstAngleDeg; i < firstAngleDeg + 360; i += rotationAngleDeg) {
		add(GetPointOnCircle(c, r, i));
	}
}

void Regular_octagon::move(int dx, int dy)
{
	Shape::move(dx, dy);
	c.x += dx;
	c.y += dy;
}

Point GetPointOnCircle(Point center, int radius, int angleDegree)
{
	double angleRadian = angleDegree * M_PI / 180.0;
	int x = center.x + radius * cos(angleRadian);
	int y = center.y - radius * sin(angleRadian);
	return { x, y };
}
