/* Exercise 13.8 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct Regular_hexagon : Closed_polyline {
		Regular_hexagon(Point center, int radius);

		Point GetCenter() const { return c; }
		int GetRadius() const { return r; }
		void draw_lines() const;
	private:
		Point c;
		int r;
	};
}

Point GetPointOnCircle(Point center, int radius, int angleDegree);
