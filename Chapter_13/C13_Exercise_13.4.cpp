/* Exercise 13.4 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C13_Exercise_13.4.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;
using namespace Rectangle;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Rectangle" };

	RectanglePPP2 rect{ Point{200, 100}, 500, 400 };
	sw.attach(rect);
	ostringstream oss;
	oss << "Top left point (x,y): " << rect.point(0).x << "," << rect.point(0).y;
	oss << "; height " << rect.height() << ", width " << rect.width();
	string sTLPoint = oss.str();
	Text tTLPoint{ Point{200, 30}, sTLPoint };
	sw.attach(tTLPoint);
	
	Point pNorth = n(rect);
	oss.str("");
	oss << pNorth.x << "," << pNorth.y;
	string sNorth = oss.str();
	Text tNorth{ pNorth, sNorth };
	sw.attach(tNorth);
	Mark mNorth{ pNorth, 'x' };
	sw.attach(mNorth);

	Point pSouth = s(rect);
	oss.str("");
	oss << pSouth.x << "," << pSouth.y;
	string sSouth = oss.str();
	Text tSouth{ pSouth, sSouth };
	sw.attach(tSouth);
	Mark mSouth{ pSouth, 'x' };
	sw.attach(mSouth);

	Point pWest = w(rect);
	oss.str("");
	oss << pWest.x << "," << pWest.y;
	string sWest = oss.str();
	Text tWest{ pWest, sWest };
	sw.attach(tWest);
	Mark mWest{ pWest, 'x' };
	sw.attach(mWest);

	Point pEast = e(rect);
	oss.str("");
	oss << pEast.x << "," << pEast.y;
	string sEast = oss.str();
	Text tEast{ pEast, sEast };
	sw.attach(tEast);
	Mark mEast{ pEast, 'x' };
	sw.attach(mEast);

	Point pCenter = center(rect);
	oss.str("");
	oss << pCenter.x << "," << pCenter.y;
	string sCenter = oss.str();
	Text tCenter{ pCenter, sCenter };
	sw.attach(tCenter);
	Mark mCenter{ pCenter, 'x' };
	sw.attach(mCenter);

	Point pNorthWest = nw(rect);
	oss.str("");
	oss << pNorthWest.x << "," << pNorthWest.y;
	string sNorthWest = oss.str();
	Text tNorthWest{ pNorthWest, sNorthWest };
	sw.attach(tNorthWest);
	Mark mNorthWest{ pNorthWest, 'x' };
	sw.attach(mNorthWest);

	Point pSouthWest = Rectangle::sw(rect);
	oss.str("");
	oss << pSouthWest.x << "," << pSouthWest.y;
	string sSouthWest = oss.str();
	Text tSouthWest{ pSouthWest, sSouthWest };
	sw.attach(tSouthWest);
	Mark mSouthWest{ pSouthWest, 'x' };
	sw.attach(mSouthWest);

	Point pNorthEast = ne(rect);
	oss.str("");
	oss << pNorthEast.x << "," << pNorthEast.y;
	string sNorthEast = oss.str();
	Text tNorthEast{ pNorthEast, sNorthEast };
	sw.attach(tNorthEast);
	Mark mNorthEast{ pNorthEast, 'x' };
	sw.attach(mNorthEast);

	Point pSouthEast = se(rect);
	oss.str("");
	oss << pSouthEast.x << "," << pSouthEast.y;
	string sSouthEast = oss.str();
	Text tSouthEast{ pSouthEast, sSouthEast };
	sw.attach(tSouthEast);
	Mark mSouthEast{ pSouthEast, 'x' };
	sw.attach(mSouthEast);

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

Point Rectangle::n(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x + r.width() / 2, topLeft.y };
}

Point Rectangle::s(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x + r.width() / 2, topLeft.y + r.height() };
}

Point Rectangle::w(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x, topLeft.y + r.height() / 2 };
}

Point Rectangle::e(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x + r.width(), topLeft.y + r.height() / 2 };
}

Point Rectangle::center(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x + r.width() / 2, topLeft.y + r.height() / 2 };
}

Point Rectangle::nw(const RectanglePPP2& r)
{
	return r.point(0);
}

Point Rectangle::sw(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x, topLeft.y + r.height() };
}

Point Rectangle::ne(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x + r.width(), topLeft.y };
}

Point Rectangle::se(const RectanglePPP2& r)
{
	Point topLeft = r.point(0);
	return { topLeft.x + r.width(), topLeft.y + r.height() };
}
