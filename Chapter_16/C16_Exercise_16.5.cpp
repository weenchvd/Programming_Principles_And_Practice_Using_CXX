/* Exercise 16.5 */

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
#include"C16_Exercise_16.5.h"

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
	inboxFileName{ Point{ 200, 0 }, 300, 20, "File name:" },
	buttonOpen{ Point{ 520, 0 }, 100, 20, "Open file",
		[](Address, Address pw) { reference_to<My_window>(pw).OpenFile(); } },
	buttonNext{ Point{ x_max() - 150, 0 }, 70, 20, "Next",
		[](Address, Address pw) { reference_to<My_window>(pw).MoveCircle(); } },
	buttonQuit{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<My_window>(pw).quit(); } },
	quitPushed{ false }
{
	attach(inboxFileName);
	attach(buttonOpen);
	attach(buttonNext);
	attach(buttonQuit);
	attach(circle);
}

void My_window::OpenFile()
{
	if (ifs.is_open()) {
		ifs.close();
		Point c = circle.center();
		circle.move(500 - c.x, 500 - c.y);
		redraw();
	}
	string file = inboxFileName.get_string();
	ifs.open(file);
	if (!ifs) error("Error. Can't open input file: ", file);
}

void My_window::MoveCircle()
{
	Point p;
	if (!ifs) return;
	if (ifs >> p) {
		Point c = circle.center();
		circle.move(p.x - c.x, p.y - c.y);
	}
	redraw();
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

ifstream& Graph_lib::operator>>(ifstream& ifs, Point& p)
{
	char comma = 0;
	Point temp;
	if (ifs >> temp.x >> comma >> temp.y) {
		if (comma == ',') p = temp;
		else ifs.clear(ios_base::failbit);
	}
	return ifs;
}

#include <FL/Fl_Output.H>
string Graph_lib::In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	string s;
	return s.assign(pi.value());
}
