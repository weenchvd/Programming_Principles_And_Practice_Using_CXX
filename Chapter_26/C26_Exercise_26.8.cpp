/* Exercise 26.8 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<iomanip>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C26_Exercise_26.8.h"

using namespace std;

inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
try {
	constexpr int windowLength = 1280;
	constexpr int windowHeight = 1024;

	My_window mw{ Point{ 80, 0 }, windowLength, windowHeight,
		"Text-based interface for the graphics interface library" };

	mw.wait_for_button();
	return 0;
}
catch (runtime_error& e) {
	cerr << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "Error. Exception\n";
	return 2;
}

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	inboxInput{ Point{ 200, 0 }, 600, 20, "Input:" },
	buttonDraw{ Point{ 810, 0 }, 70, 20, "Draw",
		[](Address, Address pw) { reference_to<My_window>(pw).DrawShape(); } },
	
	buttonReset{ Point{ x_max() - 150, 0 }, 70, 20, "Reset",
		[](Address, Address pw) { reference_to<My_window>(pw).Reset(); } },
	buttonQuit{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<My_window>(pw).quit(); } },
	quitPushed{ false }
{
	attach(inboxInput);
	attach(buttonDraw);
	textMessage.set_font(defaultFont);
	textMessage.set_font_size(defaultFontSize);
	attach(textMessage);
	attach(buttonReset);
	attach(buttonQuit);
}

void My_window::DeleteShapes()
{
	for (Shape* sh : shapes) {
		delete sh;
	}
}

void My_window::DrawShape()
{
	string command = inboxInput.get_string();
	string message;
	Shape* shape = TextInterface::ParseInput(command, message);
	if (shape != nullptr) {
		shapes.push_back(shape);
		attach(*shape);
	}
	if (message.size() > 0) {
		textMessage.set_label(message);
		textMessage.set_color(Color::dark_red);
	}
	else {
		textMessage.set_label("OK");
		textMessage.set_color(Color::dark_green);
	}
	redraw();
}

void My_window::Reset()
{
	textMessage.set_label("");
	for (Shape* sh : shapes) {
		detach(*sh);
	}
	DeleteShapes();
	shapes = vector<Shape*>{};
	redraw();
}

bool My_window::wait_for_button()
{
	show();
	quitPushed = false;
	while (!quitPushed) Fl::wait();
	Fl::redraw();
	return quitPushed;
}

void My_window::quit()
{
	quitPushed = true;
	DeleteShapes();
	hide();
}

#include <FL/Fl_Output.H>
string Graph_lib::In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	string s;
	return s.assign(pi.value());
}

TextInterface::Token TextInterface::TokenStream::GetToken()
{
	pair<bool, Token> buffer = GetBuffer();
	if (buffer.first == true) return buffer.second;
	char ch;
	while (ios.in->get(ch) && isspace(ch));
	switch (ch) {
	case '(': return Token{ TokenType::LEFTPAR };
	case ')': return Token{ TokenType::RIGHTPAR };
	case ',': return Token{ TokenType::COMMA };
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9': {
		ios.in->unget();
		int number;
		*ios.in >> number;
		if (!(*ios.in)) return Token{ TokenType::INVALID };
		return Token{ TokenType::NUMBER, number };
	}
	default: {
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (ios.in->get(ch) && (isalnum(ch) || ch == '_')) s += ch;
			if (!(*ios.in)) return Token{ TokenType::INVALID };
			ios.in->unget();
			if (s == "Line") return Token{ TokenType::LINE };
			if (s == "RectanglePPP2") return Token{ TokenType::RECTANGLE };
			if (s == "Circle") return Token{ TokenType::CIRCLE };
			if (s == "Closed_polyline") return Token{ TokenType::CLOSEDPOLYLINE };
			if (s == "Point") return Token{ TokenType::POINT };
			return Token{ TokenType::INVALID };
		}
		else return Token{ TokenType::INVALID };
	}
	}
}

void TextInterface::TokenStream::UngetToken(TextInterface::Token t)
{
	if (n < buf.size()) buf[n] = t;
	else buf.push_back(t);
	++n;
}

pair<bool, TextInterface::Token> TextInterface::TokenStream::GetBuffer()
{
	if (n > 0) return { true, buf[--n] };
	return { false, Token{ TokenType::INVALID } };
}

pair<bool, int> TextInterface::GetNumber(TokenStream& ts)
{
	pair<bool, int> failure{ false, 0 };
	Token t = ts.GetToken();
	if (t.type != TokenType::NUMBER) return failure;
	return { true, t.ival };
}

pair<bool, Point> TextInterface::GetPoint(TokenStream& ts)
{
	pair<bool, Point> failure{ false, Point{ 0, 0 } };
	Token t = ts.GetToken();
	if (t.type != TokenType::POINT) return failure;
	t = ts.GetToken();
	if (t.type != TokenType::LEFTPAR) return failure;
	pair<bool, int> p1 = GetNumber(ts);
	if (p1.first == false) return failure;
	t = ts.GetToken();
	if (t.type != TokenType::COMMA) return failure;
	pair<bool, int> p2 = GetNumber(ts);
	if (p2.first == false) return failure;
	t = ts.GetToken();
	if (t.type != TokenType::RIGHTPAR) return failure;
	return { true, Point{ p1.second, p2.second } };
}

Line* TextInterface::GetLine(TokenStream& ts)
{
	const string err{ "Invalid token. Line" };
	Token t = ts.GetToken();
	if (t.type != TokenType::LEFTPAR) return static_cast<Line*>(Error(ts, err));
	pair<bool, Point> p1 = GetPoint(ts);
	if (p1.first == false) return static_cast<Line*>(Error(ts, err));
	t = ts.GetToken();
	if (t.type != TokenType::COMMA) return static_cast<Line*>(Error(ts, err));
	pair<bool, Point> p2 = GetPoint(ts);
	if (p2.first == false) return nullptr;
	t = ts.GetToken();
	if (t.type != TokenType::RIGHTPAR) return static_cast<Line*>(Error(ts, err));
	return new Line{ p1.second, p2.second };
}

RectanglePPP2* TextInterface::GetRectangle(TokenStream& ts)
{
	const string err{ "Invalid token. RectanglePPP2" };
	Token t = ts.GetToken();
	if (t.type != TokenType::LEFTPAR)
		return static_cast<RectanglePPP2*>(Error(ts, err));
	pair<bool, Point> p1 = GetPoint(ts);
	if (p1.first == false)
		return static_cast<RectanglePPP2*>(Error(ts, err));
	t = ts.GetToken();
	if (t.type != TokenType::COMMA)
		return static_cast<RectanglePPP2*>(Error(ts, err));
	t = ts.GetToken();
	if (t.type == TokenType::POINT) {
		ts.UngetToken(t);
		pair<bool, Point> p2 = GetPoint(ts);
		if (p2.first == false)
			return static_cast<RectanglePPP2*>(Error(ts, err));
		t = ts.GetToken();
		if (t.type != TokenType::RIGHTPAR)
			return static_cast<RectanglePPP2*>(Error(ts, err));
		return new RectanglePPP2{ p1.second, p2.second };
	}
	else if (t.type == TokenType::NUMBER) {
		ts.UngetToken(t);
		pair<bool, int> p2 = GetNumber(ts);
		if (p2.first == false)
			return static_cast<RectanglePPP2*>(Error(ts, err));
		t = ts.GetToken();
		if (t.type != TokenType::COMMA)
			return static_cast<RectanglePPP2*>(Error(ts, err));
		pair<bool, int> p3 = GetNumber(ts);
		if (p3.first == false)
			return static_cast<RectanglePPP2*>(Error(ts, err));
		t = ts.GetToken();
		if (t.type != TokenType::RIGHTPAR)
			return static_cast<RectanglePPP2*>(Error(ts, err));
		return new RectanglePPP2{ p1.second, p2.second, p3.second };
	}
	else return static_cast<RectanglePPP2*>(Error(ts, err));
}

Circle* TextInterface::GetCircle(TokenStream& ts)
{
	const string err{ "Invalid token. Circle" };
	Token t = ts.GetToken();
	if (t.type != TokenType::LEFTPAR)
		return static_cast<Circle*>(Error(ts, err));
	pair<bool, Point> p1 = GetPoint(ts);
	if (p1.first == false)
		return static_cast<Circle*>(Error(ts, err));
	t = ts.GetToken();
	if (t.type != TokenType::COMMA)
		return static_cast<Circle*>(Error(ts, err));
	pair<bool, int> p2 = GetNumber(ts);
	if (p2.first == false)
		return static_cast<Circle*>(Error(ts, err));
	t = ts.GetToken();
	if (t.type != TokenType::RIGHTPAR)
		return static_cast<Circle*>(Error(ts, err));
	return new Circle{ p1.second, p2.second };
}

Closed_polyline* TextInterface::GetClosedPolyline(TokenStream& ts)
{
	constexpr int minPoints = 3;			// minimum number of points for a Closed_polyline
	const string err{ "Invalid token. Closed_polyline" };
	Token t = ts.GetToken();
	if (t.type != TokenType::LEFTPAR)
		return static_cast<Closed_polyline*>(Error(ts, err));
	vector<Point> vp;
	while (true) {
		pair<bool, Point> p = GetPoint(ts);
		if (p.first == false)
			return static_cast<Closed_polyline*>(Error(ts, err));
		vp.push_back(p.second);
		t = ts.GetToken();
		if (t.type == TokenType::RIGHTPAR)
			break;
		if (t.type != TokenType::COMMA)
			return static_cast<Closed_polyline*>(Error(ts, err));
	}
	if (vp.size() < minPoints)
		return static_cast<Closed_polyline*>(Error(ts,
			"Minimum number of points for a 'Closed_polyline' must be 3"));
	Closed_polyline* polyline = new Closed_polyline{};
	if (polyline == nullptr)
		return static_cast<Closed_polyline*>(Error(ts, "'Closed_polyline' is not allocated"));
	for (const Point& p : vp) {
		polyline->add(p);
	}
	return polyline;
}

Shape* TextInterface::GetShape(TokenStream& ts)
{
	Token t = ts.GetToken();
	switch (t.type) {
	case TokenType::LINE: {
		return GetLine(ts);
	}
	case TokenType::RECTANGLE: {
		return GetRectangle(ts);
	}
	case TokenType::CIRCLE: {
		return GetCircle(ts);
	}
	case TokenType::CLOSEDPOLYLINE: {
		return GetClosedPolyline(ts);
	}
	case TokenType::INVALID:
	default:
		ts.Error("Invalid token");
		return nullptr;
	}
}

Shape* TextInterface::ParseInput(const string& input, string& output)
{
	istringstream iss{ input };
	ostringstream oss;
	TokenStream ts;
	IOStream ios{ iss, oss, oss };
	ts.ChangeStream(ios);
	Shape* shape = GetShape(ts);
	output = oss.str();
	return shape;
}
