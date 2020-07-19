/* Exercise 13.13 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	constexpr int colorSize = 40;
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "RGB color chart" };

	Vector_ref<RectanglePPP2> colorChart;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			colorChart.push_back(new RectanglePPP2{ Point{ i * colorSize, j * colorSize}, colorSize, colorSize });
			colorChart[colorChart.size() - 1].set_fill_color(i * 16 + j);
			colorChart[colorChart.size() - 1].set_color(Color{ Color::black, Color::Transparency::invisible });
			sw.attach(colorChart[colorChart.size() - 1]);
		}
	}

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
