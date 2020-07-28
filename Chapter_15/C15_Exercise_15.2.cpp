/* Exercise 15.2 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include<functional>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C15_Exercise_15.2.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	constexpr int xmax = 1280;
	constexpr int ymax = 1280;
	constexpr int x_orig = xmax / 2;
	constexpr int y_orig = ymax / 2;
	const Point orig{ x_orig,y_orig };
	constexpr int r_min = -10;				// range [–10:11)
	constexpr int r_max = 11;
	constexpr int n_points = 400;			// number of points used in range
	constexpr int x_scale = 30;
	constexpr int y_scale = 30;
	Simple_window sw{ Point{ 80, 0 }, xmax, ymax, "Fct" };

	constexpr int xlength = xmax - 80;
	constexpr int ylength = ymax - 80;
	Axis x{ Axis::x, Point{ 40, y_orig }, xlength, xlength / x_scale, "one notch == 1" };
	Axis y{ Axis::y, Point{ x_orig, ylength + 40 }, ylength, ylength / y_scale, "one notch == 1" };
	x.set_color(Color::red);
	y.set_color(Color::red);
	sw.attach(x);
	sw.attach(y);

	Fct::Fct s{ one, r_min, r_max, orig, n_points, x_scale, y_scale };
	sw.attach(s);
	sw.wait_for_button();

	s.reset(double(r_min) * 1.2, double(r_max) * 1.2);
	sw.set_label("range == range * 1.2");
	sw.wait_for_button();

	s.reset(600);
	sw.set_label("count == 600");
	sw.wait_for_button();

	s.reset(slope);
	sw.set_label("fct == slope");
	sw.wait_for_button();

	s.reset(square);
	sw.set_label("fct == square");
	sw.wait_for_button();
	
	s.reset([] (double x) { return x / 2; });
	sw.set_label("fct == lambda slope");
	sw.wait_for_button();

	s.reset_scale(40, 40);
	sw.set_label("scale == 40, 40");
	sw.wait_for_button();

	s.reset_scale(x_scale, y_scale);
	sw.set_label("scale == 30, 30");
	sw.wait_for_button();

	s.reset(Point{orig.x - 50, orig.y - 50});
	sw.set_label("origin == orig.x - 50, orig.y - 50");
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

Fct::Fct::Fct(Graph_lib::Fct f, double r1, double r2, Point orig, int count, double xscale, double yscale)
	: fct{ f }, x1{ r1 }, x2{ r2 }, o{ orig }, cnt{ count }, xs{ xscale }, ys{ yscale }
{
	if (r2 - r1 <= 0) error("bad graphing range");
	if (count <= 0) error("non-positive graphing count");
	double dist = (r2 - r1) / count;
	double r = r1;
	for (int i = 0; i < count; ++i) {
		add(Point(orig.x + int(r * xscale), orig.y - int(f(r) * yscale)));
		r += dist;
	}
}

void Fct::Fct::reset(Graph_lib::Fct f)
{
	if (cnt != number_of_points()) error("cnt != points.size()");
	fct = f;
	double dist = (x2 - x1) / cnt;
	double r = x1;
	for (int i = 0; i < cnt; ++i) {
		set_point(i, Point{ o.x + int(r * xs), o.y - int(fct(r) * ys) });
		r += dist;
	}
}

void Fct::Fct::reset(double r1, double r2)
{
	if (cnt != number_of_points()) error("cnt != points.size()");
	x1 = r1;
	x2 = r2;
	double dist = (x2 - x1) / cnt;
	double r = x1;
	for (int i = 0; i < cnt; ++i) {
		set_point(i, Point{ o.x + int(r * xs), o.y - int(fct(r) * ys) });
		r += dist;
	}
}

void Fct::Fct::reset(Point orig)
{
	if (cnt != number_of_points()) error("cnt != points.size()");
	o = orig;
	double dist = (x2 - x1) / cnt;
	double r = x1;
	for (int i = 0; i < cnt; ++i) {
		set_point(i, Point{ o.x + int(r * xs), o.y - int(fct(r) * ys) });
		r += dist;
	}
}

void Fct::Fct::reset(int count)
{
	if (count < cnt) error("cnt < points.size()");
	cnt = count;
	double dist = (x2 - x1) / cnt;
	double r = x1;
	int nPoints = number_of_points();
	if (cnt == nPoints) {
		for (int i = 0; i < cnt; ++i) {
			set_point(i, Point{ o.x + int(r * xs), o.y - int(fct(r) * ys) });
			r += dist;
		}
	}
	else {
		int i;
		for (i = 0; i < nPoints; ++i) {
			set_point(i, Point{ o.x + int(r * xs), o.y - int(fct(r) * ys) });
			r += dist;
		}
		for (; i < cnt; ++i) {
			add(Point{ o.x + int(r * xs), o.y - int(fct(r) * ys) });
			r += dist;
		}
	}
}

void Fct::Fct::reset_scale(double xscale, double yscale)
{
	if (cnt != number_of_points()) error("cnt != points.size()");
	xs = xscale;
	ys = yscale;
	double dist = (x2 - x1) / cnt;
	double r = x1;
	for (int i = 0; i < cnt; ++i) {
		set_point(i, Point{ o.x + int(r * xs), o.y - int(fct(r) * ys) });
		r += dist;
	}
}

double one(double)
{
	return 1;
}

double slope(double x)
{
	return x / 2;
}

double square(double x)
{
	return x * x;
}
