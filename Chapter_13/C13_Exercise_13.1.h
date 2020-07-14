/* Exercise 13.1 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct Arc : Shape {
		Arc(Point p, int widthRadius, int heightRadius, int fromAngle, int toAngle)
			: w{ widthRadius }, h{ heightRadius }, a1{ fromAngle }, a2{ toAngle }
		{
			add(Point{ p.x - widthRadius, p.y - heightRadius });
		}
		void draw_lines() const;
		int GetMajorRadius() const { return w; }
		int GetMinoRadiusr() const { return h; }
		Point GetCenter() const { return { point(0).x + w, point(0).y + h }; }
		void SetMajorRadius(int widthRadius) { w = widthRadius; }
		void SetMinorRadius(int heightRadius) { h = heightRadius; }
	private:
		int w;		//radius
		int h;		//radius
		int a1;
		int a2;
	};
}