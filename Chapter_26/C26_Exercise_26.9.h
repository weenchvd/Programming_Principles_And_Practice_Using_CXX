/* Exercise 26.9 */

using namespace std;
using namespace Graph_lib;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

/*
	Command list:
	"Line"
	"RectanglePPP2"
	"Circle"
	"Closed_polyline"
	"Point"
*/

namespace TextInterface {
	namespace Command {
		const string line{ "Line" };
		const string rectangle{ "RectanglePPP2" };
		const string circle{ "Circle" };
		const string clpolyline{ "Closed_polyline" };
		const string point{ "Point" };
	}

	enum class TokenType {
		INVALID, NUMBER, LEFTPAR, RIGHTPAR, COMMA, POINT, LINE, RECTANGLE, CIRCLE, CLOSEDPOLYLINE
	};

	struct Token {
		TokenType type;
		int ival;
		//string sval;
		Token(TokenType tt) : type{ tt }, ival{ 0 } {}
		Token(TokenType tt, int value) : type{ tt }, ival{ value } {}
	};

	struct IOStream {
		istream* in;
		ostream* out;
		ostream* err;
		IOStream() : in{ &cin }, out{ &cout }, err{ &cerr } {}
		IOStream(istream& input, ostream& output, ostream& error)
			: in{ &input }, out{ &output }, err{ &error } {}
	};

	class TokenStream {
		vector<Token> buf;					// buffer
		int n;								// n items in the buffer
		IOStream ios;
	public:
		TokenStream() : n{ 0 } {}
		Token GetToken();
		void UngetToken(Token t);

		pair<bool, Token> GetBuffer();
		void ChangeStream(IOStream& iostream) { ios = iostream; }
		void Error(const string& s) { *ios.err << s << endl; }
		void Message(const string& s) { *ios.out << s << endl; }
	};

	void* Error(TokenStream& ts, const string& s) { ts.Error(s); return nullptr; }

	pair<bool, int> GetNumber(TokenStream& ts);
	pair<bool, Point> GetPoint(TokenStream& ts);

	Line* GetLine(TokenStream& ts);
	RectanglePPP2* GetRectangle(TokenStream& ts);
	Circle* GetCircle(TokenStream& ts);
	Closed_polyline* GetClosedPolyline(TokenStream& ts);
	Shape* GetShape(TokenStream& ts);
	
	Shape* ParseInput(const string& input, string& output);

	void PrintShapeCommand(ostream& os, Shape* sh);
}

namespace Graph_lib {
	constexpr int defaultFontSize = 14;
	constexpr int defaultFont = int(Font::helvetica);

	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);
		bool wait_for_button();
	private:
		In_box inboxInput;
		Button buttonDraw;
		Text textMessage{ Point{ 200, 55 }, "" };
		Out_box outboxOutput;

		Button buttonReset;
		Button buttonQuit;
		bool quitPushed;

		vector<Shape*> shapes;
		void DeleteShapes();

		void DrawShape();
		void Reset();
		void quit();
	};
}
