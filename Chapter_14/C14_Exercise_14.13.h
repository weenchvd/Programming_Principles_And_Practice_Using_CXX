/* Exercise 14.13 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	enum class Link_type {
		line = 0,
		lineArrowUp = 1,
		lineArrowDown = 2
	};

	class Binary_tree : public Shape {
	public:
		Binary_tree(Point p, int level)
			: lvl{ level }, lt{ Link_type::line } { add(p); }
		Binary_tree(Point p, int level, Color color)
			: lvl{ level }, lt{ Link_type::line } { add(p); set_color(color); }
		Binary_tree(Point p, int level, Link_type link)
			: lvl{ level }, lt{ link } { add(p); }
		Binary_tree(Point p, int level, Link_type link, Color color)
			: lvl{ level }, lt{ link } { add(p); set_color(color); }
		void SetLevel(int level) { lvl = level; }
		int GetLevel() const { return lvl; }
		Link_type GetLinkType() const { return lt; }
		inline int GetDistance() const { return dist; }
		inline int GetRadius() const { return radius; }
		virtual void draw_lines() const;
	private:
		void DrawChildren(Point par, const int parLevel) const;

		int lvl;										// number of levels
		Link_type lt;
		static const int radius = 20;					// radius of a node
		static const int dist = 60;						// distance between the centers of nodes along each axis

	};

	class Binary_tree_triangle : public Binary_tree {
	public:
		Binary_tree_triangle(Point p, int level)
			: Binary_tree(p, level) { }
		Binary_tree_triangle(Point p, int level, Color color)
			: Binary_tree(p, level, color) { }
		Binary_tree_triangle(Point p, int level, Link_type link)
			: Binary_tree(p, level, link) { }
		Binary_tree_triangle(Point p, int level, Link_type link, Color color)
			: Binary_tree(p, level, link, color) { }
		void draw_lines() const;
	private:
		void DrawChildren(Point par, const int parLevel) const;
	};

	class Binary_tree_rhombus : public Binary_tree {
	public:
		Binary_tree_rhombus(Point p, int level)
			: Binary_tree(p, level) { }
		Binary_tree_rhombus(Point p, int level, Color color)
			: Binary_tree(p, level, color) { }
		Binary_tree_rhombus(Point p, int level, Link_type link)
			: Binary_tree(p, level, link) { }
		Binary_tree_rhombus(Point p, int level, Link_type link, Color color)
			: Binary_tree(p, level, link, color) { }
		void draw_lines() const;
	private:
		void DrawChildren(Point par, const int parLevel) const;
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

Point GetPointOnCircle(Point center, int radius, double angleDegree);
void DrawLineArrow(Point from, Point to);
