/* Exercise 13.6 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct Box : Shape {
		Box(Point p, int radius, int fontSize, const string& s);
		void draw_lines() const;
		int GetWidth() const { return w; }
		int GetHeight() const { return h; }
		int GetRadius() const { return r; }

		void SetWidth(int widht) { w = widht; }
		void SetHeight(int height) { h = height; }
		void SetRadius(int radius) { r = radius; }

		Point GetTopCenter() const { return { point(0).x + w / 2, point(0).y }; }
		Point GetBottomCenter() const { return { point(0).x + w / 2, point(0).y + h }; }
		Point GetLeftCenter() const { return { point(0).x, point(0).y + h / 2 }; }
		Point GetRightCenter() const { return { point(0).x + w, point(0).y + h / 2 }; }
		Point GetTopLeft() const { return point(0); }
		Point GetBottomLeft() const { return { point(0).x, point(0).y + h }; }
		Point GetTopRigth() const { return { point(0).x + w, point(0).y }; }
		Point GetBottomRigth() const { return { point(0).x + w, point(0).y + h }; }
	private:
		int w;			// width
		int h;			// height
		int r;			// radius
		string lab;		// label
		Font fnt;		// font
		int fnt_sz;		// font size
	};

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