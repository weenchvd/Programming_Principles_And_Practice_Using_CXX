/* Exercise 14.11 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C14_Exercise_14.11.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Binary tree" };

	Binary_tree bt{ Point{600, 50}, 8 };
	sw.attach(bt);

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

void Binary_tree::draw_lines() const
{
	if (lvl > 0) {
		Point p = point(0);
		fl_circle(p.x, p.y, radius);
		DrawChildren(p, 1);
	}
}

// Point par - center of the parent node, parLevel - current level of the parent
void Binary_tree::DrawChildren(Point par, const int parLevel) const
{
	const int dif = lvl - parLevel;						// difference between the max level and the parent level
	if (dif < 1) return;
	int xIndentation = dist / 2;
	for (int i = 1; i < dif; i++) {
		xIndentation *= 2;
	}
	Point leftCenter{ par.x - xIndentation, par.y + dist };
	Point rightCenter{ par.x + xIndentation, par.y + dist };
	fl_circle(leftCenter.x, leftCenter.y, radius);
	fl_circle(rightCenter.x, rightCenter.y, radius);
	Point leftTop = GetPointOnCircle(leftCenter, radius, 90);
	Point rightTop = GetPointOnCircle(rightCenter, radius, 90);
	Point parBottom = GetPointOnCircle(par, radius, 270);
	fl_line(leftTop.x, leftTop.y, parBottom.x, parBottom.y);
	fl_line(rightTop.x, rightTop.y, parBottom.x, parBottom.y);
	DrawChildren(leftCenter, parLevel + 1);
	DrawChildren(rightCenter, parLevel + 1);
}

Point GetPointOnCircle(Point center, int radius, double angleDegree)
{
	double angleRadian = angleDegree * M_PI / 180.0;
	int x = center.x + radius * cos(angleRadian);
	int y = center.y - radius * sin(angleRadian);
	return { x, y };
}

//void Binary_tree::draw_lines() const
//{
//	const int factor = lvl - 2;
//	Point p = point(0);
//	int nNodes{ 0 };				// number of nodes
//	for (int i = 1; i <= lvl; i++) {
//		if (i == 1) {
//			nNodes = 1;
//			fl_circle(p.x, p.y, nodeRadius);
//		}
//		else {
//			nNodes *= 2;
//			Point leftCenter{ p.x - (distance / 2 + factor * distance), p.y + i * distance };
//			for (int j = 0; j < nNodes; j++) {
//
//
//
//
//
//			}
//		}
//	}
//}
