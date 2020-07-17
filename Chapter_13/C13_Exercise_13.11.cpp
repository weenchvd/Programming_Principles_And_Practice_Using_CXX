/* Exercise 13.11 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.11.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Ellipse" };

	Point center{ 500, 500 };
	EllipsePPP2 el{ center, 150, 100 };
	sw.attach(el);
	Axis xAxis{ Axis::Orientation::x, Point{center.x - 200, center.y}, 400, 0, "x" };
	sw.attach(xAxis);
	Axis yAxis{ Axis::Orientation::y, Point{center.x, center.y + 150}, 300, 0, "y" };
	sw.attach(yAxis);
	Point pFocus1 = el.focus1();
	Mark mFocus1{ pFocus1, 'x' };
	sw.attach(mFocus1);
	Point pFocus2 = el.focus2();
	Mark mFocus2{ pFocus2, 'x' };
	sw.attach(mFocus2);
	Point pAngleDeg = GetPointOnEllipse(el.center(), el.major(), el.minor(), 310);
	Mark mAngleDeg{ pAngleDeg, 'x' };
	sw.attach(mAngleDeg);
	Line line1{ pFocus1, pAngleDeg };
	sw.attach(line1);
	Line line2{ pFocus2, pAngleDeg };
	sw.attach(line2);

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
