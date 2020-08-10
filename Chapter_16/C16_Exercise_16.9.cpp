/* Exercise 16.9 */

/*
	Simple calculator
	This program implements a basic expression calculator.
	Input from cin; output to cout.
	The grammar for input is:

	Calculation:
		Statement
		Print
		Quit
		Help
		Calculation Statement
	Statement:
		Declaration
		Assignment
		Expression
	Print:
		";"
	Quit:
		"quit"
	Help:
		"help"
	Declaration:
		"let" Name "=" Expression
		"const" Name "=" Expression
	Assignment:
		Name "=" Expression
	Expression:
		Term
		Expression "+" Term
		Expression "–" Term
	Term:
		Primary
		Term "*" Primary
		Term "/" Primary
		Term "%" Primary
	Primary:
		Number
		Name
		"(" Expression ")"
		"–" Primary
		"+" Primary
		"sqrt(" Expression ")"
		"pow(" Expression "," Expression ")"
		"ln(" Expression ")"
	Number:
		floating-point-literal
	Name:
		string-literal
	
	Input comes from cin through the Token_stream called ts.
*/

#include<iostream>
#include<istream>
#include<ostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C16_Exercise_16.9.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;

#undef max
void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}

Token Token_stream::GetBuffer()
{
	if (BufferIsFull()) {
		return buffer[--nItems];
	}
	error("buffer underflow");
}

void Token_stream::unget(Token t)
{
	if (nItems < buffer.size()) {
		buffer[nItems++] = t;
	}
	else {
		buffer.push_back(t);
		nItems++;
	}
	return;
}

void printHelp(ostream& os)
{
	os << "Operators: '+', '-', '*', '/', '%' - remainder of division, '()'\n"
			"Acronyms: 'f' - floating-point number, 'i' - integer number, 's' - string, 'v' - value (number or expression)\n"
			"Enter 'sqrt(f)' to extract the square root of 'f'\n"
			"Enter 'pow(f,i)' to raise 'f' to the power of 'i'\n"
			"Enter 'ln(f)' to compute the natural logarithm of 'f'\n"
			"Enter 'let s = v' to declare a variable with the name 's' and the value 'v'\n"
			"Enter 'const s = v' to declare a constant with the name 's' and the value 'v'\n"
			"Enter 'from s' to enter data from the file 's' (enter 'from std' to enter data from 'standart input')\n"
			"Enter 'to s' to output data to the file 's' (enter 'to std' to output data to 'standart output')\n"
			"Enter ';' or press ENTER to get the result.\nEnter 'quit' to exit\n\n";
	return;
}

const char let = 'L';
const char constant = 'C';
const char help = 'H';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char sqroot = 'R';
const char power = 'P';
const char ln = 'E';
const char from = 'F';
const char to = 'T';

