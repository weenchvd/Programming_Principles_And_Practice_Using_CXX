/* Exercise 15.6 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class Bar : public Shape {
	public:
		Bar(const vector<double>& values, Point orig, int xLength = 600, int yLength = 400);
		void draw_lines() const;
	};
}
