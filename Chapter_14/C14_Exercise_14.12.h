/* Exercise 14.12 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class Binary_tree : public Shape {
	public:
		Binary_tree(Point p, int level) : lvl{ level } { Shape::add(p); }
		void SetLevel(int level) { lvl = level; }
		int GetLevel() const { return lvl; }
		inline int GetDistance() const { return dist; }
		inline int GetRadius() const { return radius; }
		virtual void draw_lines() const;
	private:
		void DrawChildren(Point par, const int parLevel) const;

		int lvl;										// number of levels
		static const int radius = 20;					// radius of a node
		static const int dist = 60;						// distance between the centers of nodes along each axis

	};

	class Binary_tree_triangle : public Binary_tree {
	public:
		Binary_tree_triangle(Point p, int level)
			: Binary_tree(p, level) { }
		void draw_lines() const;
	private:
		void DrawChildren(Point par, const int parLevel) const;
	};

	class Binary_tree_rhombus : public Binary_tree {
	public:
		Binary_tree_rhombus(Point p, int level)
			: Binary_tree(p, level) { }
		void draw_lines() const;
	private:
		void DrawChildren(Point par, const int parLevel) const;
	};

}

Point GetPointOnCircle(Point center, int radius, double angleDegree);
