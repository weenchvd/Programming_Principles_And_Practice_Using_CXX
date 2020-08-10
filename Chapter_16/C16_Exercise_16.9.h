/* Exercise 16.9 */

using namespace std;
using namespace Graph_lib;

template<class R, class A> R narrow_cast(const A& a)
{
	R r = R(a);
	if (A(r) != a) error(string("info loss"));
	return r;
}

struct IOCalcStream {
	istringstream iss;
	ifstream ifs;
	ofstream ofs;
	IOCalcStream() {}
};

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string s) : kind(ch), value(0), name(s) { }
};

class ChangeIOStream {};

class Token_stream {
	int nItems;
	vector<Token> buffer;
public:
	Token_stream() : nItems(0) { }
	Token_stream(istream& stream) : nItems(0) { }

	inline bool BufferIsFull() { if (nItems > 0) return true; return false; }
	Token GetBuffer();
	Token get(IOCalcStream& io);
	void unget(Token t);
	void ignore(IOCalcStream& io, char c);
};

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

namespace Graph_lib {
	struct MyText : Text {
		MyText(Point x, const string& s)
			: Text(x, s) { }
		void draw_lines() const;
	};

	struct Help {
		Help(Point x);
		void Show();

		MyText textString1{ Point{0, 0},
			"Operators: '+', '-', '*', '/', '%' - remainder of division, '()'" };
		MyText textString2{ Point{0, 0},
			"Acronyms: 'f' - floating-point number, 'i' - integer number, 's' - string, 'v' - value (number or expression)" };
		MyText textString3{ Point{0, 0},
			"Enter 'sqrt(f)' to extract the square root of 'f'" };
		MyText textString4{ Point{0, 0},
			"Enter 'pow(f,i)' to raise 'f' to the power of 'i'" };
		MyText textString5{ Point{0, 0},
			"Enter 'ln(f)' to compute the natural logarithm of 'f'" };
		MyText textString6{ Point{0, 0},
			"Enter 'let s = v' to declare a variable with the name 's' and the value 'v'" };
		MyText textString7{ Point{0, 0},
			"Enter 'const s = v' to declare a constant with the name 's' and the value 'v'" };
		MyText textString8{ Point{0, 0},
			"Enter 'from s' to enter data from the file 's' (enter 'from std' to enter data from 'standart input')" };
		MyText textString9{ Point{0, 0},
			"Enter 'to s' to output data to the file 's' (enter 'to std' to output data to 'standart output')" };
		MyText textString10{ Point{0, 0},
			"Press the button \"Caclulate\" to get the result" };
		MyText textString11{ Point{0, 0},
			"Press the button \"Quit\" to exit" };
	private:
		Point topLeft;
	};

	struct Calculator : Window {
		Calculator(Point xy, int w, int h, const string& title);
		void ShowHelp();
		void ShowError(const string& errorMessage);
		void HideError();
		IOCalcStream& GetIOStream() { return io; }
		Token_stream& GetTokenStream() { return ts; }
		bool wait_for_button();
	private:
		IOCalcStream io;
		Token_stream ts;

		Text textWelcolmeMessage1{ Point{x_max() / 2 - 200, 100}, "Welcome to our simple calculator" };
		Text textWelcolmeMessage2{ Point{x_max() / 2 - 200, 120}, "Please enter expressions using floating-point numbers" };
		Text textWelcolmeMessage3{ Point{x_max() / 2 - 200, 140}, "Enter 'help' and press \"Caclulate\" to get help" };
		MyText textInvalidInput{ Point{x_max() / 2 - 195, 290 }, "Invalid input" };

		Help help{ Point { x_max() / 2 - 200, 500 } };

		In_box ibCalc;
		Out_box obCalc;

		Button buttonCalc;
		Button buttonQuit;

		bool quitPushed;

		void calculate(Token_stream& ts, IOCalcStream& io);
		void calculate();
		void quit();
	};
}
