/* Exercise 16.1 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C16_Exercise_16.1.h"

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
	next_button{ Point{ x_max() - 150, 0 }, 70, 20, "Next", cb_next },
	quit_button{ Point{ x_max() - 70, 0 }, 70, 20, "Quit", cb_quit },
	next_pushed{ false },
	quit_pushed{ false }
{
	attach(next_button);
	attach(quit_button);
}

bool My_window::wait_for_button()
{
	show();
	next_pushed = false;
	while (!(next_pushed || quit_pushed)) Fl::wait();
	Fl::redraw();
	return true;
}

void My_window::cb_next(Address, Address pw)
{
	reference_to<My_window>(pw).next();
}

void My_window::cb_quit(Address, Address pw)
{
	reference_to<My_window>(pw).quit();
}

void My_window::next()
{
	next_pushed = true;
	hide();
}

void My_window::quit()
{
	quit_pushed = true;
	hide();
}
