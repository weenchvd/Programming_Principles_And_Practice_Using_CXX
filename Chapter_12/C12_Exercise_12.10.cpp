/* Exercise 12.10 */

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

constexpr double factor = 0.7;
constexpr int fontSize = 16;
constexpr int charWidth = double(fontSize) * factor;
constexpr int fieldHeight = double(fontSize) * factor * 2.0;
constexpr int indentWidth = 5;
constexpr int indentHeigth = fieldHeight - 6;

using namespace Graph_lib;

int main()
try {
	const Point tl{ 100, 50 };
	const Color borderColor{ Color::black };
	const Color fontColor{ Color::black };
	const Color fillColor{ Color::dark_yellow };
	const Font font{ Font::courier };
	const Font fontBold{ Font::courier_bold };
	Simple_window sw{ Point{ 80, 0 }, 1280, 1024, "File diagram" };

	Point pPointH{ tl.x + 50, tl.y + 50 };
	string sPointHTitle{ "Point.h:" };
	string sPointH1{ "struct Point { ... };" };
	int wPointH = sPointH1.size();
	int fieldWidthPointH = wPointH * charWidth + indentWidth * 2;
	Text tPointHTitle{ Point{pPointH.x, pPointH.y + indentHeigth}, sPointHTitle };
	tPointHTitle.set_font(fontBold);
	tPointHTitle.set_font_size(fontSize);
	tPointHTitle.set_color(fontColor);
	sw.attach(tPointHTitle);
	RectanglePPP2 rPointH{ Point{pPointH.x, pPointH.y + fieldHeight}, fieldWidthPointH, fieldHeight };
	rPointH.set_color(borderColor);
	rPointH.set_fill_color(fillColor);
	sw.attach(rPointH);
	Text tPointH1{ Point{pPointH.x + indentWidth, pPointH.y + fieldHeight + indentHeigth}, sPointH1 };
	tPointH1.set_font(fontBold);
	tPointH1.set_font_size(fontSize);
	tPointH1.set_color(fontColor);
	sw.attach(tPointH1);

	Point pGraphH{ pPointH.x, pPointH.y + 100 };
	string sGraphHTitle{ "Graph.h:" };
	string sGraphH1{ "// graphing interface:" };
	string sGraphH2{ "struct Shape { ... };" };
	string sGraphH3{ "..." };
	int wGraphH = max(sGraphH1.size(), sGraphH2.size());
	int fieldWidthGraphH = wGraphH * charWidth + indentWidth * 2;
	Text tGraphHTitle{ Point{pGraphH.x, pGraphH.y + indentHeigth}, sGraphHTitle };
	tGraphHTitle.set_font(fontBold);
	tGraphHTitle.set_font_size(fontSize);
	tGraphHTitle.set_color(fontColor);
	sw.attach(tGraphHTitle);
	RectanglePPP2 rGraphH{ Point{pGraphH.x, pGraphH.y + fieldHeight}, fieldWidthGraphH, fieldHeight * 3 };
	rGraphH.set_color(borderColor);
	rGraphH.set_fill_color(fillColor);
	sw.attach(rGraphH);
	Text tGraphH1{ Point{pGraphH.x + indentWidth, pGraphH.y + fieldHeight + indentHeigth}, sGraphH1 };
	tGraphH1.set_font(font);
	tGraphH1.set_font_size(fontSize);
	tGraphH1.set_color(fontColor);
	sw.attach(tGraphH1);
	Text tGraphH2{ Point{pGraphH.x + indentWidth, pGraphH.y + fieldHeight * 2 + indentHeigth}, sGraphH2 };
	tGraphH2.set_font(fontBold);
	tGraphH2.set_font_size(fontSize);
	tGraphH2.set_color(fontColor);
	sw.attach(tGraphH2);
	Text tGraphH3{ Point{pGraphH.x + indentWidth, pGraphH.y + fieldHeight * 3 + indentHeigth}, sGraphH3 };
	tGraphH3.set_font(fontBold);
	tGraphH3.set_font_size(fontSize);
	tGraphH3.set_color(fontColor);
	sw.attach(tGraphH3);

	Point pGraphCpp{ tl.x, pGraphH.y + 200 };
	string sGraphCppTitle{ "Graph.cpp:" };
	string sGraphCpp1{ "Graph code" };
	int wGraphCpp = sGraphCpp1.size();
	int fieldWidthGraphCpp = wGraphCpp * charWidth + indentWidth * 2;
	Text tGraphCppTitle{ Point{pGraphCpp.x, pGraphCpp.y + indentHeigth}, sGraphCppTitle };
	tGraphCppTitle.set_font(fontBold);
	tGraphCppTitle.set_font_size(fontSize);
	tGraphCppTitle.set_color(fontColor);
	sw.attach(tGraphCppTitle);
	RectanglePPP2 rGraphCpp{ Point{pGraphCpp.x, pGraphCpp.y + fieldHeight}, fieldWidthGraphCpp, fieldHeight };
	rGraphCpp.set_color(borderColor);
	rGraphCpp.set_fill_color(fillColor);
	sw.attach(rGraphCpp);
	Text tGraphCpp1{ Point{pGraphCpp.x + indentWidth, pGraphCpp.y + fieldHeight + indentHeigth}, sGraphCpp1 };
	tGraphCpp1.set_font(fontBold);
	tGraphCpp1.set_font_size(fontSize);
	tGraphCpp1.set_color(fontColor);
	sw.attach(tGraphCpp1);

	Point pFLTKHeaders{ pPointH.x + 400, tl.y };
	string sFLTKHeaders1{ "FLTK headers" };
	int wFLTKHeaders = sFLTKHeaders1.size();
	int fieldWidthFLTKHeaders = wFLTKHeaders * charWidth + indentWidth * 2;
	RectanglePPP2 rFLTKHeaders1{ Point{pFLTKHeaders.x, pFLTKHeaders.y},
		fieldWidthFLTKHeaders, fieldHeight * 2 };
	rFLTKHeaders1.set_color(borderColor);
	rFLTKHeaders1.set_fill_color(fillColor);
	sw.attach(rFLTKHeaders1);
	RectanglePPP2 rFLTKHeaders2{ Point{pFLTKHeaders.x + 10, pFLTKHeaders.y + 10},
		fieldWidthFLTKHeaders, fieldHeight * 2 };
	rFLTKHeaders2.set_color(borderColor);
	rFLTKHeaders2.set_fill_color(fillColor);
	sw.attach(rFLTKHeaders2);
	RectanglePPP2 rFLTKHeaders3{ Point{pFLTKHeaders.x + 20, pFLTKHeaders.y + 20},
	fieldWidthFLTKHeaders, fieldHeight * 2 };
	rFLTKHeaders3.set_color(borderColor);
	rFLTKHeaders3.set_fill_color(fillColor);
	sw.attach(rFLTKHeaders3);
	Text tFLTKHeaders1{ Point{pFLTKHeaders.x + 20 + indentWidth,
		pFLTKHeaders.y + 20 + indentHeigth}, sFLTKHeaders1 };
	tFLTKHeaders1.set_font(font);
	tFLTKHeaders1.set_font_size(fontSize);
	tFLTKHeaders1.set_color(fontColor);
	sw.attach(tFLTKHeaders1);

	Point pFLTKCode{ pFLTKHeaders.x + 300, pPointH.y };
	string sFLTKCode1{ "FLTK code" };
	int wFLTKCode = sFLTKCode1.size();
	int fieldWidthFLTKCode = wFLTKCode * charWidth + indentWidth * 2;
	RectanglePPP2 rFLTKCode1{ Point{pFLTKCode.x, pFLTKCode.y},
		fieldWidthFLTKCode, fieldHeight * 2 };
	rFLTKCode1.set_color(borderColor);
	rFLTKCode1.set_fill_color(fillColor);
	sw.attach(rFLTKCode1);
	RectanglePPP2 rFLTKCode2{ Point{pFLTKCode.x + 10, pFLTKCode.y + 10},
		fieldWidthFLTKCode, fieldHeight * 2 };
	rFLTKCode2.set_color(borderColor);
	rFLTKCode2.set_fill_color(fillColor);
	sw.attach(rFLTKCode2);
	RectanglePPP2 rFLTKCode3{ Point{pFLTKCode.x + 20, pFLTKCode.y + 20},
		fieldWidthFLTKCode, fieldHeight * 2 };
	rFLTKCode3.set_color(borderColor);
	rFLTKCode3.set_fill_color(fillColor);
	sw.attach(rFLTKCode3);
	Text tFLTKCode1{ Point{pFLTKCode.x + 20 + indentWidth,
		pFLTKCode.y + 20 + fieldHeight + indentHeigth}, sFLTKCode1 };
	tFLTKCode1.set_font(font);
	tFLTKCode1.set_font_size(fontSize);
	tFLTKCode1.set_color(fontColor);
	sw.attach(tFLTKCode1);

	Point pWindowH{ pPointH.x + 350, pPointH.y + 70 };
	string sWindowHTitle{ "Window.h:" };
	string sWindowH1{ "// window interface:" };
	string sWindowH2{ "class Window { ... };" };
	string sWindowH3{ "..." };
	int wWindowH = max(max(sWindowH1.size(), sWindowH2.size()), sWindowH3.size());
	int fieldWidthWindowH = wWindowH * charWidth + indentWidth * 2;
	Text tWindowHTitle{ Point{pWindowH.x, pWindowH.y + indentHeigth}, sWindowHTitle };
	tWindowHTitle.set_font(fontBold);
	tWindowHTitle.set_font_size(fontSize);
	tWindowHTitle.set_color(fontColor);
	sw.attach(tWindowHTitle);
	RectanglePPP2 rWindowH{ Point{pWindowH.x, pWindowH.y + fieldHeight}, fieldWidthWindowH, fieldHeight * 3 };
	rWindowH.set_color(borderColor);
	rWindowH.set_fill_color(fillColor);
	sw.attach(rWindowH);
	Text tWindowH1{ Point{pWindowH.x + indentWidth, pWindowH.y + fieldHeight + indentHeigth}, sWindowH1 };
	tWindowH1.set_font(font);
	tWindowH1.set_font_size(fontSize);
	tWindowH1.set_color(fontColor);
	sw.attach(tWindowH1);
	Text tWindowH2{ Point{pWindowH.x + indentWidth, pWindowH.y + fieldHeight * 2 + indentHeigth}, sWindowH2 };
	tWindowH2.set_font(fontBold);
	tWindowH2.set_font_size(fontSize);
	tWindowH2.set_color(fontColor);
	sw.attach(tWindowH2);
	Text tWindowH3{ Point{pWindowH.x + indentWidth, pWindowH.y + fieldHeight * 3 + indentHeigth}, sWindowH3 };
	tWindowH3.set_font(fontBold);
	tWindowH3.set_font_size(fontSize);
	tWindowH3.set_color(fontColor);
	sw.attach(tWindowH3);

	Point pWindowCpp{ pGraphH.x + 200, pGraphH.y + 150 };
	string sWindowCppTitle{ "Window.cpp:" };
	string sWindowCpp1{ "Window code" };
	int wWindowCpp = sWindowCpp1.size();
	int fieldWidthWindowCpp = wWindowCpp * charWidth + indentWidth * 2;
	Text tWindowCppTitle{ Point{pWindowCpp.x, pWindowCpp.y + indentHeigth}, sWindowCppTitle };
	tWindowCppTitle.set_font(fontBold);
	tWindowCppTitle.set_font_size(fontSize);
	tWindowCppTitle.set_color(fontColor);
	sw.attach(tWindowCppTitle);
	RectanglePPP2 rWindowCpp{ Point{pWindowCpp.x, pWindowCpp.y + fieldHeight}, fieldWidthWindowCpp, fieldHeight };
	rWindowCpp.set_color(borderColor);
	rWindowCpp.set_fill_color(fillColor);
	sw.attach(rWindowCpp);
	Text tWindowCpp1{ Point{pWindowCpp.x + indentWidth, pWindowCpp.y + fieldHeight + indentHeigth}, sWindowCpp1 };
	tWindowCpp1.set_font(fontBold);
	tWindowCpp1.set_font_size(fontSize);
	tWindowCpp1.set_color(fontColor);
	sw.attach(tWindowCpp1);

	Point pSimpleWindowH{ pWindowCpp.x + 50, pWindowCpp.y + 100 };
	string sSimpleWindowHTitle{ "Simple_window.h:" };
	string sSimpleWindowH1{ "// window interface:" };
	string sSimpleWindowH2{ "class Simple_window { ... };" };
	string sSimpleWindowH3{ "..." };
	int wSimpleWindowH = max(max(sSimpleWindowH1.size(), sSimpleWindowH2.size()), sSimpleWindowH3.size());
	int fieldWidthSimpleWindowH = wSimpleWindowH * charWidth + indentWidth * 2;
	Text tSimpleWindowHTitle{ Point{pSimpleWindowH.x, pSimpleWindowH.y + indentHeigth}, sSimpleWindowHTitle };
	tSimpleWindowHTitle.set_font(fontBold);
	tSimpleWindowHTitle.set_font_size(fontSize);
	tSimpleWindowHTitle.set_color(fontColor);
	sw.attach(tSimpleWindowHTitle);
	RectanglePPP2 rSimpleWindowH{ Point{pSimpleWindowH.x, pSimpleWindowH.y + fieldHeight},
		fieldWidthSimpleWindowH, fieldHeight * 3 };
	rSimpleWindowH.set_color(borderColor);
	rSimpleWindowH.set_fill_color(fillColor);
	sw.attach(rSimpleWindowH);
	Text tSimpleWindowH1{ Point{pSimpleWindowH.x + indentWidth,
		pSimpleWindowH.y + fieldHeight + indentHeigth}, sSimpleWindowH1 };
	tSimpleWindowH1.set_font(font);
	tSimpleWindowH1.set_font_size(fontSize);
	tSimpleWindowH1.set_color(fontColor);
	sw.attach(tSimpleWindowH1);
	Text tSimpleWindowH2{ Point{pSimpleWindowH.x + indentWidth,
		pSimpleWindowH.y + fieldHeight * 2 + indentHeigth}, sSimpleWindowH2 };
	tSimpleWindowH2.set_font(fontBold);
	tSimpleWindowH2.set_font_size(fontSize);
	tSimpleWindowH2.set_color(fontColor);
	sw.attach(tSimpleWindowH2);
	Text tSimpleWindowH3{ Point{pSimpleWindowH.x + indentWidth,
		pSimpleWindowH.y + fieldHeight * 3 + indentHeigth}, sSimpleWindowH3 };
	tSimpleWindowH3.set_font(fontBold);
	tSimpleWindowH3.set_font_size(fontSize);
	tSimpleWindowH3.set_color(fontColor);
	sw.attach(tSimpleWindowH3);

	Point pChapter12Cpp{ pGraphH.x, pGraphH.y + 400 };
	string sChapter12CppTitle{ "chapter12.cpp:" };
	string sChapter12Cpp1{ "#include \"Graph.h\"" };
	string sChapter12Cpp2{ "#include \"Simple_window.h\"" };
	string sChapter12Cpp3{ "int main() { ... }" };
	int wChapter12Cpp = max(max(sChapter12Cpp1.size(), sChapter12Cpp2.size()), sChapter12Cpp3.size());
	int fieldWidthChapter12Cpp = wChapter12Cpp * charWidth + indentWidth * 2;
	Text tChapter12CppTitle{ Point{pChapter12Cpp.x, pChapter12Cpp.y + indentHeigth}, sChapter12CppTitle };
	tChapter12CppTitle.set_font(fontBold);
	tChapter12CppTitle.set_font_size(fontSize);
	tChapter12CppTitle.set_color(fontColor);
	sw.attach(tChapter12CppTitle);
	RectanglePPP2 rChapter12Cpp{ Point{pChapter12Cpp.x, pChapter12Cpp.y + fieldHeight},
		fieldWidthChapter12Cpp, fieldHeight * 3 };
	rChapter12Cpp.set_color(borderColor);
	rChapter12Cpp.set_fill_color(fillColor);
	sw.attach(rChapter12Cpp);
	Text tChapter12Cpp1{ Point{pChapter12Cpp.x + indentWidth,
		pChapter12Cpp.y + fieldHeight + indentHeigth}, sChapter12Cpp1 };
	tChapter12Cpp1.set_font(font);
	tChapter12Cpp1.set_font_size(fontSize);
	tChapter12Cpp1.set_color(fontColor);
	sw.attach(tChapter12Cpp1);
	Text tChapter12Cpp2{ Point{pChapter12Cpp.x + indentWidth,
		pChapter12Cpp.y + fieldHeight * 2 + indentHeigth}, sChapter12Cpp2 };
	tChapter12Cpp2.set_font(fontBold);
	tChapter12Cpp2.set_font_size(fontSize);
	tChapter12Cpp2.set_color(fontColor);
	sw.attach(tChapter12Cpp2);
	Text tChapter12Cpp3{ Point{pChapter12Cpp.x + indentWidth,
		pChapter12Cpp.y + fieldHeight * 3 + indentHeigth}, sChapter12Cpp3 };
	tChapter12Cpp3.set_font(fontBold);
	tChapter12Cpp3.set_font_size(fontSize);
	tChapter12Cpp3.set_color(fontColor);
	sw.attach(tChapter12Cpp3);

	Point pGuiH{ pWindowH.x + 200, pWindowH.y + 130 };
	string sGuiHTitle{ "GUI.h:" };
	string sGuiH1{ "// GUI interface:" };
	string sGuiH2{ "struct In_box { ... };" };
	string sGuiH3{ "..." };
	int wGuiH = max(max(sGuiH1.size(), sGuiH2.size()), sGuiH3.size());
	int fieldWidthGuiH = wGuiH * charWidth + indentWidth * 2;
	Text tGuiHTitle{ Point{pGuiH.x, pGuiH.y + indentHeigth}, sGuiHTitle };
	tGuiHTitle.set_font(fontBold);
	tGuiHTitle.set_font_size(fontSize);
	tGuiHTitle.set_color(fontColor);
	sw.attach(tGuiHTitle);
	RectanglePPP2 rGuiH{ Point{pGuiH.x, pGuiH.y + fieldHeight}, fieldWidthGuiH, fieldHeight * 3 };
	rGuiH.set_color(borderColor);
	rGuiH.set_fill_color(fillColor);
	sw.attach(rGuiH);
	Text tGuiH1{ Point{pGuiH.x + indentWidth, pGuiH.y + fieldHeight + indentHeigth}, sGuiH1 };
	tGuiH1.set_font(font);
	tGuiH1.set_font_size(fontSize);
	tGuiH1.set_color(fontColor);
	sw.attach(tGuiH1);
	Text tGuiH2{ Point{pGuiH.x + indentWidth, pGuiH.y + fieldHeight * 2 + indentHeigth}, sGuiH2 };
	tGuiH2.set_font(fontBold);
	tGuiH2.set_font_size(fontSize);
	tGuiH2.set_color(fontColor);
	sw.attach(tGuiH2);
	Text tGuiH3{ Point{pGuiH.x + indentWidth, pGuiH.y + fieldHeight * 3 + indentHeigth}, sGuiH3 };
	tGuiH3.set_font(fontBold);
	tGuiH3.set_font_size(fontSize);
	tGuiH3.set_color(fontColor);
	sw.attach(tGuiH3);

	Point pGuiCpp{ pGuiH.x + 100, pGuiH.y + 150 };
	string sGuiCppTitle{ "GUI.cpp:" };
	string sGuiCpp1{ "GUI code" };
	int wGuiCpp = sGuiCpp1.size();
	int fieldWidthGuiCpp = wGuiCpp * charWidth + indentWidth * 2;
	Text tGuiCppTitle{ Point{pGuiCpp.x, pGuiCpp.y + indentHeigth}, sGuiCppTitle };
	tGuiCppTitle.set_font(fontBold);
	tGuiCppTitle.set_font_size(fontSize);
	tGuiCppTitle.set_color(fontColor);
	sw.attach(tGuiCppTitle);
	RectanglePPP2 rGuiCpp{ Point{pGuiCpp.x, pGuiCpp.y + fieldHeight}, fieldWidthGuiCpp, fieldHeight };
	rGuiCpp.set_color(borderColor);
	rGuiCpp.set_fill_color(fillColor);
	sw.attach(rGuiCpp);
	Text tGuiCpp1{ Point{pGuiCpp.x + indentWidth, pGuiCpp.y + fieldHeight + indentHeigth}, sGuiCpp1 };
	tGuiCpp1.set_font(fontBold);
	tGuiCpp1.set_font_size(fontSize);
	tGuiCpp1.set_color(fontColor);
	sw.attach(tGuiCpp1);

	Line lGraphH1{ Point{pGraphH.x + rGraphH.width() / 2, pGraphH.y + fieldHeight},
		Point{pPointH.x + rPointH.width() / 2, pPointH.y + fieldHeight + rPointH.height()} };
	lGraphH1.set_color(borderColor);
	sw.attach(lGraphH1);
	Line lGraphH2{ Point{pGraphH.x + rGraphH.width() / 2, pGraphH.y + fieldHeight},
		Point{pFLTKHeaders.x + 20, pFLTKHeaders.y + 20 + fieldHeight + rPointH.height()} };
	lGraphH2.set_color(borderColor);
	sw.attach(lGraphH2);
	Line lGraphCpp{ Point{pGraphCpp.x + rGraphCpp.width() - 10, pGraphCpp.y + fieldHeight},
		Point{pGraphH.x + rGraphH.width() / 2, pGraphH.y + fieldHeight + rGraphH.height()} };
	lGraphCpp.set_color(borderColor);
	sw.attach(lGraphCpp);
	Line lChapter12Cpp1{ Point{pChapter12Cpp.x + rChapter12Cpp.width() / 2, pChapter12Cpp.y + fieldHeight},
		Point{pGraphH.x + rGraphH.width() / 2 + 10, pGraphH.y + fieldHeight + rGraphH.height()} };
	lChapter12Cpp1.set_color(borderColor);
	sw.attach(lChapter12Cpp1);
	Line lChapter12Cpp2{ Point{pChapter12Cpp.x + rChapter12Cpp.width() / 2, pChapter12Cpp.y + fieldHeight},
		Point{pSimpleWindowH.x + 30, pSimpleWindowH.y + fieldHeight + rSimpleWindowH.height()} };
	lChapter12Cpp2.set_color(borderColor);
	sw.attach(lChapter12Cpp2);
	Line lWindowCpp{ Point{pWindowCpp.x + rWindowCpp.width() - 10, pWindowCpp.y + fieldHeight},
		Point{pWindowH.x + rWindowH.width() / 2 - 40, pWindowH.y + fieldHeight + rWindowH.height()} };
	lWindowCpp.set_color(borderColor);
	sw.attach(lWindowCpp);
	Line lSimpleWindowH1{ Point{pSimpleWindowH.x + rSimpleWindowH.width() / 2 + 40, pSimpleWindowH.y + fieldHeight},
		Point{pWindowH.x + rWindowH.width() / 2, pWindowH.y + fieldHeight + rWindowH.height()} };
	lSimpleWindowH1.set_color(borderColor);
	sw.attach(lSimpleWindowH1);
	Line lSimpleWindowH2{ Point{pSimpleWindowH.x + rSimpleWindowH.width() / 2 + 40, pSimpleWindowH.y + fieldHeight},
		Point{pGuiH.x + 20, pGuiH.y + fieldHeight + rGuiH.height()} };
	lSimpleWindowH2.set_color(borderColor);
	sw.attach(lSimpleWindowH2);
	Line lGuiCpp{ Point{pGuiCpp.x + rGuiCpp.width() - 10, pGuiCpp.y + fieldHeight},
		Point{pGuiH.x + rGuiH.width() / 2, pGuiH.y + fieldHeight + rGuiH.height()} };
	lGuiCpp.set_color(borderColor);
	sw.attach(lGuiCpp);
	Line lGuiH1{ Point{pGuiH.x + rGuiH.width() / 2 + 40, pGuiH.y + fieldHeight},
		Point{pWindowH.x + rWindowH.width() - 10, pWindowH.y + fieldHeight + rWindowH.height()} };
	lGuiH1.set_color(borderColor);
	sw.attach(lGuiH1);
	Line lGuiH2{ Point{pGuiH.x + rGuiH.width() / 2 + 40, pGuiH.y + fieldHeight},
		Point{pFLTKHeaders.x + 20 + rFLTKHeaders3.width() - 10,
		pFLTKHeaders.y + 20 + fieldHeight + rPointH.height()} };
	lGuiH2.set_color(borderColor);
	sw.attach(lGuiH2);
	Line lWindowH1{ Point{pWindowH.x + 20, pWindowH.y + fieldHeight},
		Point{pPointH.x + rPointH.width() - 30, pPointH.y + fieldHeight + rPointH.height()} };
	lWindowH1.set_color(borderColor);
	sw.attach(lWindowH1);
	Line lWindowH2{ Point{pWindowH.x + rWindowH.width() / 2, pWindowH.y + fieldHeight},
		Point{pFLTKHeaders.x + 20 + rFLTKHeaders3.width() / 2,
		pFLTKHeaders.y + 20 + fieldHeight + rPointH.height()} };
	lWindowH2.set_color(borderColor);
	sw.attach(lWindowH2);
	Line lFLTKCode{ Point{pFLTKCode.x, pFLTKCode.y + rFLTKCode1.height() / 2},
		Point{pFLTKHeaders.x + 20 + rFLTKHeaders3.width(),
		pFLTKHeaders.y + 20 + rFLTKHeaders3.height() / 2} };
	lFLTKCode.set_color(borderColor);
	sw.attach(lFLTKCode);

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
