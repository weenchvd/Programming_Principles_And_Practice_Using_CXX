/* Exercise 14.5 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class Striped_rectangle : public RectanglePPP2 {
	public:
		Striped_rectangle(Point xy, int width, int height, int lineSpacing)
			: RectanglePPP2(xy, width, height), ls{lineSpacing} { }
		void draw_lines() const;

		int GetLineSpacing() const { return ls; }
		void SetLineSpacing(int lineSpacing) { ls = lineSpacing; }
	private:
		int ls;
	};
}