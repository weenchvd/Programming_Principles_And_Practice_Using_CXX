/* Exercise 13.2 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct Box : Shape {
		Box(Point p, int width, int height, int radius);
		void draw_lines() const;
		int GetWidth() const { return w; }
		int GetHeight() const { return h; }
		int GetRadius() const { return r; }

		void SetWidth(int widht) { w = widht; }
		void SetHeight(int height) { h = height; }
		void SetRadius(int radius) { r = radius; }
	private:
		int w;
		int h;
		int r;
	};
}