/* Exercise 15.10 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C15_Exercise_15.10.h"

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
	const string fileName = "C15_Exercise_15.10_test.txt";
	ifstream ifs;
	ifs.open(fileName);
	if (!ifs) error("Error. Can't open input file: ", fileName);
	vector<HeightWeight> hw;
	for (HeightWeight temp; ifs >> temp; ) {
		hw.push_back(temp);
		char ch;
		for (ifs >> ch; ch != '('; ifs >> ch);
		if (ch == '(') ifs.unget();
	}
	
	// graph for mens
	Simple_window sw{ Point{ 80, 0 }, windowLength, windowHeight, "DotGraph" };
	Point origin{ 100, windowHeight - 124 };

	DotGraph dg1{ origin, 1000, 800, "Workers", "Height (cm)", "Weight (kg)" };
	sw.attach(dg1);

	for (int i = 0; i < hw.size(); i++) {
		dg1.add(hw[i].h, hw[i].w);
	}

	sw.wait_for_button();
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

DotGraph::DotGraph(Point orig, int width, int height, const string& label,
	const string& xLabel, const string& yLabel)
	: o{ orig }, lab{ label }, w{ width }, h{ height },
	xmax{ 0 }, ymax{ 0 }, dr{ 3 },
	fc{ Color::black }, fnt{ Font::helvetica }, fs{ 14 }, xl{ xLabel }, yl{ yLabel },
	ac{ Color::black }, nw{ 5 }, nNotches{ 10 } { }

void DotGraph::add(double xValue, double yValue, Color dotColor)
{
	if (xValue >= 0 && yValue >= 0) {
		if (xmax < xValue) xmax = xValue;
		if (ymax < yValue) ymax = yValue;
		xv.push_back(xValue);
		yv.push_back(yValue);
		c.push_back(dotColor);
	}
}

void DotGraph::draw_lines() const
{
	const double xScale = w / xmax;
	const double yScale = h / ymax;
	const int nDots = xv.size();
	Point p;
	for (int i = 0; i < nDots; i++) {
		p = o;
		p.x += int(xv[i] * xScale);
		p.y -= int(yv[i] * yScale);
		fl_color(c[i].as_int());
		fl_begin_complex_polygon();
		fl_circle(p.x, p.y, dr);
		fl_end_complex_polygon();
	}
	// draw graph label
	fl_color(fc.as_int());
	fl_font(fnt.as_int(), fs + 6);
	fl_draw(lab.c_str(), o.x + w / 2 - fl_width(lab.c_str()) / 2, o.y - h - (fs + 10));
	// draw axes
	fl_color(ac.as_int());
	fl_line(o.x, o.y, o.x + w, o.y);
	fl_line(o.x, o.y, o.x, o.y - h);
	// draw axis labels
	fl_color(fc.as_int());
	fl_font(fnt.as_int(), fs + 2);
	fl_draw(xl.c_str(), o.x + w + fs, o.y + fs / 2);
	fl_draw(yl.c_str(), o.x - fl_width(yl.c_str()) / 2, o.y - h - (fs + 6));
	// draw notches and values
	ostringstream oss;
	p = o;
	double xDistance = double(w) / nNotches;
	double xNotchValue = xmax / nNotches;
	fl_font(fnt.as_int(), fs);
	for (int i = 0; i < nNotches; i++) {
		p.x += xDistance;
		fl_line(p.x, p.y, p.x, p.y + nw);
		oss.str("");
		oss << xNotchValue;
		string notchLabel = oss.str();
		fl_draw(notchLabel.c_str(), p.x - fl_width(notchLabel.c_str()) / 2, p.y + nw * 2 + fs);
		xNotchValue += xmax / nNotches;
	}
	p = o;
	double yDistance = double(h) / nNotches;
	double yNotchValue = ymax / nNotches;
	for (int i = 0; i < nNotches; i++) {
		p.y -= yDistance;
		fl_line(p.x, p.y, p.x - nw, p.y);
		oss.str("");
		oss << yNotchValue;
		string notchLabel = oss.str();
		fl_draw(notchLabel.c_str(), p.x - fl_width(notchLabel.c_str()) - (nw + fs), p.y + fs / 2);
		yNotchValue += ymax / nNotches;
	}
}

// assume format: (height, weight)
istream& Graph_lib::operator>>(istream& is, HeightWeight& hw)
{
	char ch1 = 0;
	char ch2 = 0;
	char ch3 = 0;
	HeightWeight temp;
	if (is >> ch1 >> temp.h >> ch2 >> temp.w >> ch3) {
		if (ch1 != '(' || ch2 != ',' || ch3 != ')') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else return is;
	hw = temp;
	return is;
}
