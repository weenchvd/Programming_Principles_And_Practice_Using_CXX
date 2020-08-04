/* Exercise 16.3 */

using namespace std;
using namespace Graph_lib;

inline int rand_int(int min, int max)
{
	static default_random_engine ran;
	return uniform_int_distribution<>{min, max}(ran);
}

namespace Graph_lib {
	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);
		bool wait_for_button();
	private:
		Image fry{ Point{x_max() - x_max() / 2 - 250, y_max() - y_max() / 2 - 50 }, "C16_Exercise_16.3_11784800.jpg" };
		Button suspicious_button;
		Button quit_button;
		bool quit_pushed;

		void move();
		void quit();
	};
}
