/* Exercise 13.5 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.5.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Circle, ellipse" };

	Circle circle{ Point{500, 300}, 200 };
	sw.attach(circle);
	ostringstream oss;
	oss << "Top left point (x,y): " << circle.point(0).x << "," << circle.point(0).y;
	oss << "; radius " << circle.radius();
	string sCPoint = oss.str();
	Text tCPoint{ Point{500, 30}, sCPoint };
	sw.attach(tCPoint);

	Point pCNorth = CircleNS::n(circle);
	oss.str("");
	oss << pCNorth.x << "," << pCNorth.y;
	string sCNorth = oss.str();
	Text tCNorth{ pCNorth, sCNorth };
	sw.attach(tCNorth);
	Mark mCNorth{ pCNorth, 'x' };
	sw.attach(mCNorth);

	Point pCSouth = CircleNS::s(circle);
	oss.str("");
	oss << pCSouth.x << "," << pCSouth.y;
	string sCSouth = oss.str();
	Text tCSouth{ pCSouth, sCSouth };
	sw.attach(tCSouth);
	Mark mCSouth{ pCSouth, 'x' };
	sw.attach(mCSouth);

	Point pCWest = CircleNS::w(circle);
	oss.str("");
	oss << pCWest.x << "," << pCWest.y;
	string sCWest = oss.str();
	Text tCWest{ pCWest, sCWest };
	sw.attach(tCWest);
	Mark mCWest{ pCWest, 'x' };
	sw.attach(mCWest);

	Point pCEast = CircleNS::e(circle);
	oss.str("");
	oss << pCEast.x << "," << pCEast.y;
	string sCEast = oss.str();
	Text tCEast{ pCEast, sCEast };
	sw.attach(tCEast);
	Mark mCEast{ pCEast, 'x' };
	sw.attach(mCEast);

	Point pCCenter = CircleNS::center(circle);
	oss.str("");
	oss << pCCenter.x << "," << pCCenter.y;
	string sCCenter = oss.str();
	Text tCCenter{ pCCenter, sCCenter };
	sw.attach(tCCenter);
	Mark mCCenter{ pCCenter, 'x' };
	sw.attach(mCCenter);

	Point pCNorthWest = CircleNS::nw(circle);
	oss.str("");
	oss << pCNorthWest.x << "," << pCNorthWest.y;
	string sCNorthWest = oss.str();
	Text tCNorthWest{ pCNorthWest, sCNorthWest };
	sw.attach(tCNorthWest);
	Mark mCNorthWest{ pCNorthWest, 'x' };
	sw.attach(mCNorthWest);

	Point pCSouthWest = CircleNS::sw(circle);
	oss.str("");
	oss << pCSouthWest.x << "," << pCSouthWest.y;
	string sCSouthWest = oss.str();
	Text tCSouthWest{ pCSouthWest, sCSouthWest };
	sw.attach(tCSouthWest);
	Mark mCSouthWest{ pCSouthWest, 'x' };
	sw.attach(mCSouthWest);

	Point pCNorthEast = CircleNS::ne(circle);
	oss.str("");
	oss << pCNorthEast.x << "," << pCNorthEast.y;
	string sCNorthEast = oss.str();
	Text tCNorthEast{ pCNorthEast, sCNorthEast };
	sw.attach(tCNorthEast);
	Mark mCNorthEast{ pCNorthEast, 'x' };
	sw.attach(mCNorthEast);

	Point pCSouthEast = CircleNS::se(circle);
	oss.str("");
	oss << pCSouthEast.x << "," << pCSouthEast.y;
	string sCSouthEast = oss.str();
	Text tCSouthEast{ pCSouthEast, sCSouthEast };
	sw.attach(tCSouthEast);
	Mark mCSouthEast{ pCSouthEast, 'x' };
	sw.attach(mCSouthEast);

	EllipsePPP2 ellipse{ Point{500, 800}, 300, 150 };
	sw.attach(ellipse);
	oss.str("");
	oss << "Top left point (x,y): " << ellipse.point(0).x << "," << ellipse.point(0).y;
	oss << "; width " << ellipse.major() * 2 << ", height " << ellipse.minor() * 2;
	string sEPoint = oss.str();
	Text tEPoint{ Point{500, 580}, sEPoint };
	sw.attach(tEPoint);

	Point pENorth = EllipseNS::n(ellipse);
	oss.str("");
	oss << pENorth.x << "," << pENorth.y;
	string sENorth = oss.str();
	Text tENorth{ pENorth, sENorth };
	sw.attach(tENorth);
	Mark mENorth{ pENorth, 'x' };
	sw.attach(mENorth);

	Point pESouth = EllipseNS::s(ellipse);
	oss.str("");
	oss << pESouth.x << "," << pESouth.y;
	string sESouth = oss.str();
	Text tESouth{ pESouth, sESouth };
	sw.attach(tESouth);
	Mark mESouth{ pESouth, 'x' };
	sw.attach(mESouth);

	Point pEWest = EllipseNS::w(ellipse);
	oss.str("");
	oss << pEWest.x << "," << pEWest.y;
	string sEWest = oss.str();
	Text tEWest{ pEWest, sEWest };
	sw.attach(tEWest);
	Mark mEWest{ pEWest, 'x' };
	sw.attach(mEWest);

	Point pEEast = EllipseNS::e(ellipse);
	oss.str("");
	oss << pEEast.x << "," << pEEast.y;
	string sEEast = oss.str();
	Text tEEast{ pEEast, sEEast };
	sw.attach(tEEast);
	Mark mEEast{ pEEast, 'x' };
	sw.attach(mEEast);

	Point pECenter = EllipseNS::center(ellipse);
	oss.str("");
	oss << pECenter.x << "," << pECenter.y;
	string sECenter = oss.str();
	Text tECenter{ pECenter, sECenter };
	sw.attach(tECenter);
	Mark mECenter{ pECenter, 'x' };
	sw.attach(mECenter);

	Point pENorthWest = EllipseNS::nw(ellipse);
	oss.str("");
	oss << pENorthWest.x << "," << pENorthWest.y;
	string sENorthWest = oss.str();
	Text tENorthWest{ pENorthWest, sENorthWest };
	sw.attach(tENorthWest);
	Mark mENorthWest{ pENorthWest, 'x' };
	sw.attach(mENorthWest);

	Point pESouthWest = EllipseNS::sw(ellipse);
	oss.str("");
	oss << pESouthWest.x << "," << pESouthWest.y;
	string sESouthWest = oss.str();
	Text tESouthWest{ pESouthWest, sESouthWest };
	sw.attach(tESouthWest);
	Mark mESouthWest{ pESouthWest, 'x' };
	sw.attach(mESouthWest);

	Point pENorthEast = EllipseNS::ne(ellipse);
	oss.str("");
	oss << pENorthEast.x << "," << pENorthEast.y;
	string sENorthEast = oss.str();
	Text tENorthEast{ pENorthEast, sENorthEast };
	sw.attach(tENorthEast);
	Mark mENorthEast{ pENorthEast, 'x' };
	sw.attach(mENorthEast);

	Point pESouthEast = EllipseNS::se(ellipse);
	oss.str("");
	oss << pESouthEast.x << "," << pESouthEast.y;
	string sESouthEast = oss.str();
	Text tESouthEast{ pESouthEast, sESouthEast };
	sw.attach(tESouthEast);
	Mark mESouthEast{ pESouthEast, 'x' };
	sw.attach(mESouthEast);

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

Point RectangleNS::n(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x + r.width() / 2, topLeft.y };
}

Point RectangleNS::s(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x + r.width() / 2, topLeft.y + r.height() };
}

Point RectangleNS::w(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x, topLeft.y + r.height() / 2 };
}

Point RectangleNS::e(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x + r.width(), topLeft.y + r.height() / 2 };
}

Point RectangleNS::center(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x + r.width() / 2, topLeft.y + r.height() / 2 };
}

Point RectangleNS::nw(const RectanglePPP2& r)
{
	return r.point(0);
}

Point RectangleNS::sw(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x, topLeft.y + r.height() };
}

Point RectangleNS::ne(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x + r.width(), topLeft.y };
}

Point RectangleNS::se(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x + r.width(), topLeft.y + r.height() };
}

Point GetPointOnCircle(Point center, int radius, int angleDegree)
{
	double angleRadian = angleDegree * M_PI / 180.0;
	int x = center.x + radius * cos(angleRadian);
	int y = center.y - radius * sin(angleRadian);
	return { x, y };
}

Point CircleNS::n(const Circle& c)
{
	return { c.center().x, c.center().y - c.radius() };
}

Point CircleNS::s(const Circle& c)
{
	return { c.center().x, c.center().y + c.radius() };
}

Point CircleNS::w(const Circle& c)
{
	return { c.center().x - c.radius(), c.center().y };
}

Point CircleNS::e(const Circle& c)
{
	return { c.center().x + c.radius(), c.center().y };
}

Point CircleNS::center(const Circle& c)
{
	return c.center();
}

Point CircleNS::nw(const Circle& c)
{
	return GetPointOnCircle(c.center(), c.radius(), 135);
}

Point CircleNS::sw(const Circle& c)
{
	return GetPointOnCircle(c.center(), c.radius(), 225);
}

Point CircleNS::ne(const Circle& c)
{
	return GetPointOnCircle(c.center(), c.radius(), 45);
}

Point CircleNS::se(const Circle& c)
{
	return GetPointOnCircle(c.center(), c.radius(), 315);
}

Point EllipseNS::n(const EllipsePPP2& e)
{
	return { e.center().x, e.center().y - e.minor() };
}

Point EllipseNS::s(const EllipsePPP2& e)
{
	return { e.center().x, e.center().y + e.minor() };
}

Point EllipseNS::w(const EllipsePPP2& e)
{
	return { e.center().x - e.major(), e.center().y };
}

Point EllipseNS::e(const EllipsePPP2& e)
{
	return { e.center().x + e.major(), e.center().y };
}

Point EllipseNS::center(const EllipsePPP2& e)
{
	return { e.center().x, e.center().y };
}

Point EllipseNS::nw(const EllipsePPP2& e)
{
	RectanglePPP2 r{ e.point(0), e.major() * 2, e.minor() * 2 };
	return RectangleNS::nw(r);
}

Point EllipseNS::sw(const EllipsePPP2& e)
{
	RectanglePPP2 r{ e.point(0), e.major() * 2, e.minor() * 2 };
	return RectangleNS::sw(r);
}

Point EllipseNS::ne(const EllipsePPP2& e)
{
	RectanglePPP2 r{ e.point(0), e.major() * 2, e.minor() * 2 };
	return RectangleNS::ne(r);
}

Point EllipseNS::se(const EllipsePPP2& e)
{
	RectanglePPP2 r{ e.point(0), e.major() * 2, e.minor() * 2 };
	return RectangleNS::se(r);
}
