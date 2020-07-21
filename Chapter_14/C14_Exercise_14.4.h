/* Exercise 14.4 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class Immobile_Circle : public Circle {
	public:
		Immobile_Circle(Point center, int radius)
			: Circle(center, radius) { }
	protected:
		void move(int dx, int dy) { Shape::move(dx, dy); }
	};
}