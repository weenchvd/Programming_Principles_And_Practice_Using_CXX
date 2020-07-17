/* Exercise 13.10 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.10.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Regular polygon" };

	constexpr int radius = 80;
	Point topLeft{ 100, 100 };
	Vector_ref<Regular_polygon> polygons;
	int i;
	for (i = 0; i < 5; i++) {
		polygons.push_back(new Regular_polygon{ Point{topLeft.x + 2 * i * topLeft.x, topLeft.y}, radius, i + 3 });
		sw.attach(polygons[polygons.size() - 1]);
	}
	topLeft.y += 200;
	for (; i < 10; i++) {
		polygons.push_back(new Regular_polygon{ Point{topLeft.x + 2 * (i - 5) * topLeft.x, topLeft.y}, radius, i + 3 });
		sw.attach(polygons[polygons.size() - 1]);
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

Regular_polygon::Regular_polygon(Point center, int radius, int numberOfSides)
	: c{ center }, r{ radius }, n{ numberOfSides }
{
	if (numberOfSides < 3) error("less than 3 sides in a Regular_polygon");
	const int rotationAngleDeg = 360 / n;
	int firstAngleDeg{ 0 };
	if (n == 4) firstAngleDeg = 45;
	else firstAngleDeg = 90;

	for (int i = firstAngleDeg; i < firstAngleDeg + 360; i += rotationAngleDeg) {
		add(GetPointOnCircle(c, r, i));
	}
}

void Regular_polygon::draw_lines() const
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
