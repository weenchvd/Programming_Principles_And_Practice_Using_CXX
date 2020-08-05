/* Exercise 16.4 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C16_Exercise_16.4.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	constexpr int windowLength = 1280;
	constexpr int windowHeight = 1024;

	My_window mw{ Point{ 80, 0 }, windowLength, windowHeight, "My_window" };
	

	mw.wait_for_button();
	return 0;
}
catch (runtime_error& e) {
	cerr << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "Error. Exception\n";
	return 2;
}

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	inboxXOrigin{ Point{ 200, 0}, 50, 20, "x:" },
	inboxYOrigin{ Point{ 200, 20}, 50, 20, "y:" },
	inboxRadius{ Point{ 200, 40}, 50, 20, "radius:" },
	menuShape{ Point{ 400, 0}, 200, 20, Menu::Kind::vertical, "" },
	buttonMenuShape{ Point{400, 0}, 200, 20, "Geomentrical shape",
		[](Address, Address pw) { reference_to<My_window>(pw).MenuShapePressed(); } },
	buttonQuit{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<My_window>(pw).quit(); } },
	quitPushed{ false }
{
	attach(inboxXOrigin);
	attach(inboxYOrigin);
	attach(inboxRadius);
	menuShape.attach(new Button{ Point {0, 0}, 0, 0, "Circle",
		[](Address, Address pw) { reference_to<My_window>(pw).DrawCircle(); } });
	menuShape.attach(new Button{ Point {0, 0}, 0, 0, "Square",
		[](Address, Address pw) { reference_to<My_window>(pw).DrawSquare(); } });
	menuShape.attach(new Button{ Point {0, 0}, 0, 0, "Triangle",
		[](Address, Address pw) { reference_to<My_window>(pw).DrawTriangle(); } });
	menuShape.attach(new Button{ Point {0, 0}, 0, 0, "Hexagon",
		[](Address, Address pw) { reference_to<My_window>(pw).DrawHexagon(); } });
	attach(menuShape);
	menuShape.hide();
	attach(buttonMenuShape);
	attach(buttonQuit);
}

bool My_window::wait_for_button()
{
	show();
	quitPushed = false;
	while (!quitPushed) Fl::wait();
	Fl::redraw();
	return quitPushed;
}

void My_window::DrawCircle()
{
	int x = inboxXOrigin.get_int();
	int y = inboxYOrigin.get_int();
	int r = inboxRadius.get_int();
	attach(*(new Circle{ Point{x, y}, r }));
	menuShape.hide();
	buttonMenuShape.show();
}

void My_window::DrawSquare()
{
	Point p{ inboxXOrigin.get_int(), inboxYOrigin.get_int() };
	int r = inboxRadius.get_int();
	Point p1 = GetPointOnCircle(p, r, 135);
	Point p2 = GetPointOnCircle(p, r, 315);
	attach(*(new RectanglePPP2{ p1, p2 }));
	menuShape.hide();
	buttonMenuShape.show();
}

void My_window::DrawTriangle()
{
	Point p{ inboxXOrigin.get_int(), inboxYOrigin.get_int() };
	int r = inboxRadius.get_int();
	Point p1 = GetPointOnCircle(p, r, 90);
	Point p2 = GetPointOnCircle(p, r, 210);
	Point p3 = GetPointOnCircle(p, r, 330);
	Closed_polyline* ptr = new Closed_polyline;
	ptr->add(p1);
	ptr->add(p2);
	ptr->add(p3);
	attach(*ptr);
	menuShape.hide();
	buttonMenuShape.show();
}

void My_window::DrawHexagon()
{
	Point p{ inboxXOrigin.get_int(), inboxYOrigin.get_int() };
	int r = inboxRadius.get_int();
	Point p1 = GetPointOnCircle(p, r, 90);
	Point p2 = GetPointOnCircle(p, r, 150);
	Point p3 = GetPointOnCircle(p, r, 210);
	Point p4 = GetPointOnCircle(p, r, 270);
	Point p5 = GetPointOnCircle(p, r, 330);
	Point p6 = GetPointOnCircle(p, r, 390);
	Closed_polyline* ptr = new Closed_polyline;
	ptr->add(p1);
	ptr->add(p2);
	ptr->add(p3);
	ptr->add(p4);
	ptr->add(p5);
	ptr->add(p6);
	attach(*ptr);
	menuShape.hide();
	buttonMenuShape.show();
}

void My_window::quit()
{
	quitPushed = true;
	hide();
}

Point Graph_lib::GetPointOnCircle(Point center, int radius, double angleDegree)
{
	double angleRadian = angleDegree * M_PI / 180.0;
	int x = center.x + radius * cos(angleRadian);
	int y = center.y - radius * sin(angleRadian);
	return { x, y };
}
