/* Exercise 14.8 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct Regular_octagon : Closed_polyline {
		Regular_octagon(Point center, int radius);
		void move(int dx, int dy);

		Point GetCenter() const { return c; }
		int GetRadius() const { return r; }
	private:
		Point c;
		int r;
	};
}

Point GetPointOnCircle(Point center, int radius, int angleDegree);
