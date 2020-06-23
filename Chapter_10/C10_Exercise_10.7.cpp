/* Exercise 10.7 */

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
		integer-literal
	Name:
		string-literal
	
	Input comes from cin through the Token_stream called ts.
*/

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<cstdio>
#include"C10_Exercise_10.7.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

template<class R, class A> R narrow_cast_overflow(const A& a)
{
	R r = R(a);
	if (A(r) != a) error(string("integer variable overflow"));
	return r;
}

template<class R, class A> R narrow_cast_underflow(const A& a)
{
	R r = R(a);
	if (A(r) != a) error(string("underflow"));
	return r;
}

struct Token {
	char kind;
	int value;
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
			"Acronyms: 'i' - integer number, 's' - string, 'v' - value (number or expression)\n"
			"Enter 'sqrt(i)' to extract the square root of 'i'\n"
			"Enter 'pow(i1,i2)' to raise 'i1' to the power of 'i2'\n"
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
	case 'I':
	case 'V':
	case 'X':
	case 'L':
	case 'C':
	case 'D':
	case 'M': {
		cin.unget();
		RomanNumerals::Roman_int r;
		cin >> r;
		int val = r.as_int();
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
	int value;
	bool isConst;
	Variable(string n, int v, bool c) :name(n), value(v), isConst(c) { }
};

class Symbol_table {
public:
	int get(string s);
	void set(string s, int d);
	bool is_declared(string s);
	void declare(Variable var);
private:
	vector<Variable> var_table;
};

Symbol_table var;

int Symbol_table::get(string s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;
	error("get: undefined name ", s);
}

void Symbol_table::set(string s, int d)
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

int expression();

int primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(': {
		int n = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return n;
	}
	case '-': {
		int n = primary();
		if (n == 0) {
			return 0;
		}
		else {
			return -n;
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
		int n = expression();
		if (n < 0) error("square root of the negative number");
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return narrow_cast_underflow<int>(sqrt(n));
	}
	case power: {
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		int n = expression();
		t = ts.get();
		if (t.kind != ',') error("',' expected");
		int i = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		narrow_cast_underflow<long long int>(pow(n, i));
		return narrow_cast_overflow<int>(pow(n, i));
	}
	default:
		error("primary expected");
	}
}

int term()
{
	int left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left = narrow_cast_overflow<int>((long long int) left * primary());
			break;
		case '/': {
			int n = primary();
			if (n == 0) error("divide by zero");
			if (left % n) error("underflow: the quotient is not an integer");
			left /= n;
			break;
		}
		case '%': {
			int n = primary();
			if (n == 0) error("divide by zero");
			left %= n;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

int expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left = narrow_cast_overflow<int>((long long int) left + term());
			break;
		case '-':
			left = narrow_cast_overflow<int>((long long int) left - term());
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

int declaration(bool isConst)
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", t.name);
	int n = expression();
	var.declare(Variable(t.name, n, isConst));
	return n;
}

int statement()
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
		int n = expression();
		var.set(t.name, n);
		return n;
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
		cout << result << RomanNumerals::IntToRoman(statement()) << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
	catch (RomanNumerals::Roman_int::Invalid& e) {
		cerr << "Error. Roman is invalid\n";
		clean_up_mess();
	}
}

int main()

