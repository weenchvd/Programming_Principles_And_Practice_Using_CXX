/* Exercise 16.7 */

#include<Windows.h>
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
#include"C16_Exercise_16.7.h"

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

	My_window mw{ Point{ 80, 0 }, windowLength, windowHeight, "Airplane" };

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

Airplane::Airplane(Point center, int airplaneSize, double rotationAngle)
	: c{ center }, size{ airplaneSize }, angle{ rotationAngle }
{
	if (airplaneSize < 60) size = 60;
	r1 = size / 2;
	a1 = 0.0;
	r2 = sqrt(r1 * 2 / 3 * r1 * 2 / 3 + r1 / 6 * r1 / 6);
	a2 = acos(double(r1 * 2 / 3) / r2) / M_PI * 180.0;
	r3 = sqrt(r1 / 6 * r1 / 6 * 2);
	a3 = acos(double(r1 / 6) / r3) / M_PI * 180.0;
	r4 = sqrt(r1 / 6 * r1 / 6 + r1 * r1);
	a4 = acos(double(-r1 / 6) / r4) / M_PI * 180.0;
	r5 = sqrt(-r1 * 5 / 12 * -r1 * 5 / 12 + r1 * r1);
	a5 = acos(double(-r1 * 5 / 12) / r5) / M_PI * 180.0;
	r6 = sqrt(-r1 * 3 / 12 * -r1 * 3 / 12 + r1 / 6 * r1 / 6);
	a6 = acos(double(-r1 * 3 / 12) / r6) / M_PI * 180.0;
	r7 = sqrt(-r1 * 9 / 12 * -r1 * 9 / 12 + r1 / 6 * r1 / 6);
	a7 = acos(double(-r1 * 9 / 12) / r7) / M_PI * 180.0;
	r8 = sqrt(-r1 * 11 / 12 * -r1 * 11 / 12 + r1 / 2 * r1 / 2);
	a8 = acos(double(-r1 * 11 / 12) / r8) / M_PI * 180.0;
	r9 = sqrt(-r1 * -r1 + r1 / 2 * r1 / 2);
	a9 = acos(double(-r1) / r9) / M_PI * 180.0;
	r10 = r1 - r1 / 12;
	a10 = 180.0;
}

void Airplane::draw_lines() const
{
	Point p1 = GetPointOnCircle(c, r1, a1 + angle);
	Point p2 = GetPointOnCircle(c, r2, a2 + angle);
	Point p3 = GetPointOnCircle(c, r3, a3 + angle);
	Point p4 = GetPointOnCircle(c, r4, a4 + angle);
	Point p5 = GetPointOnCircle(c, r5, a5 + angle);
	Point p6 = GetPointOnCircle(c, r6, a6 + angle);
	Point p7 = GetPointOnCircle(c, r7, a7 + angle);
	Point p8 = GetPointOnCircle(c, r8, a8 + angle);
	Point p9 = GetPointOnCircle(c, r9, a9 + angle);
	Point p10 = GetPointOnCircle(c, r10, a10 + angle);

	Point p11 = GetPointOnCircle(c, r9, -a9 + angle);
	Point p12 = GetPointOnCircle(c, r8, -a8 + angle);
	Point p13 = GetPointOnCircle(c, r7, -a7 + angle);
	Point p14 = GetPointOnCircle(c, r6, -a6 + angle);
	Point p15 = GetPointOnCircle(c, r5, -a5 + angle);
	Point p16 = GetPointOnCircle(c, r4, -a4 + angle);
	Point p17 = GetPointOnCircle(c, r3, -a3 + angle);
	Point p18 = GetPointOnCircle(c, r2, -a2 + angle);

	fl_line(p1.x, p1.y, p2.x, p2.y);
	fl_line(p2.x, p2.y, p3.x, p3.y);
	fl_line(p3.x, p3.y, p4.x, p4.y);
	fl_line(p4.x, p4.y, p5.x, p5.y);
	fl_line(p5.x, p5.y, p6.x, p6.y);
	fl_line(p6.x, p6.y, p7.x, p7.y);
	fl_line(p7.x, p7.y, p8.x, p8.y);
	fl_line(p8.x, p8.y, p9.x, p9.y);
	fl_line(p9.x, p9.y, p10.x, p10.y);
	fl_line(p10.x, p10.y, p11.x, p11.y);
	fl_line(p11.x, p11.y, p12.x, p12.y);
	fl_line(p12.x, p12.y, p13.x, p13.y);
	fl_line(p13.x, p13.y, p14.x, p14.y);
	fl_line(p14.x, p14.y, p15.x, p15.y);
	fl_line(p15.x, p15.y, p16.x, p16.y);
	fl_line(p16.x, p16.y, p17.x, p17.y);
	fl_line(p17.x, p17.y, p18.x, p18.y);
	fl_line(p18.x, p18.y, p1.x, p1.y);
}

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	buttonStart{ Point{ x_max() / 2 - 80, 0 }, 70, 20, "Start",
		[](Address, Address pw) { reference_to<My_window>(pw).start(); } },
	buttonStop{ Point{ x_max() / 2 + 10, 0 }, 70, 20, "Stop",
		[](Address, Address pw) { reference_to<My_window>(pw).stop(); } },
	buttonQuit{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<My_window>(pw).quit(); } },
	toFly{ false },
	quitPushed{ false }
{
	airplane.set_color(Color::dark_magenta);
	airplane.set_style(Line_style(Line_style::Line_style_type::solid, 3));
	attach(airplane);
	attach(buttonStart);
	attach(buttonStop);
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

void My_window::start()
{
	toFly = true;
	double angle = defaultRotationAngle;
	while (toFly) {
		airplane.SetCenter(GetPointOnCircle(airplaneCenter, defaultFlyRadius, angle));
		airplane.SetAngle(angle + 90);
		Fl::wait(0.0);
		redraw();
		Sleep(10);
		angle += defaultRotationAngleStep;
		if (angle >= defaultRotationAngle + 360.0) angle = defaultRotationAngle;
	}
}

void My_window::stop()
{
	toFly = false;
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
