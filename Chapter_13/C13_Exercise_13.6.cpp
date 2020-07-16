/* Exercise 13.6 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.6.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	constexpr int fontSize = 20;
	constexpr int radius = 5;
	
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Box" };

	Box window{ Point{300, 100}, radius, fontSize, "Window" };
	sw.attach(window);

	Box simpleWindow{ Point{ window.GetTopLeft().x, window.GetTopLeft().y + 200},
		radius, fontSize, "Simple_window" };
	sw.attach(simpleWindow);
	int xShiftSimpleWindow = window.GetBottomCenter().x - simpleWindow.GetTopCenter().x;
	simpleWindow.move(xShiftSimpleWindow, 0);
	Arrow aSimpleWindow{ simpleWindow.GetTopCenter(), window.GetBottomCenter() };
	sw.attach(aSimpleWindow);

	Box lineStyle{ Point{ window.GetTopLeft().x + window.GetWidth() + 100, window.GetTopLeft().y },
		radius, fontSize, "Line_style" };
	sw.attach(lineStyle);

	Box color{ Point{ lineStyle.GetTopLeft().x + lineStyle.GetWidth() + 100, lineStyle.GetTopLeft().y}, 
		radius, fontSize, "Color" };
	sw.attach(color);

	Box shape{ Point{simpleWindow.GetTopLeft().x + simpleWindow.GetWidth() + 100,
		simpleWindow.GetTopLeft().y - 30}, radius, fontSize, "Shape" };
	sw.attach(shape);

	Box point{ Point{shape.GetTopLeft().x + shape.GetWidth() + 100, simpleWindow.GetTopLeft().y},
		radius, fontSize, "Point" };
	sw.attach(point);

	Box axis{ Point{shape.GetTopLeft().x, shape.GetTopLeft().y + 200 }, radius, fontSize, "Axis" };
	sw.attach(axis);
	int xShiftAxis = shape.GetBottomCenter().x - axis.GetTopCenter().x;
	axis.move(xShiftAxis, 0);
	Arrow aAxis{ axis.GetTopCenter(), shape.GetBottomCenter() };
	sw.attach(aAxis);

	Box polygon{ axis.GetTopLeft(), radius, fontSize, "Polygon" };
	sw.attach(polygon);
	int xShiftPolygon = -(polygon.GetWidth() + 15);
	polygon.move(xShiftPolygon, 0);
	Arrow aPolygon{ polygon.GetTopCenter(),
		{ shape.GetBottomCenter().x - ((shape.GetWidth() - shape.GetRadius() * 2) / 2 / 3),
		shape.GetBottomCenter().y} };
	sw.attach(aPolygon);

	Box lines{ polygon.GetTopLeft(), radius, fontSize, "Lines" };
	sw.attach(lines);
	int xShiftLines = -(lines.GetWidth() + 15);
	lines.move(xShiftLines, 0);
	Arrow aLines{ lines.GetTopCenter(),
		{ shape.GetBottomCenter().x - ((shape.GetWidth() - shape.GetRadius() * 2) / 2 / 3 * 2),
		shape.GetBottomCenter().y} };
	sw.attach(aLines);

	Box line{ lines.GetTopLeft(), radius, fontSize, "Line" };
	sw.attach(line);
	int xShiftLine = -(line.GetWidth() + 15);
	line.move(xShiftLine, 0);
	Arrow aLine{ line.GetTopCenter(),
		{ shape.GetBottomCenter().x - ((shape.GetWidth() - shape.GetRadius() * 2) / 2 / 3 * 3),
		shape.GetBottomCenter().y} };
	sw.attach(aLine);

	Box rectangle{ axis.GetTopLeft(), radius, fontSize, "Rectangle" };
	sw.attach(rectangle);
	int xShiftRectangle = axis.GetWidth() + 15;
	rectangle.move(xShiftRectangle, 0);
	Arrow aRectangle{ rectangle.GetTopCenter(),
		{ shape.GetBottomCenter().x + ((shape.GetWidth() - shape.GetRadius() * 2) / 2 / 3),
		shape.GetBottomCenter().y} };
	sw.attach(aRectangle);

	Box text{ rectangle.GetTopLeft(), radius, fontSize, "Text" };
	sw.attach(text);
	int xShiftText = rectangle.GetWidth() + 15;
	text.move(xShiftText, 0);
	Arrow aText{ text.GetTopCenter(),
		{ shape.GetBottomCenter().x + ((shape.GetWidth() - shape.GetRadius() * 2) / 2 / 3 * 2),
		shape.GetBottomCenter().y} };
	sw.attach(aText);

	Box image{ text.GetTopLeft(), radius, fontSize, "Image" };
	sw.attach(image);
	int xShiftImage = text.GetWidth() + 15;
	image.move(xShiftImage, 0);
	Arrow aImage{ image.GetTopCenter(),
		{ shape.GetBottomCenter().x + ((shape.GetWidth() - shape.GetRadius() * 2) / 2 / 3 * 3),
		shape.GetBottomCenter().y} };
	sw.attach(aImage);


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

Box::Box(Point p, int radius, int fontSize, const string& s)
	: r{ radius }, fnt_sz{ fontSize }, lab{ s } , fnt{ Font::helvetica_bold }
{
	constexpr int minRadius = 5;
	constexpr int minFontSize = 12;
	constexpr double letterScaleWidth = 0.7;
	if (radius < minRadius) r = minRadius;
	if (fontSize < minFontSize) fnt_sz = minFontSize;
	w = r * 2 + fnt_sz * letterScaleWidth * s.size();
	h = r * 2 + fnt_sz;
	add(p);
}

void Box::draw_lines() const
{
	constexpr int indentation = 7;
	Point p = point(0);
	fl_arc(p.x, p.y, r + r, r + r, 90, 180);							// top left corner
	fl_arc(p.x + w - r * 2, p.y, r + r, r + r, 0, 90);					// top right corner
	fl_arc(p.x + w - r * 2, p.y + h - r * 2, r + r, r + r, 270, 360);	// bottom right corner
	fl_arc(p.x, p.y + h - r * 2, r + r, r + r, 180, 270);				// bottom left corner
	fl_line(p.x + r, p.y, p.x + w - r, p.y);							// top edge
	fl_line(p.x + w, p.y + r, p.x + w, p.y + h - r);					// right edge
	fl_line(p.x + r, p.y + h, p.x + w - r, p.y + h);					// bottom edge
	fl_line(p.x, p.y + r, p.x, p.y + h - r);							// left edge
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(fnt.as_int(), fnt_sz);
	fl_draw(lab.c_str(), point(0).x + indentation, point(0).y + h - indentation);
	fl_font(ofnt, osz);
}

Arrow::Arrow(Point from, Point to)
	: lineStart{ from }, lineEnd{ to }
{
	constexpr int arrowheadLength = 20;
	constexpr int arrowheadWidth = 12;
	int xLength = lineStart.x - lineEnd.x;
	int yLength = -(lineStart.y - lineEnd.y);
	double hypotenuse = sqrt(pow(xLength, 2) + pow(yLength, 2));
	double angleRadian{ 0 };
	if (xLength >= 0 && yLength >= 0 || xLength <= 0 && yLength >= 0) {		// 0 <= angle <= Pi
		angleRadian = acos(double(xLength) / hypotenuse);
	}
	else {																	// Pi < angle < 2*Pi
		angleRadian = -acos(double(xLength) / hypotenuse);
	}
	/*	point(0,0) is origin
		x' = xcos(angle) - ysin(angle);
		y' = xsin(angle) + ycos(angle);
	*/
	Point p2{ arrowheadLength, -arrowheadWidth / 2 };
	Point p3{ arrowheadLength, arrowheadWidth / 2 };
	arrowhead2.x = p2.x * cos(angleRadian) - p2.y * sin(angleRadian);
	arrowhead2.y = p2.x * sin(angleRadian) + p2.y * cos(angleRadian);
	arrowhead3.x = p3.x * cos(angleRadian) - p3.y * sin(angleRadian);
	arrowhead3.y = p3.x * sin(angleRadian) + p3.y * cos(angleRadian);
	arrowhead2.x += lineEnd.x;
	arrowhead2.y = -arrowhead2.y + lineEnd.y;
	arrowhead3.x += lineEnd.x;
	arrowhead3.y = -arrowhead3.y + lineEnd.y;
	add(lineStart);
	add(lineEnd);
	add(arrowhead2);
	add(arrowhead3);
}

void Arrow::draw_lines() const
{
	fl_line(lineStart.x, lineStart.y, lineEnd.x, lineEnd.y);
	fl_polygon(lineEnd.x, lineEnd.y, arrowhead2.x, arrowhead2.y, arrowhead3.x, arrowhead3.y);
}
