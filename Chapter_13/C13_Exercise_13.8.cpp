/* Exercise 13.8 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.8.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Regular hexagon" };

	Regular_hexagon hexagon{ Point{500,500}, 300 };
	sw.attach(hexagon);

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
