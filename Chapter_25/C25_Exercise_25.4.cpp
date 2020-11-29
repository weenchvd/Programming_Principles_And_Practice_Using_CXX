/* Exercise 25.4 */

/*
	Simple calculator
	This program implements a basic expression calculator.
	Input from cin or file; output to cout or file.
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
	ExpL6:
		ExpL5
		ExpL6 "|" ExpL5
	ExpL5:
		ExpL4
		ExpL5 "^" ExpL4
	ExpL4:
		ExpL3
		ExpL4 "&" ExpL3
	ExpL3:
		ExpL2
		ExpL3 "+" ExpL2
		ExpL3 "–" ExpL2
	ExpL2:
		ExpL1
		ExpL2 "*" ExpL1
		ExpL2 "/" ExpL1
		ExpL2 "%" ExpL1
	ExpL1:
		Number
		Name
		"(" ExpL6 ")"
		"–" ExpL1
		"+" ExpL1
		"~" ExpL1
		"sqrt(" ExpL6 ")"
		"pow(" ExpL6 "," ExpL6 ")"
		"ln(" ExpL6 ")"
	Number:
		floating-point-literal
	Name:
		string-literal
	
	Input comes from cin or file through the Token_stream called ts.
*/

#include<iostream>
#include<istream>
#include<ostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

template<class R, class A> R narrow_cast(const A& a)
{
	R r = R(a);
	if (A(r) != a) error(string("info loss"));
	return r;
}

struct IOFStream {
	ifstream ifs;
	ofstream ofs;
	IOFStream() : ifs(), ofs() { }
};

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string s) : kind(ch), value(0), name(s) { }
};

class ChangeIOStream{};

class Token_stream {
	int nItems;
	vector<Token> buffer;
public:
	Token_stream() : nItems(0) { }
	Token_stream(istream& stream) : nItems(0) { }

	inline bool BufferIsFull() { if (nItems > 0) return true; return false; }
	Token GetBuffer();
	Token get(IOFStream& io);
	void unget(Token t);
	void ignore(IOFStream& io, char c);
};

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
	os	<< sp_2 << "Operators:" << endl
		<< sp_4 << "'+', '-', '*', '/', '%' - remainder of division, '()'" << endl
		<< sp_4 << "'~' - bitwise NOT, '&' - bitwise AND, '^' - bitwise XOR, '|' - bitwise OR" << endl
		<< sp_2 << "Precedence of operators" << endl
		<< sp_2 << "From greatest (top) to smallest (bottom) priority, operators are evaluated in the following order:" << endl
		<< sp_4 << "()" << endl
		<< sp_4 << "~ - 'unary prefix'" << endl
		<< sp_4 << "* / %" << endl
		<< sp_4 << "+ -" << endl
		<< sp_4 << "&" << endl
		<< sp_4 << "^" << endl
		<< sp_4 << "|" << endl
		<< sp_2 << "Acronyms:" << endl
		<< sp_4 << "'f' - floating-point number, 'i' - integer number, 's' - string, 'v' - value (number or expression)" << endl
		<< sp_2 << "Enter 'sqrt(f)' to extract the square root of 'f'" << endl
		<< sp_2 << "Enter 'pow(f,i)' to raise 'f' to the power of 'i'" << endl
		<< sp_2 << "Enter 'ln(f)' to compute the natural logarithm of 'f'" << endl
		<< sp_2 << "Enter 'let s = v' to declare a variable with the name 's' and the value 'v'" << endl
		<< sp_2 << "Enter 'const s = v' to declare a constant with the name 's' and the value 'v'" << endl
		<< sp_2 << "Enter 'from s' to enter data from the file 's' (enter 'from std' to enter data from 'standart input')" << endl
		<< sp_2 << "Enter 'to s' to output data to the file 's' (enter 'to std' to output data to 'standart output')" << endl
		<< sp_2 << "Enter ';' or press ENTER to get the result." << endl
		<< sp_2 << "Enter 'quit' to exit" << endl << endl;
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

Token Token_stream::get(IOFStream& io)
{
	if (BufferIsFull()) return GetBuffer();
	char ch;
	if (io.ifs.is_open()) {
		while (io.ifs.get(ch) && isspace(ch)) {
			if (ch == '\n') return Token(print);
		}
	}
	else {
		while (cin.get(ch) && isspace(ch)) {
			if (ch == '\n') return Token(print);
		}
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
	case '~':
	case '&':
	case '^':
	case '|':
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
			cin.unget();
			double val;
			cin >> val;
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
				while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
				cin.unget();
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

void Token_stream::ignore(IOFStream& io, char c)
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
		while (cin >> ch)
			if (ch == c) return;
	}
}

struct Variable {
	string name;
	double value;
	bool isConst;
	Variable(string n, double v, bool c) :name(n), value(v), isConst(c) { }
};

class Symbol_table {
public:
	double get(string s);
	void set(string s, double d);
	bool is_declared(string s);
	void declare(Variable var);
private:
	vector<Variable> var_table;
};

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

