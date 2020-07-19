/* Exercise 13.17 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.17.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Regular hexagon" };

	constexpr int numberOfAngles = 6;
	constexpr int hexagonRadius = 100;
	const Point topLeft{ 0, 0 };
	const int sideLength = 2 * round(hexagonRadius * sin(M_PI / numberOfAngles));
	const int yShift = hexagonRadius + sideLength / 2;
	int xShift;
	// r = R * cos(Pi / n), n is number of angles
	if (hexagonRadius % 2) xShift = round(hexagonRadius * cos(M_PI / numberOfAngles)) * 2;
	else xShift = round(hexagonRadius * cos(M_PI / numberOfAngles) * 2);

	bool shiftCenter{ false };
	Vector_ref<Regular_hexagon> tile;
	for (int y = topLeft.y; y <= y_max(); y += yShift) {
		int x = (shiftCenter) ? (topLeft.x + xShift / 2) : (topLeft.x);
		for (; x <= x_max(); x += xShift) {
			tile.push_back(new Regular_hexagon{ Point{x, y}, hexagonRadius });
			tile[tile.size() - 1].set_color(Color::black);
			tile[tile.size() - 1].set_fill_color(GetNextColor());
			sw.attach(tile[tile.size() - 1]);
		}
		shiftCenter = (shiftCenter) ? false : true;
	}

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

Regular_hexagon::Regular_hexagon(Point center, int radius)
	: c{ center }, r{ radius }
{
	constexpr int firstAngleDeg = 90;
	constexpr int rotationAngleDeg = 60;
	for (int i = firstAngleDeg; i < firstAngleDeg + 360; i += rotationAngleDeg) {
		add(GetPointOnCircle(c, r, i));
	}
}

void Regular_hexagon::draw_lines() const
{
	Closed_polyline::draw_lines();
}

Point GetPointOnCircle(Point center, int radius, int angleDegree)
{
	double angleRadian = angleDegree * M_PI / 180.0;
	int x = center.x + radius * cos(angleRadian);
	int y = center.y - radius * sin(angleRadian);
	return { x, y };
}

Color GetNextColor()
{
	static int col{ 0 };
	switch (col) {
	case Color::dark_blue:
		col = Color::dark_cyan;
		break;
	case Color::dark_cyan:
		col = Color::dark_green;
		break;
	case Color::dark_green:
		col = Color::dark_magenta;
		break;
	case Color::dark_magenta:
		col = Color::dark_red;
		break;
	case Color::dark_red:
		col = Color::dark_yellow;
		break;
	default:
		col = Color::dark_blue;
		break;
	}
	return col;
}
