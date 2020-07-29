/* Exercise 15.6 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C15_Exercise_15.6.h"

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

	Simple_window sw{ Point{ 80, 0 }, windowLength, windowHeight, "Bar" };

	vector<double> values1;
	values1.push_back(94.0);
	values1.push_back(44.5);
	values1.push_back(0.9);
	values1.push_back(15.6);
	values1.push_back(87.0);
	values1.push_back(22.0);
	values1.push_back(37.5);
	values1.push_back(41.1);

	Point origin{ windowLength / 20, windowHeight * 19 / 20 };
	Axis x1{ Axis::Orientation::x, origin, windowLength * 3 / 4 * (int(values1.size()) + 1) / int(values1.size()) };
	Axis y1{ Axis::Orientation::y, origin, windowHeight * 3 / 4 * 11 / 10 , 11, "Value" };
	x1.set_color(Color::dark_blue);
	y1.set_color(Color::dark_blue);
	sw.attach(x1);
	sw.attach(y1);

	Bar b1{ values1, origin, windowLength * 3 / 4, windowHeight * 3 / 4 };
	b1.set_color(Color::black);
	b1.set_fill_color(Color::dark_red);
	sw.attach(b1);
	sw.wait_for_button();
	sw.detach(b1);
	sw.detach(x1);
	sw.detach(y1);


	vector<double> values2;
	values2.push_back(0.7885);
	values2.push_back(0.999789);
	values2.push_back(0.456456);
	values2.push_back(0.1245);
	values2.push_back(0.06);
	values2.push_back(0.433);
	values2.push_back(0.7);
	values2.push_back(0.81);
	values2.push_back(0.33);
	values2.push_back(0.15);
	values2.push_back(0.2);
	values2.push_back(0.19);
	values2.push_back(0.44);
	values2.push_back(0.68);
	values2.push_back(0.78);
	values2.push_back(0.41);
	values2.push_back(0.13);

	Axis x2{ Axis::Orientation::x, origin, windowLength * 3 / 4 * (int(values2.size()) + 1) / int(values2.size()) };
	Axis y2{ Axis::Orientation::y, origin, windowHeight * 3 / 4 * 11 / 10 , 11, "Value" };
	x2.set_color(Color::black);
	y2.set_color(Color::black);
	sw.attach(x2);
	sw.attach(y2);

	Bar b2{ values2, origin, windowLength * 3 / 4, windowHeight * 3 / 4 };
	b2.set_color(Color::black);
	b2.set_fill_color(Color::dark_green);
	sw.attach(b2);


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

Bar::Bar(const vector<double>& values, Point orig, int xLength, int yLength)
{
	constexpr double intervalScale = 0.3;
	const int nBars = values.size();							// number of bars
	const int intervalLength = double(xLength) / nBars * intervalScale;
	const int barLength = double(xLength) / nBars * (1.0 - intervalScale);
	double maxValue = 0;
	for (int i = 0; i < nBars; i++) {
		if (maxValue < values[i]) maxValue = values[i];
	}
	Point p{ orig };
	for (int i = 0; i < nBars; i++) {
		p.x += intervalLength;									// top left point
		p.y -= int(yLength * values[i] / maxValue);				// top left point
		add(p);
		p.x += barLength;										// bottom right point
		p.y = orig.y;											// bottom right point
		add(p);
	}
}

void Bar::draw_lines() const
{
	for (int i = 1; i < number_of_points(); i++) {
		int width = point(i).x - point(i - 1).x;
		int height = point(i).y - point(i - 1).y;
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_rectf(point(i - 1).x, point(i - 1).y, width, height);
		}
		if (color().visibility()) {
			fl_color(color().as_int());
			fl_rect(point(i - 1).x, point(i - 1).y, width, height);
		}
	}
}
