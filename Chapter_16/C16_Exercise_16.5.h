/* Exercise 16.5 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);
		bool wait_for_button();
	private:
		Circle circle{ Point{500, 500}, 100 };

		In_box inboxFileName;
		ifstream ifs;
		Button buttonOpen;

		Button buttonNext;
		Button buttonQuit;
		bool quitPushed;

		void OpenFile();
		void MoveCircle();
		void quit();
	};

	ifstream& operator>>(ifstream& ifs, Point& p);
}
