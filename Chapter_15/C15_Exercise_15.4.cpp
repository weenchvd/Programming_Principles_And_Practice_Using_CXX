/* Exercise 15.4 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C15_Exercise_15.4.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	constexpr int xmax = 1600;
	constexpr int ymax = 1200;
	constexpr int x_orig = xmax / 2;
	constexpr int y_orig = ymax / 2;
	const Point orig{ x_orig,y_orig };
	constexpr double r_min = -M_PI * 2;		// range [x:x)
	constexpr double r_max = M_PI * 2;
	constexpr int n_points = 600;			// number of points used in range
	constexpr int x_scale = 100;
	constexpr int y_scale = 100;
	Simple_window sw{ Point{ 80, 0 }, xmax, ymax, "Sin cos" };

	constexpr int xlength = xmax - 400;
	constexpr int ylength = ymax - 200;
	Axis x{ Axis::x, Point{ 200, y_orig }, xlength, xlength / x_scale, "one notch == 1" };
	Axis y{ Axis::y, Point{ x_orig, ylength + 100 }, ylength, ylength / y_scale, "one notch == 1" };
	x.set_color(Color::black);
	y.set_color(Color::black);
	sw.attach(x);
	sw.attach(y);

	Function fsin{ sin, r_min, r_max, orig, n_points, x_scale, y_scale };
	fsin.set_color(Color::blue);
	sw.attach(fsin);
	Text tsin{ Point{ 10, orig.y - int(sin(r_min) * y_scale) }, "sin(x)" };
	tsin.set_color(Color::blue);
	sw.attach(tsin);

	Function fcos{ cos, r_min, r_max, orig, n_points, x_scale, y_scale };
	fcos.set_color(Color::red);
	sw.attach(fcos);
	Text tcos{ Point{ 10, orig.y - int(cos(r_min) * y_scale) + 20 }, "cos(x)" };
	tcos.set_color(Color::red);
	sw.attach(tcos);

	Function fsum{ [](double x) { return sin(x) + cos(x); }, r_min, r_max, orig, n_points, x_scale, y_scale };
	fsum.set_color(Color::dark_green);
	sw.attach(fsum);
	Text tsum{ Point{ 10, orig.y - int((sin(r_min) + cos(r_min)) * y_scale) - 20 }, "sin(x)+cos(x)" };
	tsum.set_color(Color::dark_green);
	sw.attach(tsum);

	Function fsum2{ [](double x) { return sin(x) * sin(x) + cos(x) * cos(x); },
		r_min, r_max, orig, n_points, x_scale, y_scale };
	fsum2.set_color(Color::dark_yellow);
	sw.attach(fsum2);
	Text tsum2{ Point{ 10, orig.y - int((sin(r_min) * sin(r_min) + cos(r_min) * cos(r_min)) * y_scale) },
		"sin(x)^2+cos(x)^2" };
	tsum2.set_color(Color::dark_yellow);
	sw.attach(tsum2);

	
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
