/* Exercise 13.19 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct Star : Shape {
		Star(Point center, int radius, int numberOfVertices, int density);

		Point GetCenter() const { return c; }
		int GetRadius() const { return r; }
		int GetNumberOfVertices() const { return p; }
		int GetDensity() const { return q; }
		void draw_lines() const;
	private:
		Point c;		// center
		int r;			// radius
		int p;			// Schläfli symbol {p/q}, where p  is the number of vertices
		int q;			// Schläfli symbol {p/q}, where q is the density
	};
}

Point GetPointOnCircle(Point center, int radius, int angleDegree);
Point GetPointOnCircle(Point center, int radius, double angleDegree);

inline pair<double, double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel);
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection);
