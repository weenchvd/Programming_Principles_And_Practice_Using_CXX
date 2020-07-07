/* Exercise 12.9 */

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
	constexpr int tlWidth = 100;
	constexpr int tlHeight = 100;
	const string s = "Futurama. Philip J. Fry";
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, s };
	Image fry{ Point{tlWidth, tlHeight + 20 }, "C12_Exercise_12.9_11784800.jpg" };
	sw.attach(fry);
	Text hint{ Point{tlWidth, tlHeight}, s + " Looking Squint" };
	hint.set_font(Font::helvetica_bold);
	hint.set_font_size(16);
	sw.attach(hint);

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
