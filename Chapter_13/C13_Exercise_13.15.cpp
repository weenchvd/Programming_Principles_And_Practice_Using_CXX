/* Exercise 13.15 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.15.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Tile" };

	constexpr int legShort = 50;
	constexpr int legLong = 120;
	constexpr int xShift = legShort;
	constexpr int yShift = legLong;
	Point topLeft{ 0, 0 };
	Vector_ref<RightTriangle> tile;
	for (int y = topLeft.y; y <= y_max(); y += yShift) {
		for (int x = topLeft.x; x <= x_max(); x += xShift) {
			tile.push_back(new RightTriangle{ Point {x,y}, legLong, legShort, -90 });
			tile[tile.size() - 1].move(legShort, 0);
			tile[tile.size() - 1].set_color(Color::black);
			sw.attach(tile[tile.size() - 1]);
			tile.push_back(new RightTriangle{ Point {x,y}, legLong, legShort, 90 });
			tile[tile.size() - 1].move(0, legLong);
			tile[tile.size() - 1].set_color(Color::black);
			sw.attach(tile[tile.size() - 1]);
		}
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
