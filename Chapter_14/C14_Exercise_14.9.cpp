/* Exercise 14.9 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C14_Exercise_14.9.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "Group" };

	/*Circle cir1{ Point{200, 200}, 100 };
	sw.attach(cir1);
	RectanglePPP2 rect1{ Point{320, 100}, 100, 200 };
	sw.attach(rect1);
	Line line1{ Point{450, 100}, Point{450, 300} };
	sw.attach(line1);
	PolygonPPP2 poly1;
	poly1.add(Point{ 470, 100 });
	poly1.add(Point{ 550, 200 });
	poly1.add(Point{ 500, 300 });
	sw.attach(poly1);

	ostringstream oss;
	oss << "Center of the circle before moving: (" << cir1.center().x << "," << cir1.center().y << ")";
	string s1 = oss.str();
	Text text1{ Point{100, 50}, s1 };
	sw.attach(text1);


	Group gr1;
	gr1.add(cir1);
	gr1.add(rect1);
	gr1.add(line1);
	gr1.add(poly1);
	gr1.move(0, 400);

	oss.str("");
	oss << "Center of the circle after moving: (" << cir1.center().x << "," << cir1.center().y << ")";
	string s2 = oss.str();
	Text text2{ Point{100, 400}, s2 };
	sw.attach(text2);*/

	constexpr int tileWidth = 70;
	constexpr int checkerRadius = (tileWidth - tileWidth / 3) / 2;
	constexpr int dimensionality = 8;
	constexpr int nCheckers = 12;					// number of checkers of the same color
	RectanglePPP2 rectBoard{ Point{0,0}, tileWidth * dimensionality, tileWidth * dimensionality };
	Vector_ref<Shape> rectangles;
	bool isBlack{ true };
	for (int i = 0; i < dimensionality; i++) {
		for (int j = 0; j < dimensionality; j++) {
			rectangles.push_back(new RectanglePPP2{ Point{j * tileWidth, i * tileWidth}, tileWidth, tileWidth });
			if (isBlack) rectangles[rectangles.size() - 1].set_fill_color(Color::black);
			else rectangles[rectangles.size() - 1].set_fill_color(Color::white);
			rectangles[rectangles.size() - 1].set_color(Color::black);
			isBlack = (isBlack) ? false : true;
			sw.attach(rectangles[rectangles.size() - 1]);
		}
		isBlack = (isBlack) ? false : true;
	}
	Vector_ref<Shape> checkers;
	for (int i = 0; i < rectangles.size(); i++) {
		if (rectangles[i].fill_color().as_int() == int(Color::black)) {
			checkers.push_back(new Circle{ Point{rectangles[i].point(0).x + tileWidth / 2,
				rectangles[i].point(0).y + tileWidth / 2}, checkerRadius });
			checkers[checkers.size() - 1].set_color(Color::dark_red);
			checkers[checkers.size() - 1].set_style(Line_style(Line_style::Line_style_type::solid, 5));
			sw.attach(checkers[checkers.size() - 1]);
		}
		if (checkers.size() >= nCheckers) break;
	}
	for (int i = rectangles.size() - 1; i >= 0; i--) {
		if (rectangles[i].fill_color().as_int() == int(Color::black)) {
			checkers.push_back(new Circle{ Point{rectangles[i].point(0).x + tileWidth / 2,
				rectangles[i].point(0).y + tileWidth / 2}, checkerRadius });
			checkers[checkers.size() - 1].set_color(Color::white);
			checkers[checkers.size() - 1].set_style(Line_style(Line_style::Line_style_type::solid, 5));
			sw.attach(checkers[checkers.size() - 1]);
		}
		if (checkers.size() >= nCheckers * 2) break;
	}

	Group groupBoard;
	for (int i = 0; i < rectangles.size(); i++) {
		groupBoard.add(rectangles[i]);
	}
	for (int i = 0; i < checkers.size(); i++) {
		groupBoard.add(checkers[i]);
	}
	groupBoard.move(0, 100);

	checkers[11].move(-tileWidth, tileWidth);

	groupBoard.move(200, 0);

	sw.wait_for_button();
	return 0;
}
catch (runtime_error& e) {
	cerr << e.what() << endl;
}
catch (...) {
	cerr << "Error. Exception\n";
	return 1;
}

void Group::add(Shape& sh)
{
	shapes.push_back(sh);
}

void Group::move(int dx, int dy)
{
	for (int i = 0; i < shapes.size(); i++) {
		shapes[i].move(dx, dy);
	}
}