Token Token_stream::get(IOCalcStream& io)
{
	if (BufferIsFull()) return GetBuffer();
	char ch;
	if (io.ifs.is_open()) {
		while (io.ifs.get(ch) && isspace(ch)) {
			if (ch == '\n') return Token(print);
		}
	}
	else {
		while (io.iss.get(ch) && isspace(ch)) {
			if (ch == '\n') return Token(print);
		}
		if (io.iss.eof()) return Token(print);
	}
	switch (ch) {
	case print:
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	case ',':
		return Token(ch);
	case '.':
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
		if (io.ifs.is_open()) {
			io.ifs.unget();
			double val;
			io.ifs >> val;
			return Token(number, val);
		}
		else {
			io.iss.unget();
			double val;
			io.iss >> val;
			return Token(number, val);
		}
	}
	default:
		if (isalpha(ch) || ch == '_') {
			string s;
			s += ch;
			if (io.ifs.is_open()) {
				while (io.ifs.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
				io.ifs.unget();
			}
			else {
				while (io.iss.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
				io.iss.unget();
			}
			if (s == "help") return Token(help);
			if (s == "let") return Token(let);
			if (s == "const") return Token(constant);
			if (s == "quit") return Token(quit);
			if (s == "sqrt") return Token(sqroot);
			if (s == "pow") return Token(power);
			if (s == "ln") return Token(ln);
			if (s == "from") return Token(from);
			if (s == "to") return Token(to);
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(IOCalcStream& io, char c)
{
	while (nItems > 0) {
		if (c == buffer[--nItems].kind) {
			return;
		}
	}
	char ch;
	if (io.ifs.is_open()) {
		while (io.ifs >> ch)
			if (ch == c) return;
	}
	else {
		while (io.iss >> ch)
			if (ch == c) return;
	}
}

Symbol_table var;

double Symbol_table::get(string s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;
	error("get: undefined name ", s);
}

void Symbol_table::set(string s, double d)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) {
			if (var_table[i].isConst == false) {
				var_table[i].value = d;
				return;
			}
			error("the constant can't be changed");
		}
	error("set: undefined name ", s);
}

bool Symbol_table::is_declared(string s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return true;
	return false;
}

void Symbol_table::declare(Variable var)
{
	if (is_declared(var.name) == false) {
		var_table.push_back(var);
		return;
	}
	error(var.name, " declared twice");
}

void ChangeInputStream(IOCalcStream& io)
{
	string fn;
	string errMessage = "Error. Invalid file name\n";
	if (io.ifs.is_open()) {
		io.ifs >> fn;
		if (!io.ifs) {
			ClearInput(io.ifs);
			(io.ofs.is_open()) ? (io.ofs << errMessage) : (cerr << errMessage);
			error("ifstream failure");
		}
	}
	else {
		io.iss >> fn;
		if (!io.iss) {
			ClearInput(io.iss);
			(io.ofs.is_open()) ? (io.ofs << errMessage) : (cerr << errMessage);
			error("cin failure");
		}
	}
	if (io.ifs.is_open()) io.ifs.close();
	if (fn != "std") {
		io.ifs.open(fn);
		if (!io.ifs) {
			io.ifs.clear();
			io.ifs.close();
			error("Error. Can't open input file: ", fn);
		}
	}
	throw ChangeIOStream{};
}

void ChangeOutputStream(IOCalcStream& io)
{
	string fn;
	string errMessage = "Error. Invalid file name\n";
	if (io.ifs.is_open()) {
		io.ifs >> fn;
		if (!io.ifs) {
			ClearInput(io.ifs);
			(io.ofs.is_open()) ? (io.ofs << errMessage) : (cerr << errMessage);
			error("ifstream failure");
		}
	}
	else {
		io.iss >> fn;
		if (!io.iss) {
			ClearInput(io.iss);
			(io.ofs.is_open()) ? (io.ofs << errMessage) : (cerr << errMessage);
			error("cin failure");
		}
	}
	if (io.ofs.is_open()) io.ofs.close();
	if (fn != "std") {
		io.ofs.open(fn);
		if (!io.ofs) {
			io.ofs.clear();
			io.ofs.close();
			error("Error. Can't open output file: ", fn);
		}
	}
	throw ChangeIOStream{};
}

void GetInputUntilMark(IOCalcStream& io, const char mark)
{
	char c;
	if (io.ifs.is_open()) {
		while (io.ifs >> c && c != mark);
	}
	else {
		while (io.iss >> c && c != mark);
	}
}

double expression(Token_stream& ts, IOCalcStream& io);

double primary(Token_stream& ts, IOCalcStream& io)
{
	Token t = ts.get(io);
	switch (t.kind) {
	case '(':
	{	double d = expression(ts, io);
	t = ts.get(io);
	if (t.kind != ')') error("')' expected");
	return d;
	}
	case '-': {
		double d = primary(ts, io);
		if (d == 0) {
			return 0;
		}
		else {
			return -d;
		}
	}
	case '+':
		return primary(ts, io);
	case number:
		return t.value;
	case name:
		return var.get(t.name);
	case sqroot: {
		t = ts.get(io);
		if (t.kind != '(') error("'(' expected");
		double d = expression(ts, io);
		if (d < 0) error("square root of the negative number");
		t = ts.get(io);
		if (t.kind != ')') error("')' expected");
		return sqrt(d);
	}
	case power: {
		t = ts.get(io);
		if (t.kind != '(') error("'(' expected");
		double d = expression(ts, io);
		t = ts.get(io);
		if (t.kind != ',') error("',' expected");
		int i = narrow_cast<int>(expression(ts, io));
		t = ts.get(io);
		if (t.kind != ')') error("')' expected");
		return pow(d, i);
	}
	case ln: {
		t = ts.get(io);
		if (t.kind != '(') error("'(' expected");
		double d = expression(ts, io);
		if (d <= 0) error("the natural logarithm of the non positive number");
		t = ts.get(io);
		if (t.kind != ')') error("')' expected");
		return log(d);
	}
	default:
		error("primary expected");
	}
}

double term(Token_stream& ts, IOCalcStream& io)
{
	double left = primary(ts, io);
	while (true) {
		Token t = ts.get(io);
		switch (t.kind) {
		case '*':
			left *= primary(ts, io);
			break;
		case '/':
		{	double d = primary(ts, io);
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		case '%': {
			double d = primary(ts, io);
			if (d == 0) error("divide by zero");
			left = fmod(left, d);
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression(Token_stream& ts, IOCalcStream& io)
{
	double left = term(ts, io);
	while (true) {
		Token t = ts.get(io);
		switch (t.kind) {
		case '+':
			left += term(ts, io);
			break;
		case '-':
			left -= term(ts, io);
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration(Token_stream& ts, IOCalcStream& io, bool isConst)
{
	Token t = ts.get(io);
	if (t.kind != name) error("name expected in declaration");
	Token t2 = ts.get(io);
	if (t2.kind != '=') error("= missing in declaration of ", t.name);
	double d = expression(ts, io);
	var.declare(Variable(t.name, d, isConst));
	return d;
}

double statement(Token_stream& ts, IOCalcStream& io)
{
	Token t = ts.get(io);
	switch (t.kind) {
	case let:
		return declaration(ts, io, false);
	case constant:
		return declaration(ts, io, true);
	case name: {
		Token t2 = ts.get(io);
		if (t2.kind != '=') {
			ts.unget(t2);
			ts.unget(t);
			return expression(ts, io);
		}
		if (var.is_declared(t.name) == false) {
			error(t.name, " is not declared");
		}
		double d = expression(ts, io);
		var.set(t.name, d);
		return d;
	}
	case from: {
		ChangeInputStream(io);
	}
	case to: {
		ChangeOutputStream(io);
	}
	default:
		ts.unget(t);
		return expression(ts, io);
	}
}

void clean_up_mess(Token_stream& ts, IOCalcStream& io)
{
	ts.ignore(io, print);
}

const string result = "= ";

void Calculator::calculate(Token_stream& ts, IOCalcStream& io)
{
	Token t = ts.get(io);
	while (t.kind == print) t = ts.get(io);
	if (t.kind == ::quit) {
		quitPushed = true;
		return;
	}
	if (t.kind == ::help) {
		if (io.ofs.is_open()) printHelp(io.ofs);
		else ShowHelp();
		return;
	}
	ts.unget(t);
	double r = statement(ts, io);
	if (io.ofs.is_open()) io.ofs << result << r << endl;
	else {
		ostringstream oss;
		oss << r;
		obCalc.put(oss.str());
	}
}

int main() {
	constexpr int windowLength = 1280;
	constexpr int windowHeight = 1024;
	Calculator win{ Point{ 80, 0 }, windowLength, windowHeight, "Simple calculator" };
	var.declare(Variable("k", 1000, true));

	while (true) try {
		win.wait_for_button();
		return 0;
	}
	catch (runtime_error& e) {
		if (win.GetIOStream().ofs.is_open()) win.GetIOStream().ofs << e.what() << endl;
		else {
			ostringstream oss;
			oss << e.what();
			win.ShowError(oss.str());
		}
		clean_up_mess(win.GetTokenStream(), win.GetIOStream());
	}
	catch (ChangeIOStream& e) {}
	catch (exception& e) {
		return 1;
	}
	catch (...) {
		return 2;
	}
}

Calculator::Calculator(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	ibCalc{ Point{ x_max() / 2 - 200, 300 }, 400, 30, "Input:" },
	obCalc{ Point{ x_max() / 2 - 200, 330 }, 400, 30, "Result:" },
	buttonCalc{ Point{ x_max() / 2 - 200, 380 }, 400, 30, "Calculate",
		[](Address, Address pw) { reference_to<Calculator>(pw).calculate(); } },
	buttonQuit{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<Calculator>(pw).quit(); } },
	quitPushed{ false }
{
	textWelcolmeMessage1.set_color(Color::black);
	textWelcolmeMessage1.set_font_size(14);
	attach(textWelcolmeMessage1);
	textWelcolmeMessage2.set_color(Color::black);
	textWelcolmeMessage2.set_font_size(14);
	attach(textWelcolmeMessage2);
	textWelcolmeMessage3.set_color(Color::black);
	textWelcolmeMessage3.set_font_size(14);
	attach(textWelcolmeMessage3);
	textInvalidInput.set_color(Color::Transparency::invisible);
	textInvalidInput.set_font_size(14);
	attach(textInvalidInput);
	attach(help.textString1);
	attach(help.textString2);
	attach(help.textString3);
	attach(help.textString4);
	attach(help.textString5);
	attach(help.textString6);
	attach(help.textString7);
	attach(help.textString8);
	attach(help.textString9);
	attach(help.textString10);
	attach(help.textString11);
	attach(ibCalc);
	attach(obCalc);
	attach(buttonCalc);
	attach(buttonQuit);
}

void Calculator::ShowHelp()
{
	help.Show();
	redraw();
}

void Calculator::ShowError(const string& errorMessage)
{
	textInvalidInput.set_label(errorMessage);
	textInvalidInput.set_color(Color::dark_red);
	redraw();
}

void Calculator::HideError()
{
	textInvalidInput.set_color(Color::Transparency::invisible);
	redraw();
}

bool Calculator::wait_for_button()
{
	show();
	quitPushed = false;
	while (!quitPushed) Fl::wait();
	Fl::redraw();
	return quitPushed;
}

void Calculator::calculate()
{
	HideError();
	io.iss.clear();
	io.iss.str("");
	io.iss.str(ibCalc.get_string());
	calculate(ts, io);
}

void Calculator::quit()
{
	quitPushed = true;
	hide();
}

void MyText::draw_lines() const
{
	if (!color().visibility()) return;
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(font().as_int(), font_size());
	fl_draw(label().c_str(), point(0).x, point(0).y);
	fl_font(ofnt, osz);
}

Help::Help(Point x)
	: topLeft{ x }
{
	textString1.set_color(Color::Transparency::invisible);
	textString2.set_color(Color::Transparency::invisible);
	textString3.set_color(Color::Transparency::invisible);
	textString4.set_color(Color::Transparency::invisible);
	textString5.set_color(Color::Transparency::invisible);
	textString6.set_color(Color::Transparency::invisible);
	textString7.set_color(Color::Transparency::invisible);
	textString8.set_color(Color::Transparency::invisible);
	textString9.set_color(Color::Transparency::invisible);
	textString10.set_color(Color::Transparency::invisible);
	textString11.set_color(Color::Transparency::invisible);
}

void Help::Show()
{
	textString1.move(topLeft.x, topLeft.y + 20);
	textString2.move(topLeft.x, topLeft.y + 40);
	textString3.move(topLeft.x, topLeft.y + 60);
	textString4.move(topLeft.x, topLeft.y + 80);
	textString5.move(topLeft.x, topLeft.y + 100);
	textString6.move(topLeft.x, topLeft.y + 120);
	textString7.move(topLeft.x, topLeft.y + 140);
	textString8.move(topLeft.x, topLeft.y + 160);
	textString9.move(topLeft.x, topLeft.y + 180);
	textString10.move(topLeft.x, topLeft.y + 200);
	textString11.move(topLeft.x, topLeft.y + 220);
	
	textString1.set_color(Color::dark_blue);
	textString2.set_color(Color::dark_blue);
	textString3.set_color(Color::dark_blue);
	textString4.set_color(Color::dark_blue);
	textString5.set_color(Color::dark_blue);
	textString6.set_color(Color::dark_blue);
	textString7.set_color(Color::dark_blue);
	textString8.set_color(Color::dark_blue);
	textString9.set_color(Color::dark_blue);
	textString10.set_color(Color::dark_blue);
	textString11.set_color(Color::dark_blue);
	
	textString1.set_font_size(14);
	textString2.set_font_size(14);
	textString3.set_font_size(14);
	textString4.set_font_size(14);
	textString5.set_font_size(14);
	textString6.set_font_size(14);
	textString7.set_font_size(14);
	textString8.set_font_size(14);
	textString9.set_font_size(14);
	textString10.set_font_size(14);
	textString11.set_font_size(14);
}


#include <FL/Fl_Output.H>
string Graph_lib::In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	string s;
	return s.assign(pi.value());
}
