/* Exercise 15.8 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C15_Exercise_15.8.h"

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
	const string fileName = "C15_Exercise_15.8_test.txt";
	ifstream ifs;
	ifs.open(fileName);
	if (!ifs) error("Error. Can't open input file: ", fileName);
	vector<HeightDistribution> distr;
	for (HeightDistribution hd; ifs >> hd; ) {
		distr.push_back(hd);
		char ch;
		for (ifs >> ch; ch != '('; ifs >> ch);
		if (ch == '(') ifs.unget();
	}

	Simple_window sw{ Point{ 80, 0 }, windowLength, windowHeight, "Bar" };
	Point origin{ 100, windowHeight - 124 };
	Bar bar1{ origin, 1000, 800, "Heights", Color::invisible, 40 };
	sw.attach(bar1);

	ostringstream oss;
	for (int i = 0; i < distr.size(); i++) {
		oss.str("");
		oss << distr[i].h;
		bar1.add(distr[i].n, oss.str(), Color::dark_yellow);
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

// intervalScale  is measured in percent (from 1 to 99)
Bar::Bar(Point orig, int width, int height, const string& label, Color borderColor, int intervalScale)
	: o{ orig }, lab{ label }, w{ width }, h{ height },
	bc{ borderColor }, max{ 0 },
	fc{ Color::black }, fnt{ Font::helvetica }, fs{ 14 },
	ac{ Color::black }, nw{ 5 }, nNotches{ 10 }
{
	if (intervalScale <= 0 || intervalScale >= 100) is = 30;
	else is = double(intervalScale) / 100;
}

void Bar::add(double barValue, const string& barLabel, Color barColor)
{
	if (barValue >= 0) {
		if (max < barValue) max = barValue;
		v.push_back(barValue);
		l.push_back(barLabel);
		c.push_back(barColor);
	}
}

void Bar::draw_lines() const
{
	constexpr int labelIndentation = 15;
	constexpr int labelAngle = 315;
	const int nBars = v.size();
	const int intervalWidth = double(w) / nBars * is;
	const int barWidth = double(w) / nBars * (1.0 - is);
	Point p{ o };
	p.x -= intervalWidth / 2;
	for (int i = 0; i < nBars; i++) {
		// draw bars
		p.x += intervalWidth;									// top left point of the bar
		p.y -= int(h * v[i] / max);								// top left point of the bar
		int barHeight = o.y - p.y;
		fl_color(c[i].as_int());
		fl_rectf(p.x, p.y, barWidth, barHeight);
		if (bc.visibility()) {
			fl_color(bc.as_int());
			fl_rect(p.x, p.y, barWidth, barHeight);
		}
		p.y = o.y;
		// draw bar labels
		Point pLabel{ p.x, p.y + labelIndentation };
		fl_color(fc.as_int());
		fl_font(fnt.as_int(), fs);
		fl_draw(labelAngle, l[i].c_str(), pLabel.x, pLabel.y);
		p.x += barWidth;
	}
	// draw graph label
	fl_color(fc.as_int());
	fl_font(fnt.as_int(), fs + 6);
	fl_draw(lab.c_str(), o.x + w / 2 - fl_width(lab.c_str()) / 2, o.y - h - labelIndentation);
	// draw axes
	fl_color(ac.as_int());
	fl_line(o.x, o.y, o.x + w, o.y);
	fl_line(o.x, o.y, o.x, o.y - h);
	// draw notches and values
	p = o;
	double distance = double(h) / nNotches;
	double notchValue = max / nNotches;
	ostringstream oss;
	fl_font(fnt.as_int(), fs);
	for (int i = 0; i < nNotches; i++) {
		p.y -= distance;
		fl_line(p.x, p.y, p.x - nw, p.y);
		oss.str("");
		oss << notchValue;
		string notchLabel = oss.str();
		fl_draw(notchLabel.c_str(), p.x - fl_width(notchLabel.c_str()) - (nw + labelIndentation / 3),
			p.y + labelIndentation / 3);
		notchValue += max / nNotches;
	}
}

// assume format: (height, number_of_people)
istream& Graph_lib::operator>>(istream& is, HeightDistribution& hd)
{
	char ch1 = 0;
	char ch2 = 0;
	char ch3 = 0;
	HeightDistribution d;
	if (is >> ch1 >> d.h >> ch2 >> d.n >> ch3) {
		if (ch1 != '(' || ch2 != ',' || ch3 != ')') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else return is;
	hd = d;
	return is;
}
