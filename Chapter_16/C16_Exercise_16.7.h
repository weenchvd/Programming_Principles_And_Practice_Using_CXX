/* Exercise 16.7 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	constexpr int defaultAirplaneSize = 120;
	constexpr double defaultRotationAngle = 0.0;
	constexpr int defaultFlyRadius = 400;
	constexpr double defaultRotationAngleStep = 0.5;

	static const Point airplaneCenter{ 500,500 };

	class Airplane : public Shape {
	public:
		Airplane(Point center, int airplaneSize, double rotationAngle);
		void SetCenter(Point center) { c = center; }
		void SetAngle(double rotationAngle) { angle = rotationAngle; }
		void draw_lines() const;
	private:
		Point c;
		int size;
		double angle;
		// radius and angle for the points [p1:p10] of the airplane
		int r1;
		double a1;
		int r2;
		double a2;
		int r3;
		double a3;
		int r4;
		double a4;
		int r5;
		double a5;
		int r6;
		double a6;
		int r7;
		double a7;
		int r8;
		double a8;
		int r9;
		double a9;
		int r10;
		double a10;
		// the points [p11:p18] are the mirror image of the points [p2:p9]
	};

	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);
		bool QuitPushed() const { return quitPushed; }
		bool wait_for_button();
	private:
		Airplane airplane{ airplaneCenter, defaultAirplaneSize, defaultRotationAngle };

		Button buttonStart;
		Button buttonStop;
		Button buttonQuit;

		bool toFly;
		bool quitPushed;

		void start();
		void stop();
		void quit();
	};

	Point GetPointOnCircle(Point center, int radius, double angleDegree);
}
