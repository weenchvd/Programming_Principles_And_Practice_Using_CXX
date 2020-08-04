/* Exercise 16.2 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C16_Exercise_16.2.h"

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
	b_1_1{ Point{x_max() - x_max() * 5 / 6, y_max() - y_max() * 5 / 6}, x_max() / 6, y_max() / 6, "[1][1]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::black); } },
	b_1_2{ Point{x_max() - x_max() * 4 / 6, y_max() - y_max() * 5 / 6}, x_max() / 6, y_max() / 6, "[1][2]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::red); } },
	b_1_3{ Point{x_max() - x_max() * 3 / 6, y_max() - y_max() * 5 / 6}, x_max() / 6, y_max() / 6, "[1][3]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::green); } },
	b_1_4{ Point{x_max() - x_max() * 2 / 6, y_max() - y_max() * 5 / 6}, x_max() / 6, y_max() / 6, "[1][4]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::blue); } },
	b_2_1{ Point{x_max() - x_max() * 5 / 6, y_max() - y_max() * 4 / 6}, x_max() / 6, y_max() / 6, "[2][1]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::white); } },
	b_2_2{ Point{x_max() - x_max() * 4 / 6, y_max() - y_max() * 4 / 6}, x_max() / 6, y_max() / 6, "[2][2]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::dark_red); } },
	b_2_3{ Point{x_max() - x_max() * 3 / 6, y_max() - y_max() * 4 / 6}, x_max() / 6, y_max() / 6, "[2][3]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::dark_green); } },
	b_2_4{ Point{x_max() - x_max() * 2 / 6, y_max() - y_max() * 4 / 6}, x_max() / 6, y_max() / 6, "[2][4]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::dark_blue); } },
	b_3_1{ Point{x_max() - x_max() * 5 / 6, y_max() - y_max() * 3 / 6}, x_max() / 6, y_max() / 6, "[3][1]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::black); } },
	b_3_2{ Point{x_max() - x_max() * 4 / 6, y_max() - y_max() * 3 / 6}, x_max() / 6, y_max() / 6, "[3][2]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::cyan); } },
	b_3_3{ Point{x_max() - x_max() * 3 / 6, y_max() - y_max() * 3 / 6}, x_max() / 6, y_max() / 6, "[3][3]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::magenta); } },
	b_3_4{ Point{x_max() - x_max() * 2 / 6, y_max() - y_max() * 3 / 6}, x_max() / 6, y_max() / 6, "[3][4]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::yellow); } },
	b_4_1{ Point{x_max() - x_max() * 5 / 6, y_max() - y_max() * 2 / 6}, x_max() / 6, y_max() / 6, "[4][1]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::white); } },
	b_4_2{ Point{x_max() - x_max() * 4 / 6, y_max() - y_max() * 2 / 6}, x_max() / 6, y_max() / 6, "[4][2]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::dark_cyan); } },
	b_4_3{ Point{x_max() - x_max() * 3 / 6, y_max() - y_max() * 2 / 6}, x_max() / 6, y_max() / 6, "[4][3]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::dark_magenta); } },
	b_4_4{ Point{x_max() - x_max() * 2 / 6, y_max() - y_max() * 2 / 6}, x_max() / 6, y_max() / 6, "[4][4]",
		[](Address, Address pw) { reference_to<My_window>(pw).ChangeColor(Color::dark_yellow); } },
	next_button{ Point{ x_max() - 150, 0 }, 70, 20, "Next", cb_next },
	quit_button{ Point{ x_max() - 70, 0 }, 70, 20, "Quit", cb_quit },
	next_pushed{ false },
	quit_pushed{ false }
{
	attach(rect);
	attach(b_1_1);
	attach(b_1_2);
	attach(b_1_3);
	attach(b_1_4);
	attach(b_2_1);
	attach(b_2_2);
	attach(b_2_3);
	attach(b_2_4);
	attach(b_3_1);
	attach(b_3_2);
	attach(b_3_3);
	attach(b_3_4);
	attach(b_4_1);
	attach(b_4_2);
	attach(b_4_3);
	attach(b_4_4);
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

void My_window::ChangeColor(Color col)
{
	rect.set_fill_color(col);
	Fl::redraw();
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
