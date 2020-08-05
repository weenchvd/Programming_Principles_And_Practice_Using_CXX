/* Exercise 16.4 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);
		bool wait_for_button();
	private:
		In_box inboxXOrigin;
		In_box inboxYOrigin;
		In_box inboxRadius;
		
		Menu menuShape;

		Button buttonMenuShape;
		Button buttonQuit;
		bool quitPushed;

		void MenuShapePressed() { buttonMenuShape.hide(); menuShape.show(); }
		void DrawCircle();
		void DrawSquare();
		void DrawTriangle();
		void DrawHexagon();
		void quit();
	};

	Point GetPointOnCircle(Point center, int radius, double angleDegree);
}
