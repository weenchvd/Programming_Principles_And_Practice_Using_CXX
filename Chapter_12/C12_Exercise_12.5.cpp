/* Exercise 12.5 */

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
	constexpr int shift = 20;
	constexpr double screenWidthInch = 27.45;
	constexpr double screenWidth = 3840;
	constexpr int windowWidth = 640;
	constexpr int windowHeight = 480;
	constexpr int rectangleWidth = windowWidth * 2 / 3;
	constexpr int rectangleHeight = windowHeight * 3 / 4;
	constexpr int frameThickness = screenWidth / screenWidthInch * 0.25;
	constexpr int frameWidth = rectangleWidth + frameThickness + 2;
	constexpr int frameHeight = rectangleHeight + frameThickness + 2;
	Simple_window sw{ Point{ 80, 0 }, windowWidth, windowHeight, "Red frame" };
	RectanglePPP2 rectangle{ Point { 0, 0 }, rectangleWidth, rectangleHeight };
	rectangle.set_fill_color(Color::black);
	rectangle.set_color(Color::green);
	rectangle.move(frameThickness + shift, frameThickness + shift);
	RectanglePPP2 frame{ Point{ 0, 0 }, frameWidth, frameHeight };
	frame.set_style(Line_style(Line_style::solid, frameThickness));
	frame.set_color(Color::red);
	frame.move(frameThickness / 2 + shift, frameThickness / 2 + shift);
	sw.attach(rectangle);
	sw.attach(frame);

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
