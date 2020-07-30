/* Exercise 15.8 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	class Bar : public Shape {
	public:
		Bar(Point orig, int width = 600, int height = 400, const string& label = "",
			Color borderColor = Color::black, int intervalScale = 30);
		void add(double barValue, const string& barLabel = "", Color barColor = Color::dark_green);
		void draw_lines() const;
	private:
		// graph
		Point o;												// graph origin point
		string lab;												// graph label
		int w;													// graph width
		int h;													// graph height
		// bars
		vector<double> v;										// bar values
		vector<Color> c;										// bar fill colors
		double is;												// interval scale
		Color bc;												// border color of bars
		double max;												// maximum value
		// labels
		vector<string> l;										// bar labels
		Color fc;												// font color
		Font fnt;												// font of the bar labels
		int fs;													// font size of the bar labels
		// axes
		Color ac;												// axis color
		int nw;													// notch width
		int nNotches;											// number of notches
	};

	struct HeightDistribution {
		HeightDistribution() : h{ 0 }, n{ 0 } { }
		int h;													// height
		int n;													// number of people
	};

	istream& operator>>(istream& is, HeightDistribution& hd);
}
