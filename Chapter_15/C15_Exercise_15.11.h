/* Exercise 15.11 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	constexpr int defaultIntervalScale = 30;
	constexpr int defaultFontSize = 14;

	// intervalScale is measured in percent [1:99], INTERVAL + BAR == 100
	class GraphBar : public Shape {
	public:
		struct Axis {
			Axis() : col{ Color::black }, font{ Font::helvetica }, fontSize{ defaultFontSize + 2 },
				notchWidth{ 5 }, nIntervals{ 0 } { }
			string lab;											// axis label
			Color col;											// axis color and font color of the axis label
			Font font;											// font of the axis label
			int fontSize;										// font size of the axis label
			int notchWidth;										// notch width of axis
			int nIntervals;										// number of intervals on the axis
		};

		struct Bars {
			Bars() : borderCol{ Color::black }, minVal{ 0.0 }, maxVal{ 0.0 }, fontCol{ Color::black },
				font{ Font::helvetica }, fontSize{ defaultFontSize } { }
			// bars
			vector<double> val;									// bar values
			vector<Color> col;									// bar fill colors
			Color borderCol;									// border color of bars
			double minVal;										// minimum value
			double maxVal;										// maximum value
			// labels
			vector<string> lab;									// bar labels
			Color fontCol;										// font color
			Font font;											// font of the bar labels
			int fontSize;										// font size of the bar labels
		};

		GraphBar(Point origin, int width = 600, int height = 400, const string& label = "",
			int numberOfBarsInGroup = 1, int intervalScale = defaultIntervalScale);
		void Add(double barValue, const string& barLabel = "", Color barColor = Color::dark_green);
		void SetMinMax(double minValue, double maxValue, int numberOfIntervals);
		void draw_lines() const;
	private:
		Point origin;											// graph origin point
		string lab;												// graph label
		Color fontCol;											// graph font color
		Font font;												// graph font
		int fontSize;											// graph font size
		int width;												// graph width
		int height;												// graph height
		int barsInGroup;										// number of bars in group
		double intScale;										// interval scale (from 0.01 to 0.99)

		Bars bars;
		Axis xAxis;
		Axis yAxis;
	};

	struct Temperature {
		Temperature() : max{ 0.0 } { }
		double max;												// maximum
		string lab;												// label
	};

	istream& operator>>(istream& is, Temperature& t);
	istream& GetAverageMaxTemperature(istream& is, stringstream& ss);
	string GetMonthName(int monthNumber);
}
