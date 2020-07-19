/* Exercise 13.18 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct Poly : PolygonPPP2 {
		Poly(initializer_list<Point> list);
		void draw_lines() const;
	};
}