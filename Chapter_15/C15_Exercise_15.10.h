/* Exercise 15.10 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class DotGraph : public Shape {
	public:
		DotGraph(Point orig, int width = 600, int height = 400, const string& label = "",
			const string& xLabel = "", const string& yLabel = "");
		void add(double xValue, double yValue, Color dotColor = Color::dark_green);
		void draw_lines() const;
	private:
		// graph
		Point o;												// graph origin point
		string lab;												// graph label
		int w;													// graph width
		int h;													// graph height
		// dots
		vector<double> xv;										// dot x values
		vector<double> yv;										// dot y values
		vector<Color> c;										// dot fill colors
		double xmax;											// maximum x value
		double ymax;											// maximum y value
		int dr;													// dot radius
		// labels
		Color fc;												// font color
		Font fnt;												// font
		int fs;													// font size
		string xl;												// x label
		string yl;												// yy label
		// axes
		Color ac;												// axis color
		int nw;													// notch width
		int nNotches;											// number of notches
	};

	struct HeightWeight {
		HeightWeight() : h{ 0 }, w{ 0 } { }
		int h;													// height (cm)
		int w;													// weight (kg)
	};

	istream& operator>>(istream& is, HeightWeight& hw);
}
