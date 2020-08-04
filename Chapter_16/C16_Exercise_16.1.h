/* Exercise 16.1 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);

		bool wait_for_button();

	private:
		Button next_button;
		Button quit_button;
		bool next_pushed;
		bool quit_pushed;

		static void cb_next(Address, Address);
		static void cb_quit(Address, Address);
		void next();
		void quit();
	};
}
