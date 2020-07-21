/* Exercise 14.1 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C14_Exercise_14.1.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Smiley and Frowny" };

	Smiley sm{ Point{300, 250}, 100 };
	sw.attach(sm);
	Frowny fr{ Point{900, 250}, 100 };
	sw.attach(fr);
	SmileyHat smh{ Point{300, 750}, 100 };
	sw.attach(smh);
	FrownyHat frh{ Point {900, 750}, 100 };
	sw.attach(frh);

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

void Smiley::draw_lines() const
{
	if (color().visibility()) {
		Circle::draw_lines();
		const int radius = Circle::radius();
		const Point center = Circle::center();
		const int xShiftEye = radius / 2;		// x distance from the center to the eye
		const int yShiftEye = radius / 4;		// y distance from the center to the eye
		const int eyeRadius = xShiftEye / 2.5;
		const int mouthRadius = radius - radius / 4;
		const Point leftEye{ center.x - xShiftEye - eyeRadius, center.y - yShiftEye - eyeRadius };
		const Point rightEye{ center.x + xShiftEye - eyeRadius, center.y - yShiftEye - eyeRadius };
		const Point mouth{ center.x - mouthRadius, center.y - mouthRadius };
		fl_arc(leftEye.x, leftEye.y, eyeRadius + eyeRadius, eyeRadius + eyeRadius, 0, 360);
		fl_arc(rightEye.x, rightEye.y, eyeRadius + eyeRadius, eyeRadius + eyeRadius, 0, 360);
		fl_arc(mouth.x, mouth.y, mouthRadius + mouthRadius, mouthRadius + mouthRadius, 210, 330);
	}
}

void Frowny::draw_lines() const
{
	if (color().visibility()) {
		Circle::draw_lines();
		const int radius = Circle::radius();
		const Point center = Circle::center();
		const int xShiftEye = radius / 2;		// x distance from the center to the eye
		const int yShiftEye = radius / 4;		// y distance from the center to the eye
		const int eyeRadius = xShiftEye / 2.5;
		const int mouthRadius = radius - radius / 4;
		const Point leftEye{ center.x - xShiftEye - eyeRadius, center.y - yShiftEye - eyeRadius };
		const Point rightEye{ center.x + xShiftEye - eyeRadius, center.y - yShiftEye - eyeRadius };
		const Point mouth{ center.x - mouthRadius, center.y + radius - mouthRadius };
		fl_arc(leftEye.x, leftEye.y, eyeRadius + eyeRadius, eyeRadius + eyeRadius, 0, 360);
		fl_arc(rightEye.x, rightEye.y, eyeRadius + eyeRadius, eyeRadius + eyeRadius, 0, 360);
		fl_arc(mouth.x, mouth.y, mouthRadius + mouthRadius, mouthRadius + mouthRadius, 30, 150);
	}
}

void SmileyHat::draw_lines() const
{
	if (color().visibility()) {
		Smiley::draw_lines();
		const int radius = Circle::radius();
		const Point center = Circle::center();
		const Point hatBottomCenter{ center.x, center.y - radius * 3 / 4 };
		fl_rectf(hatBottomCenter.x - radius * 5 / 4, hatBottomCenter.y - 5, radius * 5 / 4 * 2, 5);
		fl_rectf(hatBottomCenter.x - radius * 3 / 4, hatBottomCenter.y - 5 - 100, radius * 3 / 4 * 2, 100);
	}
}

void FrownyHat::draw_lines() const
{
	if (color().visibility()) {
		Frowny::draw_lines();
		const int radius = Circle::radius();
		const Point center = Circle::center();
		const Point hatBottomCenter{ center.x, center.y - radius * 3 / 4 };
		fl_rectf(hatBottomCenter.x - radius * 5 / 4, hatBottomCenter.y - 5, radius * 5 / 4 * 2, 5);
		fl_rectf(hatBottomCenter.x - radius * 3 / 4, hatBottomCenter.y - 5 - 100, radius * 3 / 4 * 2, 100);
	}
}
