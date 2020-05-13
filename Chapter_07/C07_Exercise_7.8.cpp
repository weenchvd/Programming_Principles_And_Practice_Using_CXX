/* Exercise 7.8 */

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
	Number:
		floating-point-literal
	Name:
		string-literal
	
	Input comes from cin through the Token_stream called ts.
*/

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>

using namespace std;

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

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string s) : kind(ch), name(s) { }
};

class Token_stream {
	int nItems;
	vector<Token> buffer;
public:
	Token_stream() :nItems(0) { }

	inline bool BufferIsFull() { if (nItems > 0) return true; return false; }
	Token GetBuffer();
	Token get();
	void unget(Token t);
	void ignore(char c);
};

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

void printHelp()
{
	cout << "Operators: '+', '-', '*', '/', '%' - remainder of division, '()'\n"
			"Acronyms: 'f' - floating-point number, 'i' - integer number, 's' - string, 'v' - value (number or expression)\n"
			"Enter 'sqrt(f)' to extract the square root of 'f'\n"
			"Enter 'pow(f,i)' to raise 'f' to the power of 'i'\n"
			"Enter 'let s = v' to declare a variable with the name 's' and the value 'v'\n"
			"Enter 'const s = v' to declare a constant with the name 's' and the value 'v'\n"
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

Token Token_stream::get()
{
	if (BufferIsFull()) return GetBuffer();
	char ch;
	while (cin.get(ch) && isspace(ch)) {
		if (ch == '\n') return Token(print);
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
	case '9':
	{	cin.unget();
	double val;
	cin >> val;
	return Token(number, val);
	}
	default:
		if (isalpha(ch) || ch == '_') {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			cin.unget();
			if (s == "help") return Token(help);
			if (s == "let") return Token(let);
			if (s == "const") return Token(constant);
			if (s == "quit") return Token(quit);
			if (s == "sqrt") return Token(sqroot);
			if (s == "pow") return Token(power);
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	while (nItems > 0) {
		if (c == buffer[--nItems].kind) {
			return;
		}
	}
	char ch;
	while (cin >> ch)
		if (ch == c) return;
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

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
	t = ts.get();
	if (t.kind != ')') error("')' expected");
	return d;
	}
	case '-': {
		double d = primary();
		if (d == 0) {
			return 0;
		}
		else {
			return -d;
		}
	}
	case '+':
		return primary();
	case number:
		return t.value;
	case name:
		return var.get(t.name);
	case sqroot: {
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		double d = expression();
		if (d < 0) error("square root of the negative number");
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return sqrt(d);
	}
	case power: {
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		double d = expression();
		t = ts.get();
		if (t.kind != ',') error("',' expected");
		int i = narrow_cast<int>(expression());
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return pow(d, i);
	}
	default:
		error("primary expected");
	}
}

double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		case '%': {
			double d = primary();
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

double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration(bool isConst)
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", t.name);
	double d = expression();
	var.declare(Variable(t.name, d, isConst));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration(false);
	case constant:
		return declaration(true);
	case name: {
		Token t2 = ts.get();
		if (t2.kind != '=') {
			ts.unget(t2);
			ts.unget(t);
			return expression();
		}
		if (var.is_declared(t.name) == false) {
			error(t.name, " is not declared");
		}
		double d = expression();
		var.set(t.name, d);
		return d;
	}
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	var.declare(Variable("k", 1000, true));
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		if (t.kind == help) {
			printHelp();
			continue;
		}
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()

try {
	cout <<	"Welcome to our simple calculator\n"
			"Please enter expressions using floating-point numbers\n"
			"Enter 'help' to get help\n";
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != print);
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != print);
	return 2;
}

