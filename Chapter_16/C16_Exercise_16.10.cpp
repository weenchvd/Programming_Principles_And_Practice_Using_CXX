/* Exercise 16.10 */

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
#include"C16_Exercise_16.10.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Functions win{ Point{ 80, 0 }, windowWidth, windowHeight, "Functions" };
	

	win.wait_for_button();
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

Functions::Functions(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	ibMin{ Point{ leftIndentation * 2 / 5, defaultButtonHeigth },
		leftIndentation * 3 / 5, defaultButtonHeigth, "Min x:" },
	ibMax{ Point{ leftIndentation * 2 / 5, defaultButtonHeigth * 2 },
		leftIndentation * 3 / 5, defaultButtonHeigth, "Max x:" },
	menuFunction{ Point{ leftIndentation * 2 / 5, defaultButtonHeigth * 3 },
		leftIndentation * 3 / 5, defaultButtonHeigth, Menu::Kind::vertical, "" },
	buttonMenuFunction{ Point{ leftIndentation * 2 / 5, defaultButtonHeigth * 3 },
		leftIndentation * 3 / 5, defaultButtonHeigth, "Function",
		[](Address, Address pw) { reference_to<Functions>(pw).MenuFunctionPressed(); } },
	buttonQuit{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<Functions>(pw).quit(); } },
	quitPushed{ false }
{
	xAxis.set_color(Color::black);
	attach(xAxis);
	yAxis.set_color(Color::black);
	attach(yAxis);
	textTop.set_font(defaultFont);
	textTop.set_font_size(defaultFontSize);
	textTop.set_color(Color::black);
	attach(textTop);
	textBottom.set_font(defaultFont);
	textBottom.set_font_size(defaultFontSize);
	textBottom.set_color(Color::black);
	attach(textBottom);
	textLeft.set_font(defaultFont);
	textLeft.set_font_size(defaultFontSize);
	textLeft.set_color(Color::black);
	attach(textLeft);
	textRight.set_font(defaultFont);
	textRight.set_font_size(defaultFontSize);
	textRight.set_color(Color::black);
	attach(textRight);
	attach(ibMin);
	attach(ibMax);
	menuFunction.attach(new Button{ Point {0, 0}, 0, 0, "sin(x)",
		[](Address, Address pw) { reference_to<Functions>(pw).DrawSin(); } });
	menuFunction.attach(new Button{ Point {0, 0}, 0, 0, "cos(x)",
		[](Address, Address pw) { reference_to<Functions>(pw).DrawCos(); } });
	menuFunction.attach(new Button{ Point {0, 0}, 0, 0, "tg(x)",
		[](Address, Address pw) { reference_to<Functions>(pw).DrawTan(); } });
	menuFunction.attach(new Button{ Point {0, 0}, 0, 0, "ln(x)",
		[](Address, Address pw) { reference_to<Functions>(pw).DrawLog(); } });
	menuFunction.attach(new Button{ Point {0, 0}, 0, 0, "log2(x)",
		[](Address, Address pw) { reference_to<Functions>(pw).DrawLog2(); } });
	menuFunction.attach(new Button{ Point {0, 0}, 0, 0, "log10(x)",
		[](Address, Address pw) { reference_to<Functions>(pw).DrawLog10(); } });
	menuFunction.attach(new Button{ Point {0, 0}, 0, 0, "x^2",
		[](Address, Address pw) { reference_to<Functions>(pw).DrawSquare(); } });
	menuFunction.attach(new Button{ Point {0, 0}, 0, 0, "x^3",
		[](Address, Address pw) { reference_to<Functions>(pw).DrawCubic(); } });
	menuFunction.attach(new Button{ Point {0, 0}, 0, 0, "e^x",
		[](Address, Address pw) { reference_to<Functions>(pw).DrawExp(); } });
	attach(menuFunction);
	menuFunction.hide();
	attach(buttonMenuFunction);
	attach(buttonQuit);
}

bool Functions::wait_for_button()
{
	show();
	quitPushed = false;
	while (!quitPushed) Fl::wait();
	Fl::redraw();
	return quitPushed;
}

bool Functions::GetRange(double& xMin, double& xMax)
{
	istringstream iss;
	iss.str(ibMin.get_string());
	if (!(iss >> xMin)) return false;
	iss.clear();
	iss.str(ibMax.get_string());
	if (!(iss >> xMax)) return false;
	return true;
}

void Functions::CalculateScale(Fct function, double xMin, double xMax, double& yMin, double& yMax, double& xScale, double& yScale)
{
	if (xMin == 0.0 && xMax == 0.0) {
		xScale = 1.0;
		yScale = 1.0;
		return;
	}
	else if (xMin == 0.0) xScale = xAxisSize / 2 / abs(xMax);
	else if (xMax == 0.0) xScale = xAxisSize / 2 / abs(xMin);
	else xScale = min(xAxisSize / 2 / abs(xMin), xAxisSize / 2 / abs(xMax));
	double step = (xMax - xMin) / nPoints;
	double min = DBL_MAX;
	double max = DBL_MIN;
	for (double x = xMin; x < xMax; x += step) {
		double y = function(x);
		if (y < min) min = y;
		if (y > max) max = y;
	}
	yMin = min;
	yMax = max;
	if (min == 0.0 && max == 0.0) yScale = 1.0;
	else if (min == 0.0) yScale = yAxisSize / 2 / abs(max);
	else if (max == 0.0) yScale = yAxisSize / 2 / abs(min);
	else yScale = min(yAxisSize / 2 / abs(min), yAxisSize / 2 / abs(max));
}

void Functions::SetAxisLabels(double xAbsoluteValue, double yAbsoluteValue)
{
	ostringstream oss;
	if (!(oss << xAbsoluteValue)) return;
	textLeft.set_label("-" + oss.str());
	textRight.set_label(oss.str());
	oss.str("");
	if (!(oss << yAbsoluteValue)) return;
	textBottom.set_label("-" + oss.str());
	textTop.set_label(oss.str());
}

void Functions::Draw(Fct function)
{
	if (pf != nullptr) {
		detach(*pf);
		delete pf;
		pf = nullptr;
	}
	double xMin;
	double xMax;
	if (!GetRange(xMin, xMax)) return;
	double yMin;
	double yMax;
	double xScale;
	double yScale;
	CalculateScale(function, xMin, xMax, yMin, yMax, xScale, yScale);
	pf = new Function{ function, xMin, xMax, origin, nPoints, xScale, yScale };
	pf->set_color(Color::magenta);
	attach(*(pf));
	SetAxisLabels(max(abs(xMin), abs(xMax)), max(abs(yMin), abs(yMax)));
	menuFunction.hide();
	buttonMenuFunction.show();
	redraw();
}

void Functions::quit()
{
	quitPushed = true;
	hide();
}

#include <FL/Fl_Output.H>
string Graph_lib::In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	string s;
	return s.assign(pi.value());
}
