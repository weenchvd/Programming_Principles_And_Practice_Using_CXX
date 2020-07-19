/* Exercise 13.15 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct RightTriangle : Closed_polyline {
		RightTriangle(Point point, int legRightLength, int legDownLength, int rotationAngleDeg = 0);

		Point GetPoint() const { return p; }
		int GetLegRight() const { return lr; }
		int GetLegDown() const { return ld; }
		int GetRotationAngle() const { return a; }
		void draw_lines() const;
	private:
		Point p;			// point of right angle
		int lr;				// length of leg right
		int ld;				// length of leg down
		int a;				// angle of rotation in degrees
	};
}

Point GetPointOnCircle(Point center, int radius, int angleDegree);
Point GetPointOnEllipse(Point center, int width, int height, int angleDegree);
