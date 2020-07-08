/* Exercise 12.11 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;

int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Polygons" };
	const Point tl{ 0,0 };
	const Point center{ tl.x + 600, tl.y + 500 };

	int nAngles = 6;
	double radius = 400.0;
	double azimuth = 0.0;
	PolygonPPP2 hexagon;
	for (int i = 0; i < nAngles; i++) {
		int x = double(center.x) + radius * cos(azimuth + 2.0 * M_PI * double(i) / nAngles);
		int y = double(center.y) + radius * sin(azimuth + 2.0 * M_PI * double(i) / nAngles);
		hexagon.add(Point{ x, y });
	}
	hexagon.set_color(Color::black);
	hexagon.set_fill_color(Color::dark_blue);
	sw.attach(hexagon);

	radius = radius * cos(M_PI / nAngles);
	nAngles = 5;
	PolygonPPP2 pentagon;
	for (int i = 0; i < nAngles; i++) {
		int x = double(center.x) + radius * cos(azimuth + 2.0 * M_PI * double(i) / nAngles);
		int y = double(center.y) + radius * sin(azimuth + 2.0 * M_PI * double(i) / nAngles);
		pentagon.add(Point{ x, y });
	}
	pentagon.set_color(Color::black);
	pentagon.set_fill_color(Color::dark_green);
	sw.attach(pentagon);

	radius = radius * cos(M_PI / nAngles);
	nAngles = 4;
	PolygonPPP2 square;
	for (int i = 0; i < nAngles; i++) {
		int x = double(center.x) + radius * cos(azimuth + 2.0 * M_PI * double(i) / nAngles);
		int y = double(center.y) + radius * sin(azimuth + 2.0 * M_PI * double(i) / nAngles);
		square.add(Point{ x, y });
	}
	square.set_color(Color::black);
	square.set_fill_color(Color::dark_red);
	sw.attach(square);

	radius = radius * cos(M_PI / nAngles);
	nAngles = 3;
	PolygonPPP2 triangle;
	for (int i = 0; i < nAngles; i++) {
		int x = double(center.x) + radius * cos(azimuth + 2.0 * M_PI * double(i) / nAngles);
		int y = double(center.y) + radius * sin(azimuth + 2.0 * M_PI * double(i) / nAngles);
		triangle.add(Point{ x, y });
	}
	triangle.set_color(Color::black);
	triangle.set_fill_color(Color::dark_cyan);
	sw.attach(triangle);

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
