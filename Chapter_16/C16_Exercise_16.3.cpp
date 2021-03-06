﻿/* Exercise 16.3 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include<random>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C16_Exercise_16.3.h"
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
	suspicious_button{ Point{ x_max() - x_max() / 2 - 250, y_max() - y_max() / 2 - 50 }, 500, 100, "Suspicious",
		[](Address, Address pw) { reference_to<My_window>(pw).move(); } },
	quit_button{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<My_window>(pw).quit(); } },
	quit_pushed{ false }
{
	attach(fry);
	attach(suspicious_button);
	attach(quit_button);
}

bool My_window::wait_for_button()
{
	show();
	quit_pushed = false;
	while (!quit_pushed) Fl::wait();
	Fl::redraw();
	return quit_pushed;
}

void My_window::move()
{
	Point p{ rand_int(1, x_max() - 501), rand_int(1, y_max() - 101) };
	int xShift = p.x - suspicious_button.loc.x;
	int yShift = p.y - suspicious_button.loc.y;
	suspicious_button.move(xShift, yShift);
	fry.move(xShift, yShift);
	Fl::redraw();
}

void My_window::quit()
{
	quit_pushed = true;
	hide();
}