try {
	cout <<	"Welcome to our simple calculator\n"
			"Please enter expressions using integer numbers\n"
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

namespace RomanNumerals {
	Roman_int::Roman_int(int v)
		: value{ v }
	{
		if (v < 0 || v > int(Letter::MAX)) throw Roman_int::Invalid{};
	}

	ostream& operator<<(ostream& os, const Roman_int& r)
	{
		os << IntToRoman(r.as_int());
		return os;
	}

	string IntToRoman(const int integer)
	{
		int num = integer;
		if (num < 0 || num > int(Letter::MAX)) throw Roman_int::Invalid{};
		if (num == 0) return "N";
		string roman;
		int multiplier = 0;
		for (; num > 0; num /= 10) (multiplier > 0) ? multiplier *= 10 : multiplier = 1;
		for (; multiplier > 0; multiplier /= 10) {
			int i = integer / multiplier;
			i %= 10;
			switch (multiplier) {
			case 1000:
				roman += M[i];
				break;
			case 100:
				roman += C[i];
				break;
			case 10:
				roman += X[i];
				break;
			case 1:
				roman += I[i];
				break;
			default:
				throw Roman_int::Invalid{};
				break;
			}
		}
		return roman;
	}

	istream& operator>>(istream& is, Roman_int& r)
	{
		string roman;
		char ch;
		bool cond = true;
		while (cond && is.get(ch)) {
			cond = false;
			for (int i = 0; i < letters.size(); i++) {
				if (ch == letters[i]) {
					cond = true;
					roman += ch;
					break;
				}
			}
			if (cond == false) is.unget();
		}
		if (roman.size() <= 0) { ClearInput(cin); error("Error. Incorrect input"); }
		r = Roman_int(RomanToInt(roman));
		return is;
	}

	int RomanToInt(const string& roman)
	{
		char ch;
		int num = 0;
		int temp = 0;
		Letter previous = Letter::MAX;
		for (int i = 0; i < roman.size(); i++) {
			ch = roman[i];
			switch (ch) {
			case 'M':
				// case MM, MMM
				if (previous == Letter::M && temp <= maxLettersBefore * int(Letter::M)
					&& temp >= int(Letter::M)) {
					temp += int(Letter::M);
				}
				// case CM
				else if (previous == Letter::C && temp == int(Letter::C)) {
					temp = int(Letter::M) - int(Letter::C);
					previous = Letter::M;
				}
				// case M
				else if (previous > Letter::M) {
					num += temp;
					temp = int(Letter::M);
					previous = Letter::M;
				}
				else throw Roman_int::Invalid{};
				break;
			case 'D':
				// case CD
				if (previous == Letter::C && temp == int(Letter::C)) {
					temp = int(Letter::D) - int(Letter::C);
					previous = Letter::D;
				}
				// case D
				else if (previous > Letter::D && (temp >= int(Letter::M) || temp == 0)) {
					num += temp;
					temp = int(Letter::D);
					previous = Letter::D;
				}
				else throw Roman_int::Invalid{};
				break;
			case 'C':
				// case CC, CCC
				if (previous == Letter::C && temp <= maxLettersBefore * int(Letter::C)
					&& temp >= int(Letter::C)) {
					temp += int(Letter::C);
				}
				// case DC, DCC, DCCC
				else if (previous == Letter::D && temp <= int(Letter::D) + maxLettersBefore * int(Letter::C)
					&& temp >= int(Letter::D)) {
					temp += int(Letter::C);
				}
				// case XC
				else if (previous == Letter::X && temp == int(Letter::X)) {
					temp = int(Letter::C) - int(Letter::X);
					previous = Letter::C;
				}
				// case C
				else if (previous > Letter::C && (temp >= int(Letter::M) || temp == 0)) {
					num += temp;
					temp = int(Letter::C);
					previous = Letter::C;
				}
				else throw Roman_int::Invalid{};
				break;
			case 'L':
				// case XL
				if (previous == Letter::X && temp == int(Letter::X)) {
					temp = int(Letter::L) - int(Letter::X);
					previous = Letter::L;
				}
				// case L
				else if (previous > Letter::L && (temp >= int(Letter::C) || temp == 0)) {
					num += temp;
					temp = int(Letter::L);
					previous = Letter::L;
				}
				else throw Roman_int::Invalid{};
				break;
			case 'X':
				// case XX, XXX
				if (previous == Letter::X && temp <= maxLettersBefore * int(Letter::X)
					&& temp >= int(Letter::X)) {
					temp += int(Letter::X);
				}
				// case LX, LXX, LXXX
				else if (previous == Letter::L && temp <= int(Letter::L) + maxLettersBefore * int(Letter::X)
					&& temp >= int(Letter::L)) {
					temp += int(Letter::X);
				}
				// case IX
				else if (previous == Letter::I && temp == int(Letter::I)) {
					temp = int(Letter::X) - int(Letter::I);
					previous = Letter::X;
				}
				// case X
				else if (previous > Letter::X && (temp >= int(Letter::C) || temp == 0)) {
					num += temp;
					temp = int(Letter::X);
					previous = Letter::X;
				}
				else throw Roman_int::Invalid{};
				break;
			case 'V':
				// case IV
				if (previous == Letter::I && temp == int(Letter::I)) {
					temp = int(Letter::V) - int(Letter::I);
					previous = Letter::V;
				}
				// case V
				else if (previous > Letter::V && (temp >= int(Letter::X) || temp == 0)) {
					num += temp;
					temp = int(Letter::V);
					previous = Letter::V;
				}
				else throw Roman_int::Invalid{};
				break;
			case 'I':
				// case II, III
				if (previous == Letter::I && temp <= maxLettersBefore * int(Letter::I)
					&& temp >= int(Letter::I)) {
					temp += int(Letter::I);
				}
				// case VI, VII, VIII
				else if (previous == Letter::V && temp <= int(Letter::V) + maxLettersBefore * int(Letter::I)
					&& temp >= int(Letter::V)) {
					temp += int(Letter::I);
				}
				// case I
				else if (previous > Letter::I && (temp >= int(Letter::X) || temp == 0)) {
					num += temp;
					temp = int(Letter::I);
					previous = Letter::I;
				}
				else throw Roman_int::Invalid{};
				break;
			default:
				throw Roman_int::Invalid{};
				break;
			}
		}
		num += temp;
		return num;
	}

} // RomanNumerals

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
