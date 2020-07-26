/* Exercise 14.16 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class Controller : public Shape {
	public:
		virtual void on() = 0;
		virtual void off() = 0;
		virtual void set_level(int level) = 0;
		virtual Text* show(Point p) const = 0;
	};

	class TestController : public Controller {
	public:
		TestController()
			: isOn{ false }, lvl{ 0 } { }
		TestController(int level, bool isOn)
			: isOn{ isOn }, lvl{ level } { }
		void on() { isOn = true; }
		void off() { isOn = false; }
		void set_level(int level) { lvl = level; }
		Text* show(Point p) const;
	private:
		int lvl;
		bool isOn;
	};

	class ShapeController : public Controller {
	public:
		ShapeController(Shape& shape);
		ShapeController(Shape& shape, int level, bool isOn);
		void on();
		void off();
		void set_level(int level);
		Text* show(Point p) const;
	private:
		Shape& sh;
		Color col;
		int lvl;
		bool isOn;
	};
}
