/* Exercise 15.5 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C15_Exercise_15.5.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	constexpr int xmax = 1200;
	constexpr int ymax = 1200;
	constexpr int x_orig = 100;
	constexpr int y_orig = ymax - 100;
	const Point orig{ x_orig,y_orig };
	constexpr int r_min = 1;				// range [x:x]
	constexpr int r_max = 50;
	//constexpr int n_points = 600;			// number of points used in range
	constexpr int xlength = xmax - 200;
	constexpr int ylength = ymax - 200;
	constexpr int x_scale = ylength / r_max;
	constexpr int y_scale = 500;
	Simple_window sw{ Point{ 80, 0 }, xmax, ymax, "Leibniz’s series" };

	Axis x{ Axis::x, Point{ x_orig, y_orig }, xlength, xlength / x_scale, "one notch == 1" };
	Axis y{ Axis::y, Point{ x_orig, y_orig }, ylength, ylength / y_scale, "one notch == 1" };
	x.set_color(Color::red);
	y.set_color(Color::red);
	sw.attach(x);
	sw.attach(y);
	Text tx{ Point{x_orig + 50, y_orig + 20}, "n" };
	tx.set_color(Color::dark_red);
	sw.attach(tx);
	Text ty{ Point{x_orig - 20, y_orig - 50}, "x" };
	ty.set_color(Color::dark_red);
	sw.attach(ty);

	Line quarterPi{ Point{x_orig, y_orig - int(M_PI / 4 * y_scale) },
		Point{x_orig + xlength, y_orig - int(M_PI / 4 * y_scale)} };
	quarterPi.set_color(Color::magenta);
	sw.attach(quarterPi);
	Text tquarterPi{ Point{x_orig + xlength + 8, y_orig - int(M_PI / 4 * y_scale)}, "Pi/4" };
	tquarterPi.set_color(Color::dark_magenta);
	sw.attach(tquarterPi);

	for (int n = r_min + 1; n <= r_max; n++) {
		Function ls{ LeibnizSeries, r_min, double(n), Point{x_orig, y_orig}, n - 1, x_scale, y_scale };
		ls.set_color(Color::dark_green);
		sw.attach(ls);
		sw.wait_for_button();
		sw.detach(ls);
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

double LeibnizSeries(double n)
{
	if (n <= 0) return 0;
	double ls = 0.0;
	double denominator = 1.0;
	bool isAddition{ true };
	for (int i = 0; i < int(n); i++) {
		ls = (isAddition) ? ls + 1.0 / denominator : ls - 1.0 / denominator;
		isAddition = (isAddition) ? false : true;
		denominator += 2.0;
	}
	return ls;
}
