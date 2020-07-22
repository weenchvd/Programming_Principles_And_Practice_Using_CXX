/* Exercise 14.6 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C14_Exercise_14.6.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Striped circle" };

	Striped_circle sCircle{ Point{200, 200}, 100, 1 };
	sw.attach(sCircle);
	Striped_circle sCircle2{ Point{200, 500}, 100, 9 };
	sw.attach(sCircle2);
	Striped_circle sCircle3{ Point{200, 800}, 100, 20 };
	sw.attach(sCircle3);
	Striped_circle sCircle4{ Point{700, 500}, 300, 4 };
	sw.attach(sCircle4);

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

void Striped_circle::draw_lines() const
{
	if (color().visibility()) {
		Circle::draw_lines();
		const int radius = Circle::radius();
		const int radiusSquared = radius * radius;
		const Point center = Circle::center();
		for (int y = center.y - radius + ls + 1; y < center.y + radius; y += ls + 1) {
			int sinus = center.y - y;
			int cosinus = sqrt(radiusSquared - sinus * sinus);
			int xRight = center.x + cosinus;
			int xLeft = center.x - cosinus;
			fl_line(xLeft, y, xRight, y);
		}
	}
}
