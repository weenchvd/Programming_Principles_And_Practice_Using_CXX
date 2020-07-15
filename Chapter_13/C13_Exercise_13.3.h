/* Exercise 13.3 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct Arrow : Shape {
		Arrow(Point from, Point to);
		void draw_lines() const;
	private:
		Point lineStart;
		Point lineEnd;			// lineEnd == arrowhead1
		Point arrowhead2;
		Point arrowhead3;
	};
}