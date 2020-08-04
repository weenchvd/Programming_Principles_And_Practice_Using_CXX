/* Exercise 16.2 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);
		bool wait_for_button();
	private:
		RectanglePPP2 rect{ Point{x_max() - x_max() * 5 / 6, y_max() - y_max() * 5 / 6 - 100}, x_max() * 4 / 6, 100 };
		Button b_1_1;											// b_RowNumber_ColumnNumber
		Button b_1_2;
		Button b_1_3;
		Button b_1_4;
		Button b_2_1;
		Button b_2_2;
		Button b_2_3;
		Button b_2_4;
		Button b_3_1;
		Button b_3_2;
		Button b_3_3;
		Button b_3_4;
		Button b_4_1;
		Button b_4_2;
		Button b_4_3;
		Button b_4_4;
		Button next_button;
		Button quit_button;
		bool next_pushed;
		bool quit_pushed;

		static void cb_next(Address, Address);
		static void cb_quit(Address, Address);
		void ChangeColor(Color col);
		void next();
		void quit();
	};
}
