/* Exercise 16.6 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	constexpr int nIntervals = 60;								// number of intervals on the clockCircle
	constexpr int nIntervalsInHour = nIntervals / 12;			// number of intervals in a hour
	constexpr int angleInterval = 360 / nIntervals;
	constexpr int clockRadius = 200;
	constexpr int hourHandRadius = clockRadius * 5 / 10;
	constexpr int minuteHandRadius = clockRadius * 7 / 10;
	constexpr int secondHandRadius = clockRadius * 8 / 10;
	constexpr int defaultStyle = int(Line_style::Line_style_type::solid);
	constexpr int hourHandWidth = 5;
	constexpr int minuteHandWidth = 3;
	constexpr int secondHandColor = int(Color::dark_red);
	constexpr int minuteNotchSize = 10;
	constexpr int hourNotchSize = 20;
	constexpr int hourNotchWidth = 5;
	constexpr int notchOuterRadius = clockRadius - 20;
	static const Point clockCenter{ 500,500 };

	class Clock : public Shape {
	public:
		Clock(Point center);
		bool UpdateTime();
		Point GetCenter() const { return point(0); }
		void draw_lines() const;
	private:
		tm t;
		int sec;
	};

	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);
		void RunClock();
		bool QuitPushed() const { return quitPushed; }
		bool wait_for_button();
	private:
		Clock clock{ clockCenter };

		Button buttonQuit;
		bool quitPushed;

		void quit();
	};

	Point GetPointOnCircle(Point center, int radius, double angleDegree);
}
