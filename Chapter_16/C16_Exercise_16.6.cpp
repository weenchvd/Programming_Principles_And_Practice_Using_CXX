/* Exercise 16.6 */

#include<Windows.h>
#include<ctime>
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
#include"C16_Exercise_16.6.h"

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

	My_window mw{ Point{ 80, 0 }, windowLength, windowHeight, "Analog clock" };
	mw.RunClock();

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

void My_window::RunClock()
{
	while (!QuitPushed()) {
		if (clock.UpdateTime()) {
			Fl::wait(0.0);
			redraw();
		}
		else Sleep(100);
	}
}

Clock::Clock(Point center)
{
	add(center);
	UpdateTime();
}

bool Clock::UpdateTime()
{
	time_t rawTime;
	time(&rawTime);
	t = *localtime(&rawTime);
	if (t.tm_sec == sec) return false;
	else sec = t.tm_sec;
	return true;
}

void Clock::draw_lines() const
{
	Point center = point(0);
	fl_circle(center.x, center.y, clockRadius);
	// draw hour hand
	double angle = 90 - t.tm_hour * nIntervalsInHour * angleInterval + 360;
	Point po = GetPointOnCircle(center, hourHandRadius, angle);						// outer point
	fl_line_style(defaultStyle, hourHandWidth);
	fl_line(center.x, center.y, po.x, po.y);
	// draw minute hand
	angle = 90 - t.tm_min * angleInterval + 360;
	po = GetPointOnCircle(center, minuteHandRadius, angle);
	fl_line_style(defaultStyle, minuteHandWidth);
	fl_line(center.x, center.y, po.x, po.y);
	// draw second hand
	angle = 90 - t.tm_sec * angleInterval + 360;
	po = GetPointOnCircle(center, secondHandRadius, angle);
	Fl_Color oldColor = fl_color();
	fl_color(secondHandColor);
	fl_line_style(defaultStyle);
	fl_line(center.x, center.y, po.x, po.y);
	fl_color(oldColor);
	// draw notches
	Point pi;													// inner point
	angle = 0;
	for (int i = 0; i < nIntervals; i++) {
		if (i % nIntervalsInHour) {
			po = GetPointOnCircle(center, notchOuterRadius, angle);
			pi = GetPointOnCircle(center, notchOuterRadius - minuteNotchSize, angle);
			fl_line_style(defaultStyle);
			fl_line(po.x, po.y, pi.x, pi.y);
		}
		else {
			po = GetPointOnCircle(center, notchOuterRadius, angle);
			pi = GetPointOnCircle(center, notchOuterRadius - hourNotchSize, angle);
			fl_line_style(defaultStyle, hourNotchWidth);
			fl_line(po.x, po.y, pi.x, pi.y);
		}
		angle += angleInterval;
	}
}

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	buttonQuit{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<My_window>(pw).quit(); } },
	quitPushed{ false }
{
	clock.set_color(Color::black);
	clock.set_style(Line_style(Line_style::Line_style_type::solid, 5));
	attach(clock);
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
