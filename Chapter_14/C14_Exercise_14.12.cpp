/* Exercise 14.12 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C14_Exercise_14.12.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Binary tree" };

	Binary_tree bt1{ Point{600, 50}, 4 };
	sw.attach(bt1);

	Binary_tree_triangle btt1{ Point{600, 300}, 4 };
	sw.attach(btt1);

	Binary_tree_rhombus btr1{ Point{600, 600}, 5 };
	sw.attach(btr1);

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

void Binary_tree_triangle::draw_lines() const
{
	constexpr double factor = 1.333333;
	if (GetLevel() > 0) {
		const int yShiftCenter = int(GetRadius() * factor - GetRadius());
		Point center = Point{ point(0).x, point(0).y + yShiftCenter };
		Point p1 = GetPointOnCircle(center, GetRadius() + yShiftCenter, 90);
		Point p2 = GetPointOnCircle(center, GetRadius() + yShiftCenter, 90 + 360 / 3);
		Point p3 = GetPointOnCircle(center, GetRadius() + yShiftCenter, 90 + 2 * 360 / 3);
		fl_line(p1.x, p1.y, p2.x, p2.y);
		fl_line(p2.x, p2.y, p3.x, p3.y);
		fl_line(p3.x, p3.y, p1.x, p1.y);
		center = point(0);
		DrawChildren(center, 1);
	}
}

// Point par - center of the parent node, parLevel - current level of the parent
void Binary_tree_triangle::DrawChildren(Point par, const int parLevel) const
{
	constexpr double factor = 1.333333;
	const int yShiftCenter = int(GetRadius() * factor - GetRadius());
	const int dif = GetLevel() - parLevel;			// difference between the max level and the parent level
	if (dif < 1) return;
	int xIndentation = GetDistance() / 2;
	for (int i = 1; i < dif; i++) {
		xIndentation *= 2;
	}
	Point leftCenter{ par.x - xIndentation, par.y + GetDistance() + yShiftCenter };
	Point rightCenter{ par.x + xIndentation, par.y + GetDistance() + yShiftCenter };
	Point left1 = GetPointOnCircle(leftCenter, GetRadius() + yShiftCenter, 90);
	Point left2 = GetPointOnCircle(leftCenter, GetRadius() + yShiftCenter, 90 + 360 / 3);
	Point left3 = GetPointOnCircle(leftCenter, GetRadius() + yShiftCenter, 90 + 2 * 360 / 3);
	fl_line(left1.x, left1.y, left2.x, left2.y);
	fl_line(left2.x, left2.y, left3.x, left3.y);
	fl_line(left3.x, left3.y, left1.x, left1.y);
	Point right1 = GetPointOnCircle(rightCenter, GetRadius() + yShiftCenter, 90);
	Point right2 = GetPointOnCircle(rightCenter, GetRadius() + yShiftCenter, 90 + 360 / 3);
	Point right3 = GetPointOnCircle(rightCenter, GetRadius() + yShiftCenter, 90 + 2 * 360 / 3);
	fl_line(right1.x, right1.y, right2.x, right2.y);
	fl_line(right2.x, right2.y, right3.x, right3.y);
	fl_line(right3.x, right3.y, right1.x, right1.y);
	leftCenter = Point{ par.x - xIndentation, par.y + GetDistance() };
	rightCenter = Point{ par.x + xIndentation, par.y + GetDistance() };
	Point leftTop = GetPointOnCircle(leftCenter, GetRadius(), 90);
	Point rightTop = GetPointOnCircle(rightCenter, GetRadius(), 90);
	Point parBottom = GetPointOnCircle(par, GetRadius(), 270);
	fl_line(leftTop.x, leftTop.y, parBottom.x, parBottom.y);
	fl_line(rightTop.x, rightTop.y, parBottom.x, parBottom.y);
	DrawChildren(leftCenter, parLevel + 1);
	DrawChildren(rightCenter, parLevel + 1);
}

void Binary_tree_rhombus::draw_lines() const
{
	if (GetLevel() > 0) {
		Point p = point(0);
		Point p1 = GetPointOnCircle(p, GetRadius(), 0);
		Point p2 = GetPointOnCircle(p, GetRadius(), 90);
		Point p3 = GetPointOnCircle(p, GetRadius(), 180);
		Point p4 = GetPointOnCircle(p, GetRadius(), 270);
		fl_line(p1.x, p1.y, p2.x, p2.y);
		fl_line(p2.x, p2.y, p3.x, p3.y);
		fl_line(p3.x, p3.y, p4.x, p4.y);
		fl_line(p4.x, p4.y, p1.x, p1.y);
		DrawChildren(p, 1);
	}
}

// Point par - center of the parent node, parLevel - current level of the parent
void Binary_tree_rhombus::DrawChildren(Point par, const int parLevel) const
{
	const int dif = GetLevel() - parLevel;						// difference between the max level and the parent level
	if (dif < 1) return;
	int xIndentation = GetDistance() / 2;
	for (int i = 1; i < dif; i++) {
		xIndentation *= 2;
	}
	Point leftCenter{ par.x - xIndentation, par.y + GetDistance() };
	Point rightCenter{ par.x + xIndentation, par.y + GetDistance() };
	Point left1 = GetPointOnCircle(leftCenter, GetRadius(), 0);
	Point left2 = GetPointOnCircle(leftCenter, GetRadius(), 90);
	Point left3 = GetPointOnCircle(leftCenter, GetRadius(), 180);
	Point left4 = GetPointOnCircle(leftCenter, GetRadius(), 270);
	fl_line(left1.x, left1.y, left2.x, left2.y);
	fl_line(left2.x, left2.y, left3.x, left3.y);
	fl_line(left3.x, left3.y, left4.x, left4.y);
	fl_line(left4.x, left4.y, left1.x, left1.y);
	Point right1 = GetPointOnCircle(rightCenter, GetRadius(), 0);
	Point right2 = GetPointOnCircle(rightCenter, GetRadius(), 90);
	Point right3 = GetPointOnCircle(rightCenter, GetRadius(), 180);
	Point right4 = GetPointOnCircle(rightCenter, GetRadius(), 270);
	fl_line(right1.x, right1.y, right2.x, right2.y);
	fl_line(right2.x, right2.y, right3.x, right3.y);
	fl_line(right3.x, right3.y, right4.x, right4.y);
	fl_line(right4.x, right4.y, right1.x, right1.y);
	Point leftTop = GetPointOnCircle(leftCenter, GetRadius(), 90);
	Point rightTop = GetPointOnCircle(rightCenter, GetRadius(), 90);
	Point parBottom = GetPointOnCircle(par, GetRadius(), 270);
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
