/* Exercise 14.7 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class Striped_closed_polyline : public Closed_polyline {
	public:
		Striped_closed_polyline(int lineSpacing)
			: ls{lineSpacing} { }
		void draw_lines() const;

		int GetLineSpacing() const { return ls; }
		void SetLineSpacing(int lineSpacing) { ls = lineSpacing; }
	private:
		int ls;			// line spacing
	};
}

inline pair<double, double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel);
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection);
