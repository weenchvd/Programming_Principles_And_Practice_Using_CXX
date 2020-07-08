/* Exercise 12.13 */

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

int sgn(double val)
{
	return (val > 0) - (val < 0);
}

int main()
try {
	constexpr double a = 1.0;
	constexpr double b = 0.6;
	constexpr double m = 0.6;
	constexpr double n = 0.6;
	constexpr int nPoints = 100;
	constexpr double tmax = 2.0 * M_PI;
	constexpr int scale = 400;
	const Point tl{ 0,0 };
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Superellipse" };
	
	Point center{ 600, 500 };
	double t = 0;
	double step = tmax / nPoints;
	Line* pLine;
	vector<Line*> lines;
	int xPrev;
	int yPrev;
	for (int i = 0; i < nPoints; i++) {
		int x = int((pow(abs(cos(t)), 2.0 / m) * a * sgn(cos(t))) * scale) + center.x;
		int y = int((pow(abs(sin(t)), 2.0 / n) * b * sgn(sin(t))) * scale) + center.y;
		if (i > 0) {
			pLine = new Line{ Point{ xPrev, yPrev}, Point{ x, y } };
			if (i < nPoints / 4 || i > nPoints / 4 * 2 && i < nPoints / 4 * 3) {
				(*pLine).set_color(Color::dark_cyan);
			}
			else (*pLine).set_color(Color::dark_magenta);
			lines.push_back(pLine);
		}
		xPrev = x;
		yPrev = y;
		t += step;
	}
	for (int i = 0; i < lines.size(); i++) {
		sw.attach(*lines[i]);
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
