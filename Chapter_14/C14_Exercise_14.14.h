/* Exercise 14.14 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	enum class Link_type {
		line = 0,
		lineArrowUp = 1,
		lineArrowDown = 2
	};

	struct NodeLabel {
		string loc;			// location
		string text;			// label
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
		virtual void draw_lines() const;

		void SetLabel(const string& location, const string& text) { lab.push_back(NodeLabel{ location, text }); }
		NodeLabel GetLabel(int i) const { return lab[i]; }
		void SetLevel(int level) { lvl = level; }
		int GetLevel() const { return lvl; }
		Link_type GetLinkType() const { return lt; }
		inline int GetDistance() const { return dist; }
		inline int GetRadius() const { return radius; }
	protected:
		void DrawLabel(Point rootCenter, const NodeLabel& lab) const;

		vector<NodeLabel> lab;
	private:
		void DrawChildren(Point par, const int parLevel) const;

		int lvl;										// number of levels
		Link_type lt;
		const Font fnt = Font::helvetica;
		const int fnt_sz = 12;
		static const int radius = 20;					// radius of a node
		static const int dist = 60;						// distance between the centers of nodes along each axis
		static const int nChars = 3;					// number of characters to display
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
}

Point GetPointOnCircle(Point center, int radius, double angleDegree);
void DrawLineArrow(Point from, Point to);