void ChangeInputStream(IOFStream& io)
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
		cin >> fn;
		if (!cin) {
			ClearInput(cin);
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

void ChangeOutputStream(IOFStream& io)
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
		cin >> fn;
		if (!cin) {
			ClearInput(cin);
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

void GetInputUntilMark(IOFStream& io, const char mark)
{
	char c;
	if (io.ifs.is_open()) {
		while (io.ifs >> c && c != mark);
	}
	else {
		while (cin >> c && c != mark);
	}
}

double ExpL6(Token_stream& ts, IOFStream& io);

double ExpL1(Token_stream& ts, IOFStream& io)
{
	Token t = ts.get(io);
	switch (t.kind) {
	case '(': {
		double d = ExpL6(ts, io);
		t = ts.get(io);
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-': {
		double d = ExpL1(ts, io);
		if (d == 0) {
			return 0;
		}
		else {
			return -d;
		}
	}
	case '+':
		return ExpL1(ts, io);
	case number:
		return t.value;
	case name:
		return var.get(t.name);
	case sqroot: {
		t = ts.get(io);
		if (t.kind != '(') error("'(' expected");
		double d = ExpL6(ts, io);
		if (d < 0) error("square root of the negative number");
		t = ts.get(io);
		if (t.kind != ')') error("')' expected");
		return sqrt(d);
	}
	case power: {
		t = ts.get(io);
		if (t.kind != '(') error("'(' expected");
		double d = ExpL6(ts, io);
		t = ts.get(io);
		if (t.kind != ',') error("',' expected");
		int i = narrow_cast<int>(ExpL6(ts, io));
		t = ts.get(io);
		if (t.kind != ')') error("')' expected");
		return pow(d, i);
	}
	case ln: {
		t = ts.get(io);
		if (t.kind != '(') error("'(' expected");
		double d = ExpL6(ts, io);
		if (d <= 0) error("the natural logarithm of the non positive number");
		t = ts.get(io);
		if (t.kind != ')') error("')' expected");
		return log(d);
	}
	default:
		error("ExpL1 expected");
	}
}

double ExpL2(Token_stream& ts, IOFStream& io)
{
	double left = ExpL1(ts, io);
	while (true) {
		Token t = ts.get(io);
		switch (t.kind) {
		case '*':
			left *= ExpL1(ts, io);
			break;
		case '/':
		{	double d = ExpL1(ts, io);
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		case '%': {
			double d = ExpL1(ts, io);
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

double ExpL3(Token_stream& ts, IOFStream& io)
{
	double left = ExpL2(ts, io);
	while (true) {
		Token t = ts.get(io);
		switch (t.kind) {
		case '+':
			left += ExpL2(ts, io);
			break;
		case '-':
			left -= ExpL2(ts, io);
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double ExpL4(Token_stream& ts, IOFStream& io)
{
	double left = ExpL3(ts, io);
	while (true) {
		Token t = ts.get(io);
		switch (t.kind) {
		case '&': {
			int i = narrow_cast<int>(left);
			left = i & narrow_cast<int>(ExpL3(ts, io));
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double ExpL5(Token_stream& ts, IOFStream& io)
{
	double left = ExpL4(ts, io);
	while (true) {
		Token t = ts.get(io);
		switch (t.kind) {
		case '^': {
			int i = narrow_cast<int>(left);
			left = i ^ narrow_cast<int>(ExpL4(ts, io));
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double ExpL6(Token_stream& ts, IOFStream& io)
{
	double left = ExpL5(ts, io);
	while (true) {
		Token t = ts.get(io);
		switch (t.kind) {
		case '|': {
			int i = narrow_cast<int>(left);
			left = i | narrow_cast<int>(ExpL5(ts, io));
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration(Token_stream& ts, IOFStream& io, bool isConst)
{
	Token t = ts.get(io);
	if (t.kind != name) error("name expected in declaration");
	Token t2 = ts.get(io);
	if (t2.kind != '=') error("= missing in declaration of ", t.name);
	double d = ExpL6(ts, io);
	var.declare(Variable(t.name, d, isConst));
	return d;
}

double statement(Token_stream& ts, IOFStream& io)
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
			return ExpL6(ts, io);
		}
		if (var.is_declared(t.name) == false) {
			error(t.name, " is not declared");
		}
		double d = ExpL6(ts, io);
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
		return ExpL6(ts, io);
	}
}

void clean_up_mess(Token_stream& ts, IOFStream& io)
{
	ts.ignore(io, print);
}

const string prompt = "> ";
const string result = "= ";

void calculate(IOFStream& io)
{
	Token_stream ts;
	var.declare(Variable("k", 1000, true));
	while (true) try {
		if (!io.ifs.is_open()) {
			cout << prompt;
		}
		Token t = ts.get(io);
		while (t.kind == print) t = ts.get(io);
		if (t.kind == quit) return;
		if (t.kind == help) {
			if (io.ofs.is_open()) printHelp(io.ofs);
			else printHelp(cout);
			continue;
		}
		ts.unget(t);
		double r = statement(ts, io);
		if (io.ofs.is_open()) io.ofs << result << r << endl;
		else cout << result << r << endl;
	}
	catch (runtime_error& e) {
		if (io.ofs.is_open()) io.ofs << e.what() << endl;
		else cerr << e.what() << endl;
		clean_up_mess(ts, io);
	}
	catch (ChangeIOStream& e) { }
}

int main() {
	IOFStream io;
	try {
		cout << "Welcome to our simple calculator\n"
			"Please enter expressions using floating-point numbers\n"
			"Enter 'help' to get help\n";
		calculate(io);
		return 0;
	}
	catch (exception& e) {
		if (io.ofs.is_open()) {
			io.ofs << "exception: " << e.what() << endl;
			GetInputUntilMark(io, print);
		}
		else {
			cerr << "exception: " << e.what() << endl;
			GetInputUntilMark(io, print);
		}
		return 1;
	}
	catch (...) {
		if (io.ofs.is_open()) {
			io.ofs << "exception\n";
			GetInputUntilMark(io, print);
		}
		else {
			cerr << "exception\n";
			GetInputUntilMark(io, print);
		}
		return 2;
	}
}
