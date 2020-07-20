/* Exercise 13.19 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.19.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Star" };

	Star star1{ Point{300, 220}, 200, 5, 2 };
	star1.set_color(Color::dark_blue);
	star1.set_fill_color(Color::cyan);
	sw.attach(star1);
	Star star2{ Point{900, 300}, 280, 12, 5 };
	star2.set_color(Color::black);
	star2.set_fill_color(Color::dark_green);
	sw.attach(star2);
	Star star3{ Point{250, 800}, 100, 6, 2 };
	star3.set_color(Color::dark_red);
	star3.set_fill_color(Color::dark_yellow);
	sw.attach(star3);
	Star star4{ Point{500, 800}, 100, 10, 4 };
	star4.set_color(Color::black);
	star4.set_fill_color(Color::dark_magenta);
	sw.attach(star4);
	Star star5{ Point{750, 800}, 100, 8, 3 };
	star5.set_color(Color::dark_green);
	star5.set_fill_color(Color::dark_cyan);
	sw.attach(star5);
	Star star6{ Point{1000, 800}, 120, 12, 4 };
	star6.set_color(Color::dark_magenta);
	star6.set_fill_color(Color::dark_yellow);
	sw.attach(star6);
	Star star7{ Point{100, 500}, 80, 11, 5 };
	star7.set_color(Color::dark_magenta);
	star7.set_fill_color(Color::black);
	sw.attach(star7);
	Star star8{ Point{300, 500}, 80, 12, 2 };
	star8.set_color(Color::black);
	star8.set_fill_color(Color::dark_yellow);
	sw.attach(star8);
	Star star9{ Point{550, 500}, 120, 15, 7 };
	star9.set_color(Color::black);
	star9.set_fill_color(Color::dark_red);
	sw.attach(star9);

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

Point GetPointOnCircle(Point center, int radius, double angleDegree)
{
	double angleRadian = angleDegree * M_PI / 180.0;
	int x = center.x + radius * cos(angleRadian);
	int y = center.y - radius * sin(angleRadian);
	return { x, y };
}

Star::Star(Point center, int radius, int numberOfVertices, int density)
	: c{ center }, r{ radius }, p{ numberOfVertices }, q{ density }
{
	if (radius <= 0) error("The radius must be greater than 0");
	if (numberOfVertices < 5) error("The number of vertices must be greater than 4");
	if (density < 2 || density >= ((numberOfVertices % 2) ? numberOfVertices / 2 + 1 : numberOfVertices / 2)) {
		error("The density must be greater than 1 and less than the number of vertices");
	}
	constexpr double initialAngleDeg = 90.0;
	const double rotationAngleDeg = 360.0 / numberOfVertices;
	double angleDeg = initialAngleDeg;
	for (int i = 0; i < p; i++) {
		add(GetPointOnCircle(c, r, angleDeg));
		angleDeg += rotationAngleDeg;
	}
}

void Star::draw_lines() const
{
	if (fill_color().visibility() || color().visibility()) {
		Vector_ref<Point> vertices;
		int nPoints = number_of_points();
		for (int i = 0; i < nPoints; i++) {
			int j = i + 1;
			if (j >= nPoints) j -= nPoints;
			Point* p = new Point{ point(i).x, point(i).y };
			vertices.push_back(*p);
			int ii = i + q;
			if (ii >= nPoints) ii -= nPoints;
			int jj = j - q;
			if (jj < 0) jj += nPoints;
			Point* intersection = new Point;
			if (line_segment_intersect(point(i), point(ii), point(j), point(jj), *intersection)) {
				vertices.push_back(*intersection);
			}
			else error("No intersection");
		}
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for (int i = 0; i < vertices.size(); i++) {
				fl_vertex(vertices[i].x, vertices[i].y);
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());
		}
		if (color().visibility()) {
			for (int i = 1; i < vertices.size(); i++) {
				fl_line(vertices[i - 1].x, vertices[i - 1].y, vertices[i].x, vertices[i].y);
			}
			fl_line(vertices[vertices.size() - 1].x, vertices[vertices.size() - 1].y, vertices[0].x, vertices[0].y);
		}
		for (int i = 0; i < vertices.size(); i++) {
			delete &vertices[i];
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
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection) {
	bool parallel;
	pair<double, double> u = line_intersect(p1, p2, p3, p4, parallel);
	if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
	intersection.x = p1.x + u.first * (p2.x - p1.x);
	intersection.y = p1.y + u.first * (p2.y - p1.y);
	return true;
}
