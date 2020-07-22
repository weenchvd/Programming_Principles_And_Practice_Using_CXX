/* Exercise 14.7 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include<algorithm>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C14_Exercise_14.7.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Striped closed polyline" };

	Striped_closed_polyline scp1{ 4 };
	scp1.add(Point{ 90, 20 });
	scp1.add(Point{ 110, 30 });
	scp1.add(Point{ 70, 120 });
	scp1.add(Point{ 40,90 });
	scp1.add(Point{ 10, 110 });
	scp1.add(Point{ 0, 80 });
	scp1.add(Point{ 50, 30 });
	sw.attach(scp1);

	Striped_closed_polyline scp2{ 4 };
	scp2.add(Point{ 90 + 120, 20 });
	scp2.add(Point{ 110 + 120, 30 });
	scp2.add(Point{ 70 + 120, 120 });
	scp2.add(Point{ 40 + 120, 90 });
	scp2.add(Point{ 10 + 120, 110 });
	scp2.add(Point{ 0 + 120, 80 });
	scp2.add(Point{ 50 + 120, 30 });
	sw.attach(scp2);

	Striped_closed_polyline scp3{ 4 };
	scp3.add(Point{ 0, 190 });
	scp3.add(Point{ 10, 220 });
	scp3.add(Point{ 40, 200 });
	scp3.add(Point{ 70, 200 });
	scp3.add(Point{ 110, 140 });
	scp3.add(Point{ 90, 130 });
	scp3.add(Point{ 50, 145 });
	sw.attach(scp3);

	Striped_closed_polyline scp4{ 4 };
	scp4.add(Point{ 70 + 120, 200 });
	scp4.add(Point{ 40 + 120, 200 });
	scp4.add(Point{ 10 + 120, 220 });
	scp4.add(Point{ 0 + 120, 190 });
	scp4.add(Point{ 50 + 120, 145 });
	scp4.add(Point{ 90 + 120, 130 });
	scp4.add(Point{ 110 + 120, 140 });
	sw.attach(scp4);

	Striped_closed_polyline scp5{ 4 };
	scp5.add(Point{ 110, 240 });
	scp5.add(Point{ 90, 230 });
	scp5.add(Point{ 50, 245 });
	scp5.add(Point{ 0, 290 });
	scp5.add(Point{ 10, 320 });
	scp5.add(Point{ 40, 300 });
	scp5.add(Point{ 70, 300 });
	scp5.add(Point{ 100, 315 });
	sw.attach(scp5);

	Striped_closed_polyline scp6{ 4 };
	scp6.add(Point{ 70 + 120, 300 });
	scp6.add(Point{ 40 + 120, 300 });
	scp6.add(Point{ 10 + 120, 320 });
	scp6.add(Point{ 0 + 120, 290 });
	scp6.add(Point{ 50 + 120, 245 });
	scp6.add(Point{ 90 + 120, 230 });
	scp6.add(Point{ 110 + 120, 240 });
	scp6.add(Point{ 100 + 120, 315 });
	sw.attach(scp6);

	Striped_closed_polyline scp7{ 4 };
	scp7.add(Point{ 310, 20 });
	scp7.add(Point{ 280, 60 });
	scp7.add(Point{ 280, 120 });
	scp7.add(Point{ 300, 140 });
	scp7.add(Point{ 320, 100 });
	scp7.add(Point{ 330, 130 });
	scp7.add(Point{ 300, 190 });
	scp7.add(Point{ 300, 230 });
	scp7.add(Point{ 340, 230 });
	scp7.add(Point{ 320, 200 });
	scp7.add(Point{ 340, 180 });
	scp7.add(Point{ 360, 210 });
	scp7.add(Point{ 360, 230 });
	scp7.add(Point{ 390, 230 });
	scp7.add(Point{ 390, 210 });
	scp7.add(Point{ 400, 190 });
	scp7.add(Point{ 370, 130 });
	scp7.add(Point{ 410, 170 });
	scp7.add(Point{ 420, 130 });
	scp7.add(Point{ 440, 130 });
	scp7.add(Point{ 460, 170 });
	scp7.add(Point{ 460, 50 });
	scp7.add(Point{ 390, 80 });
	scp7.add(Point{ 360, 40 });
	scp7.add(Point{ 320, 40 });
	sw.attach(scp7);

	Striped_closed_polyline scp8{ 3 };
	scp8.add(Point{ 310 + 200, 20 });
	scp8.add(Point{ 280 + 200, 60 });
	scp8.add(Point{ 280 + 200, 120 });
	scp8.add(Point{ 300 + 200, 140 });
	scp8.add(Point{ 320 + 200, 100 });
	scp8.add(Point{ 330 + 200, 130 });
	scp8.add(Point{ 300 + 200, 190 });
	scp8.add(Point{ 300 + 200, 230 });
	scp8.add(Point{ 340 + 200, 230 });
	scp8.add(Point{ 320 + 200, 200 });
	scp8.add(Point{ 340 + 200, 180 });
	scp8.add(Point{ 360 + 200, 210 });
	scp8.add(Point{ 360 + 200, 230 });
	scp8.add(Point{ 390 + 200, 230 });
	scp8.add(Point{ 390 + 200, 210 });
	scp8.add(Point{ 400 + 200, 190 });
	scp8.add(Point{ 370 + 200, 130 });
	scp8.add(Point{ 410 + 200, 170 });
	scp8.add(Point{ 420 + 200, 130 });
	scp8.add(Point{ 440 + 200, 130 });
	scp8.add(Point{ 460 + 200, 170 });
	scp8.add(Point{ 460 + 200, 50 });
	scp8.add(Point{ 390 + 200, 80 });
	scp8.add(Point{ 360 + 200, 40 });
	scp8.add(Point{ 320 + 200, 40 });
	sw.attach(scp8);

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

void Striped_closed_polyline::draw_lines() const
{
	if (color().visibility()) {
		Closed_polyline::draw_lines();
		const int nPoints = number_of_points();
		int xLeftMost{ x_max() };
		int xRightMost{ 0 };
		int yTopMost{ y_max() };
		int yBottomMost{ 0 };
		for (int i = 0; i < nPoints; i++) {
			Point p = point(i);
			if (p.x < xLeftMost) xLeftMost = p.x;
			if (p.x > xRightMost) xRightMost = p.x;
			if (p.y < yTopMost) yTopMost = p.y;
			if (p.y > yBottomMost) yBottomMost = p.y;
		}
		for (int y = yTopMost + ls + 1; y < yBottomMost; y += ls + 1) {
			Point left{ xLeftMost, y };
			Point right{ xRightMost, y };
			vector<int> xIntersection;
			Point p;
			for (int i = 1; i < nPoints; i++) {
				if (line_segment_intersect(left, right, point(i - 1), point(i), p)) {
					if (p == point(i)) {
						if (point(i - 1).y <= point(i).y) {
							if (point(i).y <= point((i == nPoints - 1) ? 0 : i + 1).y) {
								xIntersection.push_back(p.x);
							}
						}
						else {
							if (point(i).y >= point((i == nPoints - 1) ? 0 : i + 1).y) {
								xIntersection.push_back(p.x);
							}
						}
					}
					else if (p != point(i - 1)) xIntersection.push_back(p.x);
				}
				else if (left.y == point(i).y && point(i - 1).y == point(i).y) xIntersection.push_back(point(i).x);
			}
			if (line_segment_intersect(left, right, point(nPoints - 1), point(0), p)) {
				if (p == point(0)) {
					if (point(nPoints - 1).y <= point(0).y) {
						if (point(0).y <= point(1).y) {
							xIntersection.push_back(p.x);
						}
					}
					else {
						if (point(0).y >= point(1).y) {
							xIntersection.push_back(p.x);
						}
					}
				}
				else if (p != point(nPoints - 1)) xIntersection.push_back(p.x);
			}
			else if (left.y == point(0).y && point(nPoints - 1).y == point(0).y) xIntersection.push_back(point(0).x);
			sort(xIntersection.begin(), xIntersection.end());
			for (int i = 1; i < xIntersection.size(); i += 2) {
				fl_line(xIntersection[i - 1], y, xIntersection[i], y);
			}
		}
	}
}

// does two lines (p1,p2) and (p3,p4) intersect?
// if se return the distance of the intersect point as distances from p1
inline pair<double, double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel)
{
	double x1 = p1.x;
	double x2 = p2.x;
	double x3 = p3.x;
	double x4 = p4.x;
	double y1 = p1.y;
	double y2 = p2.y;
	double y3 = p3.y;
	double y4 = p4.y;

	double denom = ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	if (denom == 0) {
		parallel = true;
		return pair<double, double>(0, 0);
	}
	parallel = false;
	return pair<double, double>(((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom,
		((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom);
}

//------------------------------------------------------------------------------

//intersection between two line segments
//Returns true if the two segments intersect,
//in which case intersection is set to the point of intersection
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection)
{
	bool parallel;
	pair<double, double> u = line_intersect(p1, p2, p3, p4, parallel);
	if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
	intersection.x = p1.x + u.first * (p2.x - p1.x);
	intersection.y = p1.y + u.first * (p2.y - p1.y);
	return true;
}
