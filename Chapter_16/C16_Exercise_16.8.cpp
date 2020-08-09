/* Exercise 16.8 */

#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C16_Exercise_16.8.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	string file = "C16_Exercise_16.8_rates.txt";
	ifstream ifs;
	ifs.open(file);
	if (!ifs) error("Error. Can't open input file: ", file);
	Currency main;

	constexpr int windowLength = 1280;
	constexpr int windowHeight = 1024;
	My_window mw{ Point{ 80, 0 }, windowLength, windowHeight, "Currency converter" };

	if (ifs >> main) {
		mw.cr.SetMainCurrency(main);
	}
	else error("Read error");
	for (Currency temp; ifs >> temp; ) {
		mw.cr.AddCurrency(temp);
	}
	if (ifs.eof());
	else error("Read error");


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

bool CurrencyRate::Get(const string& symbolName, Currency& currency) const
{
	if (symbolName == main.symbol) {
		currency = main;
		return true;
	}
	for (int i = 0; i < cur.size(); i++) {
		if (symbolName == cur[i].symbol) {
			currency = cur[i];
			return true;
		}
	}
	return false;
}

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	ibCurrency{ Point{ x_max() / 2 - 200, 300 }, 100, 30, "EUR" },
	obCurrency{ Point{ x_max() / 2 + 100, 300 }, 100, 30, "EUR"},
	menuSrc{ Point{x_max() / 2 - 200, 330 }, 100, 30, Menu::Kind::vertical, "" },
	menuDst{ Point{x_max() / 2 + 100, 330 }, 100, 30, Menu::Kind::vertical, "" },
	buttonConvert{ Point{x_max() / 2 - 50, 330 }, 100, 30, "Convert",
		[](Address, Address pw) { reference_to<My_window>(pw).ConvertCurrency(); } },
	buttonMenuSrc{ Point{x_max() / 2 - 200, 330 }, 100, 30, "Currency",
		[](Address, Address pw) { reference_to<My_window>(pw).MenuSourcePressed(); } },
	buttonMenuDst{ Point{x_max() / 2 + 100, 330 }, 100, 30, "Currency",
		[](Address, Address pw) { reference_to<My_window>(pw).MenuDestinationPressed(); } },
	buttonQuit{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<My_window>(pw).quit(); } },
	quitPushed{ false }
{
	textSourceName.set_color(Color::black);
	textSourceName.set_font_size(14);
	attach(textSourceName);
	textDestinationName.set_color(Color::black);
	textDestinationName.set_font_size(14);
	attach(textDestinationName);
	textInvalidInput.set_color(Color::Transparency::invisible);
	textInvalidInput.set_font_size(14);
	attach(textInvalidInput);
	attach(ibCurrency);
	attach(obCurrency);
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "EUR",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToEUR(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "AUD",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToAUD(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "BYN",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToBYN(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "CAD",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToCAD(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "CHF",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToCHF(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "CNY",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToCNY(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "GBP",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToGBP(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "JPY",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToJPY(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "KPW",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToKPW(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "KRW",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToKRW(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "NZD",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToNZD(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "RUB",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToRUB(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "SGD",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToSGD(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "UAH",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToUAH(); } });
	menuSrc.attach(new Button{ Point {0, 0}, 0, 0, "USD",
		[](Address, Address pw) { reference_to<My_window>(pw).SetSourceToUSD(); } });
	attach(menuSrc);
	menuSrc.hide();
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "EUR",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToEUR(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "AUD",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToAUD(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "BYN",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToBYN(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "CAD",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToCAD(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "CHF",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToCHF(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "CNY",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToCNY(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "GBP",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToGBP(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "JPY",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToJPY(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "KPW",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToKPW(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "KRW",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToKRW(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "NZD",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToNZD(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "RUB",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToRUB(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "SGD",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToSGD(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "UAH",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToUAH(); } });
	menuDst.attach(new Button{ Point {0, 0}, 0, 0, "USD",
		[](Address, Address pw) { reference_to<My_window>(pw).SetDestinationToUSD(); } });
	attach(menuDst);
	menuDst.hide();
	attach(buttonConvert);
	attach(buttonMenuSrc);
	attach(buttonMenuDst);
	attach(buttonQuit);
}

void My_window::ConvertCurrency()
{
	Currency source;
	cr.Get(ibCurrency.label, source);
	Currency destination;
	cr.Get(obCurrency.label, destination);
	Currency main;
	cr.Get(main);
	double sourceValue;
	istringstream iss;
	iss.str(ibCurrency.get_string());
	if (iss >> sourceValue) {
		textInvalidInput.set_color(Color::Transparency::invisible);
		ostringstream oss;
		if (source.symbol == main.symbol) {
			oss << sourceValue * destination.rate;
			obCurrency.put(oss.str());
		}
		else if (destination.symbol == main.symbol) {
			oss << sourceValue / source.rate;
			obCurrency.put(oss.str());
		}
		else {
			oss << sourceValue / source.rate * destination.rate;
			obCurrency.put(oss.str());
		}
	}
	else {
		textInvalidInput.set_color(Color::dark_red);
	}
	redraw();
}

void My_window::SetSourceName(const string symbolName)
{
	Currency c;
	if (cr.Get(symbolName, c)) textSourceName.set_label(c.descr);
	else textSourceName.set_label("");
}

void My_window::SetDestinationName(const string symbolName)
{
	Currency c;
	if (cr.Get(symbolName, c)) textDestinationName.set_label(c.descr);
	else textDestinationName.set_label("");
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

istream& Graph_lib::operator>>(istream& is, Currency& cur)
{
	constexpr int symbolSize = 3;
	char ch{ ' ' };
	string temp;
	Currency c;
	for (int i = 0; i < symbolSize; i++) {
		if (is.get(ch));
		else return is;
	}
	for (int i = 0; i < symbolSize; i++) {
		if (is.get(ch)) c.symbol += ch;
		else return is;
	}
	while (is.get(ch) && ch != '/');
	if (!is) return is;
	while (is.get(ch) && isspace(ch));
	if (!is) return is;
	is.unget();
	while (is.get(ch) && ch != '\n') {
		temp += ch;
	}
	if (!is) return is;
	int newSize = temp.size();
	for (int i = temp.size() - 1; i >= 0; i--) {
		if (isspace(temp[i])) newSize = i;
		else break;
	}
	for (int i = 0; i < newSize; i++) {
		c.descr += temp[i];
	}
	if (is >> c.rate);
	else return is;
	while (is.get(ch) && ch != '\n');
	if (!is) return is;
	cur = c;
	return is;
}

#include <FL/Fl_Output.H>
string Graph_lib::In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	string s;
	return s.assign(pi.value());
}
