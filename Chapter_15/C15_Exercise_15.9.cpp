/* Exercise 15.9 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C15_Exercise_15.9.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	constexpr int nBars = 20;									// number of bars
	constexpr int windowLength = 1280;
	constexpr int windowHeight = 1024;
	const string fileName = "C15_Exercise_15.9_test.csv";
	ifstream ifs;
	ifs.open(fileName);
	if (!ifs) error("Error. Can't open input file: ", fileName);
	vector<MeanHeight> heightsCm;
	for (char ch = '0'; ch != '\n'; ) ifs.get(ch);
	for (MeanHeight mh; ifs >> mh; ) heightsCm.push_back(mh);

	int nMens = 0;												// number of mens
	int nWomens = 0;											// number of womens
	for (int i = 0; i < heightsCm.size(); i++) {
		if (heightsCm[i].s == 'm') nMens++;
		else if (heightsCm[i].s == 'f') nWomens++;
	}
	int nYearsPerBarMen = nMens / nBars;						// number of years in one bar for mens
	int nYearsPerBarWomen = nWomens / nBars;					// number of years in one bar for womens

	// graph for mens
	Simple_window sw{ Point{ 80, 0 }, windowLength, windowHeight, "Bar" };
	Point origin{ 100, windowHeight - 124 };
	Bar bar1{ origin, 1000, 800, "Mean heights of mens (cm)", Color::invisible, 50 };
	sw.attach(bar1);

	ostringstream oss;
	int counter = nYearsPerBarMen;
	double meanHeight = 0;
	for (int i = 0; i < heightsCm.size(); i++) {
		if (heightsCm[i].s != 'm') continue;
		counter = (counter >= nYearsPerBarMen) ? 1 : counter + 1;
		if (counter == 1) {
			oss.str("");
			oss << heightsCm[i].y << '-';
			meanHeight = 0;
		}
		meanHeight += heightsCm[i].h;
		if (counter == nYearsPerBarMen) {
			oss << heightsCm[i].y;
			bar1.add(meanHeight / counter, oss.str(), Color::dark_yellow);
		}
	}
	if (counter < nYearsPerBarMen) {
		oss << heightsCm[heightsCm.size() - 1].y;
		bar1.add(meanHeight / counter, oss.str(), Color::dark_yellow);
	}
	sw.wait_for_button();
	sw.detach(bar1);

	// graph for womens
	Bar bar2{ origin, 1000, 800, "Mean heights of womens (cm)", Color::invisible, 50 };
	sw.attach(bar2);

	counter = nYearsPerBarWomen;
	meanHeight = 0;
	for (int i = 0; i < heightsCm.size(); i++) {
		if (heightsCm[i].s != 'f') continue;
		counter = (counter >= nYearsPerBarWomen) ? 1 : counter + 1;
		if (counter == 1) {
			oss.str("");
			oss << heightsCm[i].y << '-';
			meanHeight = 0;
		}
		meanHeight += heightsCm[i].h;
		if (counter == nYearsPerBarWomen) {
			oss << heightsCm[i].y;
			bar2.add(meanHeight / counter, oss.str(), Color::dark_cyan);
		}
	}
	if (counter < nYearsPerBarWomen) {
		oss << heightsCm[heightsCm.size() - 1].y;
		bar2.add(meanHeight / counter, oss.str(), Color::dark_cyan);
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

// assume format:
// "Country","ISO","Sex","Year of birth","Mean height (cm)","Mean height lower 95% uncertainty interval (cm)","Mean height upper 95% uncertainty interval (cm)"
istream& Graph_lib::operator>>(istream& is, MeanHeight& mh)
{
	char ch = 0;
	char comma1 = 0;
	char comma2 = 0;
	char comma3 = 0;
	char comma4 = 0;
	char quote = 0;
	string country;
	string ISO;
	string sex;
	double mhl = 0.0;											// mean height lower 95% uncertainty interval (cm)
	double mhu = 0.0;											// mean height upper 95% uncertainty interval (cm)
	MeanHeight temp;
	// get "Country"
	if (is >> quote) {
		if (quote != '"') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else return is;
	for (is.get(ch); is; is.get(ch)) {
		if (ch == '"') break;
		else country += ch;
	}
	if (!is) return is;
	// get "ISO"
	if (is >> comma1 >> quote) {
		if (comma1 != ',' || quote != '"') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else return is;
	for (is.get(ch); is; is.get(ch)) {
		if (ch == '"') break;
		else ISO += ch;
	}
	if (!is) return is;
	// get "Sex"
	if (is >> comma1 >> quote) {
		if (comma1 != ',' || quote != '"') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else return is;
	for (is.get(ch); is; is.get(ch)) {
		if (ch == '"') break;
		else sex += ch;
	}
	if (!is) return is;
	// get "Year of birth","Mean height (cm)","Mean height lower 95% uncertainty interval (cm)","Mean height upper 95% uncertainty interval (cm)"
	if (is >> comma1 >> temp.y >> comma2 >> temp.h >> comma3 >> mhl >> comma4 >> mhu) {
		if (comma1 != ',' || comma2 != ',' || comma3 != ',' || comma4 != ',') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else return is;
	if (sex == "Men") temp.s = 'm';
	else if (sex == "Women") temp.s = 'f';
	mh = temp;
	return is;
}
