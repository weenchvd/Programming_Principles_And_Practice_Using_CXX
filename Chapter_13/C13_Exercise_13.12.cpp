/* Exercise 13.12 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.12.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Mark" };

	Point center{ 500, 500 };
	Circle circle{ center, 200 };
	sw.attach(circle);
	constexpr int angleStepDeg = 7;
	for (int angleDeg = 0; angleDeg < 720; angleDeg += angleStepDeg) {
		Point p = GetPointOnCircle(circle.center(), circle.radius(), angleDeg);
		Mark m{ p, 'x' };
		sw.attach(m);
		sw.wait_for_button();
	}

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
