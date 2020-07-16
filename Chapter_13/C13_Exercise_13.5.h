/* Exercise 13.5 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	namespace RectangleNS {
		Point n(const RectanglePPP2& r);
		Point s(const RectanglePPP2& r);
		Point w(const RectanglePPP2& r);
		Point e(const RectanglePPP2& r);
		Point center(const RectanglePPP2& r);
		Point nw(const RectanglePPP2& r);
		Point sw(const RectanglePPP2& r);
		Point ne(const RectanglePPP2& r);
		Point se(const RectanglePPP2& r);
	}
	namespace CircleNS {
		Point n(const Circle& c);
		Point s(const Circle& c);
		Point w(const Circle& c);
		Point e(const Circle& c);
		Point center(const Circle& c);
		Point nw(const Circle& c);
		Point sw(const Circle& c);
		Point ne(const Circle& c);
		Point se(const Circle& c);
	}
	namespace EllipseNS {
		Point n(const EllipsePPP2& e);
		Point s(const EllipsePPP2& e);
		Point w(const EllipsePPP2& e);
		Point e(const EllipsePPP2& e);
		Point center(const EllipsePPP2& e);
		Point nw(const EllipsePPP2& e);
		Point sw(const EllipsePPP2& e);
		Point ne(const EllipsePPP2& e);
		Point se(const EllipsePPP2& e);
	}
}

Point GetPointOnCircle(Point center, int radius, int angleDegree);
