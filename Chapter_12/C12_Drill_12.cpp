/* Drill 12 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C12_Drill_12.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;

int main()
try {
    Point tl(150, 100);    // top-left corner of our window

    Simple_window win(tl, 640, 480, "Window1");

    Axis xa(Axis::x, Point(20, 350), 280, 10, "x axis"); // make an Axis
    xa.set_color(Color::dark_blue);
    xa.label.set_color(Color::dark_red);
    win.attach(xa);                      // attach xa to the window, win

    Axis ya(Axis::y, Point(20, 350), 280, 10, "y axis");
    ya.set_color(Color::dark_blue);           // choose a color
    ya.label.set_color(Color::dark_red); // choose a color for the text
    win.attach(ya);

    Function sine(sin, 0, 100, Point(20, 150), 1000, 50, 50);    // sine curve
    win.attach(sine);
    sine.set_color(Color::dark_green);         // we changed our mind about sine's color

    PolygonPPP2 poly;                        // a polygon, a PolygonPPP2 is a kind of Shape
    poly.add(Point(300, 200));            // three points makes a triangle
    poly.add(Point(350, 100));
    poly.add(Point(400, 200));

    poly.set_color(Color::red);
    poly.set_style(Line_style::dash);
    win.attach(poly);

    RectanglePPP2 r(Point(200, 200), 100, 50);// top-left corner, width, height
    win.attach(r);

    Closed_polyline poly_rect;
    poly_rect.add(Point(100, 50));
    poly_rect.add(Point(200, 50));
    poly_rect.add(Point(200, 100));
    poly_rect.add(Point(100, 100));
    poly_rect.add(Point(50, 75));
    win.attach(poly_rect);

    r.set_fill_color(Color::yellow);     // color the inside of the rectangle
    poly.set_style(Line_style(Line_style::dash, 4));
    poly_rect.set_style(Line_style(Line_style::dash, 2));
    poly_rect.set_fill_color(Color::green);

    Text t(Point(150, 150), "Hello, graphical world! ");
    win.attach(t);
    t.set_font(Font::times_bold);
    t.set_font_size(20);

    Image ii(Point(100, 50), "C12_Drill_12_Fry.jpg");
    win.attach(ii);
    ii.move(50, 200);

    Circle c(Point(100, 200), 50);
    EllipsePPP2 e(Point(100, 200), 75, 25);
    e.set_color(Color::dark_red);
    Mark m(Point(100, 200), 'x');

    ostringstream oss;
    oss << "screen size: " << x_max() << "*" << y_max()
        << "; window size: " << win.x_max() << "*" << win.y_max();
    Text sizes(Point(100, 20), oss.str());

    Image cal(Point(300, 150), "C12_Drill_12_snow_cpp.gif"); // 320*240 pixel gif
    cal.set_mask(Point(40, 40), 200, 150);       // display center part of image
    cal.move(150, 150);

    win.attach(c);
    win.attach(m);
    win.attach(e);

    win.attach(sizes);
    win.attach(cal);

    win.set_label("Canvas #12");
    win.wait_for_button();               // Display!
	return 0;
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "Error. Exception\n";
	return 2;
}
