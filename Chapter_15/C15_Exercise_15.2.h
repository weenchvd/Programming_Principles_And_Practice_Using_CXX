/* Exercise 15.2 */

using namespace std;
using namespace Graph_lib;

namespace Fct {
	class Fct : public Shape {
	public:
		Fct(Graph_lib::Fct f, double r1, double r2, Point orig,
			int count = 100, double xscale = 25, double yscale = 25);
		void reset(Graph_lib::Fct f);
		void reset(double r1, double r2);
		void reset(Point orig);
		void reset(int count);
		void reset_scale(double xscale, double yscale);
	private:
		function<double(double)> fct;
		double x1;
		double x2;
		double xs;
		double ys;
		Point o;
		int cnt;
	};
}

double one(double);
double slope(double x);
double square(double x);
