/* Exercise 14.10 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class Pseudo_window : public Shape {
	public:
		Pseudo_window(Point topLeft, int width, int height, const string& string);
		void draw_lines() const;
	private:
		int w;
		int h;
		string lab;    // label
		Font fnt;
		int fnt_sz;

		static const int roundingRadius{ 5 };
		static const int headerHeight{ 20 };
		static const int minWidth{ 100 };
		static const int minHeight{ headerHeight + 30 };
	};
}
