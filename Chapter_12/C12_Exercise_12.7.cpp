/* Exercise 12.7 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;

int main()
try {
	constexpr int tlWidth = 300;
	constexpr int tlHeight = 50;
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "House" };
	RectanglePPP2 chimney{ Point{tlWidth + 150, tlHeight}, 70, 250 };
	chimney.set_color(Color::dark_green);
	chimney.set_fill_color(Color::dark_green);
	sw.attach(chimney);
	PolygonPPP2 roof;
	roof.add(Point{ tlWidth, tlHeight + 300 });
	roof.add(Point{ tlWidth + 300, tlHeight });
	roof.add(Point{ tlWidth + 600, tlHeight + 300 });
	roof.set_color(Color::dark_green);
	roof.set_fill_color(Color::dark_green);
	sw.attach(roof);
	RectanglePPP2 house{ Point{tlWidth, tlHeight + 300}, 600, 600 };
	house.set_color(Color::dark_blue);
	house.set_fill_color(Color::dark_blue);
	sw.attach(house);
	RectanglePPP2 door{ Point{tlWidth + 400, tlHeight + 550}, 150, 350 };
	door.set_color(Color::dark_cyan);
	door.set_fill_color(Color::dark_cyan);
	sw.attach(door);
	Open_polyline handle;
	handle.add(Point{ tlWidth + 410, tlHeight + 750 });
	handle.add(Point{ tlWidth + 430, tlHeight + 750 });
	handle.add(Point{ tlWidth + 430, tlHeight + 780 });
	handle.add(Point{ tlWidth + 410, tlHeight + 780 });
	handle.set_color(Color::black);
	handle.set_style(Line_style(Line_style::solid, 6));
	sw.attach(handle);
	RectanglePPP2 window{ Point{tlWidth + 100, tlHeight + 500}, 200, 200 };
	window.set_color(Color::dark_magenta);
	window.set_fill_color(Color::white);
	sw.attach(window);
	Line windowFrameHor{ Point{tlWidth + 100, tlHeight + 580}, Point{tlWidth + 300, tlHeight + 580} };
	windowFrameHor.set_color(Color::dark_magenta);
	windowFrameHor.set_style(Line_style(Line_style::solid, 10));
	sw.attach(windowFrameHor);
	Line windowFrameVert{ Point{tlWidth + 200, tlHeight + 580}, Point{tlWidth + 200, tlHeight + 700} };
	windowFrameVert.set_color(Color::dark_magenta);
	windowFrameVert.set_style(Line_style(Line_style::solid, 10));
	sw.attach(windowFrameVert);

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
