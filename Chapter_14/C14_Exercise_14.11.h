/* Exercise 14.11 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class Binary_tree : public Shape {
	public:
		Binary_tree(Point p, int level) : lvl{ level } { Shape::add(p); }
		void draw_lines() const;
		void SetLevel(int level) { lvl = level; }
		int GetLevel() const { return lvl; }
	private:
		void DrawChildren(Point par, const int parLevel) const;

		int lvl;										// number of levels
		static const int radius = 20;					// radius of a node
		static const int dist = 60;						// distance between the centers of nodes along each axis

	};
}

Point GetPointOnCircle(Point center, int radius, double angleDegree);
