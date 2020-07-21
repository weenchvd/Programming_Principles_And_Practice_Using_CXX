/* Exercise 14.1 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class Smiley : public Circle {
	public:
		Smiley(Point center, int radius)
			: Circle(center, radius) { }

		void draw_lines() const;
	};

	class Frowny : public Circle {
	public:
		Frowny(Point center, int radius)
			: Circle(center, radius) { }

		void draw_lines() const;
	};

	class SmileyHat : public Smiley {
	public:
		SmileyHat(Point center, int radius)
			: Smiley(center, radius) { }

		void draw_lines() const;
	};

	class FrownyHat : public Frowny {
	public:
		FrownyHat(Point center, int radius)
			: Frowny(center, radius) { }

		void draw_lines() const;
	};
}