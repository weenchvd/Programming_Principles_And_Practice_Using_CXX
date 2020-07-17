/* Exercise 13.10 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct Regular_polygon : Closed_polyline {
		Regular_polygon(Point center, int radius, int numberOfSides);

		Point GetCenter() const { return c; }
		int GetRadius() const { return r; }
		int GetNumberOfSides() const { return n; }
		void draw_lines() const;
	private:
		Point c;
		int r;
		int n;
	};
}

Point GetPointOnCircle(Point center, int radius, int angleDegree);
