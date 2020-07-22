/* Exercise 14.6 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class Striped_circle : public Circle {
	public:
		Striped_circle(Point xy, int radius, int lineSpacing)
			: Circle(xy, radius), ls{lineSpacing} { }
		void draw_lines() const;

		int GetLineSpacing() const { return ls; }
		void SetLineSpacing(int lineSpacing) { ls = lineSpacing; }
	private:
		int ls;			// line spacing
	};
}