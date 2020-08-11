/* Exercise 16.10 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	constexpr int windowWidth = 1600;
	constexpr int windowHeight = 1200;

	constexpr int leftIndentation = 300;
	constexpr int rightIndentation = 100;
	constexpr int topIndentation = 100;
	constexpr int bottomIndentation = 100;
	constexpr int xAxisSize = windowWidth - leftIndentation - rightIndentation;
	constexpr int yAxisSize = windowHeight - topIndentation - bottomIndentation;
	constexpr int nPoints = 500;
	constexpr int nNotches = 20;

	constexpr int defaultButtonHeigth = 30;
	constexpr int defaultFontSize = 14;
	constexpr int defaultTextIndentation = 5;
	constexpr int defaultFont = int(Font::helvetica);

	const Point origin{ leftIndentation + xAxisSize / 2, topIndentation + yAxisSize / 2 };

	double Square(double x) { return x * x; }
	double Cubic(double x) { return x * x * x; }

	struct Functions : Window {
		Functions(Point xy, int w, int h, const string& title);
		bool wait_for_button();
	private:
		Axis xAxis{ Axis::Orientation::x, Point{ leftIndentation, origin.y }, xAxisSize, nNotches };
		Axis yAxis{ Axis::Orientation::y, Point{ origin.x, topIndentation + yAxisSize }, yAxisSize, nNotches };
		Text textTop{ Point{ origin.x, topIndentation - defaultTextIndentation}, "1.0" };
		Text textBottom{ Point{ origin.x, topIndentation + yAxisSize + defaultFontSize + defaultTextIndentation }, "-1.0" };
		Text textLeft{ Point{ leftIndentation, origin.y + defaultFontSize + defaultTextIndentation }, "-1.0" };
		Text textRight{ Point{ leftIndentation + xAxisSize, origin.y + defaultFontSize + defaultTextIndentation }, "1.0" };
		Function* pf = nullptr;

		In_box ibMin;
		In_box ibMax;
		Menu menuFunction;
		Button buttonMenuFunction;
		Button buttonQuit;
		bool quitPushed;

		bool GetRange(double& xMin, double& xMax);
		void CalculateScale(Fct function, double xMin, double xMax, double& yMin, double& yMax, double& xScale, double& yScale);
		void SetAxisLabels(double xAbsoluteValue, double yAbsoluteValue);

		void MenuFunctionPressed() { buttonMenuFunction.hide(); menuFunction.show(); }
		void Draw(Fct function);
		void DrawSin() { Draw(sin); }
		void DrawCos() { Draw(cos); }
		void DrawTan() { Draw(tan); }
		void DrawLog() { Draw(log); }
		void DrawLog2() { Draw(log2); }
		void DrawLog10() { Draw(log10); }
		void DrawSquare() { Draw(Square); }
		void DrawCubic() { Draw(Cubic); }
		void DrawExp() { Draw(exp); }
		void quit();
	};
}
