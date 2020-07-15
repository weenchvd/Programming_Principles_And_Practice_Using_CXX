/* Exercise 13.3 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.3.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Arrow" };

	Arrow arrow10{ Point{ 500, 500 }, Point{ 500, 800 } };
	sw.attach(arrow10);
	Arrow arrow11{ Point{ 500, 500 }, Point{ 400, 700 } };
	sw.attach(arrow11);
	Arrow arrow12{ Point{ 500, 500 }, Point{ 400, 900 } };
	sw.attach(arrow12);
	Arrow arrow13{ Point{ 500, 500 }, Point{ 200, 700 } };
	sw.attach(arrow13);
	Arrow arrow20{ Point{ 500, 500 }, Point{ 200, 500 } };
	sw.attach(arrow20);
	Arrow arrow21{ Point{ 500, 500 }, Point{ 600, 800 } };
	sw.attach(arrow21);
	Arrow arrow22{ Point{ 500, 500 }, Point{ 700, 800 } };
	sw.attach(arrow22);
	Arrow arrow23{ Point{ 500, 500 }, Point{ 800, 800 } };
	sw.attach(arrow23);
	Arrow arrow30{ Point{ 500, 500 }, Point{ 500, 100 } };
	sw.attach(arrow30);
	Arrow arrow31{ Point{ 500, 500 }, Point{ 700, 200 } };
	sw.attach(arrow31);
	Arrow arrow32{ Point{ 500, 500 }, Point{ 900, 400 } };
	sw.attach(arrow32);
	Arrow arrow40{ Point{ 500, 500 }, Point{ 1000, 500 } };
	sw.attach(arrow40);
	Arrow arrow41{ Point{ 500, 500 }, Point{ 400, 400 } };
	sw.attach(arrow41);
	Arrow arrow42{ Point{ 500, 500 }, Point{ 400, 100 } };
	sw.attach(arrow42);
	Arrow arrow43{ Point{ 500, 500 }, Point{ 100, 300 } };
	sw.attach(arrow43);
	Arrow arrow50{ Point{ 1100, 100 }, Point{ 1100, 400 } };
	sw.attach(arrow50);
	Arrow arrow60{ Point{ 1100, 900 }, Point{ 1100, 600 } };
	sw.attach(arrow60);
	Arrow arrow70{ Point{ 50, 950 }, Point{ 450, 950 } };
	sw.attach(arrow70);
	Arrow arrow80{ Point{ 1050, 950 }, Point{ 550, 950 } };
	sw.attach(arrow80);

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

Arrow::Arrow(Point from, Point to)
	: lineStart{ from }, lineEnd{ to }
{
	constexpr int arrowheadLength = 20;
	constexpr int arrowheadWidth = 12;
	int xLength = lineStart.x - lineEnd.x;
	int yLength = -(lineStart.y - lineEnd.y);
	double hypotenuse = sqrt(pow(xLength, 2) + pow(yLength, 2));
	double angleRadian{ 0 };
	if (xLength >= 0 && yLength >= 0 || xLength <= 0 && yLength >= 0) {		// 0 <= angle <= Pi
		angleRadian = acos(double(xLength) / hypotenuse);
	}
	else {																	// Pi < angle < 2*Pi
		angleRadian = -acos(double(xLength) / hypotenuse);
	}
	/*	point(0,0) is origin
		x' = xcos(angle) - ysin(angle);
		y' = xsin(angle) + ycos(angle);
	*/
	Point p2{ arrowheadLength, -arrowheadWidth / 2 };
	Point p3{ arrowheadLength, arrowheadWidth / 2 };
	arrowhead2.x = p2.x * cos(angleRadian) - p2.y * sin(angleRadian);
	arrowhead2.y = p2.x * sin(angleRadian) + p2.y * cos(angleRadian);
	arrowhead3.x = p3.x * cos(angleRadian) - p3.y * sin(angleRadian);
	arrowhead3.y = p3.x * sin(angleRadian) + p3.y * cos(angleRadian);
	arrowhead2.x += lineEnd.x;
	arrowhead2.y = -arrowhead2.y + lineEnd.y;
	arrowhead3.x += lineEnd.x;
	arrowhead3.y = -arrowhead3.y + lineEnd.y;
	add(lineStart);
	add(lineEnd);
	add(arrowhead2);
	add(arrowhead3);
}

void Arrow::draw_lines() const
{
	fl_line(lineStart.x, lineStart.y, lineEnd.x, lineEnd.y);
	fl_polygon(lineEnd.x, lineEnd.y, arrowhead2.x, arrowhead2.y, arrowhead3.x, arrowhead3.y);
}