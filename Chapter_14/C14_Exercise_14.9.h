/* Exercise 14.9 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class Group : public Shape {
	public:
		void add(Shape& sh);
		void move(int dx, int dy);
	private:
		Vector_ref<Shape> shapes;
	};
}
