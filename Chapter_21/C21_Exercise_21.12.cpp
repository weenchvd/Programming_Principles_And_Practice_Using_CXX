/* Exercise 21.12 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<iomanip>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C21_Exercise_21.12.h"

using namespace std;
using namespace Shop;

inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
try {
	constexpr int windowLength = 1280;
	constexpr int windowHeight = 1024;

	My_window mw{ Point{ 80, 0 }, windowLength, windowHeight, "Orders" };

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
	inboxInputFile{ Point{ 200, 0 }, 300, 20, "Input file:" },
	buttonOpenInput{ Point{ 200, 20 }, 150, 20, "Open file",
		[](Address, Address pw) { reference_to<My_window>(pw).OpenInputFile(); } },
	textInputFile{ Point{ 370, 35 }, "File is not open" },

	inboxOutputFile{ Point{ 600, 0 }, 300, 20, "Output file:" },
	buttonOpenOutput{ Point{ 600, 20 }, 150, 20, "Open file",
		[](Address, Address pw) { reference_to<My_window>(pw).OpenOutputFile(); } },
	textOutputFile{ Point{ 770, 35 }, "File is not open" },

	inboxCustName{ Point{ 200, 60 }, 300, 20, "Customer name:" },
	inboxCustAddr{ Point{ 200, 80 }, 300, 20, "Customer address:" },
	inboxCustData{ Point{ 200, 100 }, 300, 20, "Additional info:" },
	inboxPurName{ Point{ 200, 120 }, 300, 20, "Product name:" },
	inboxPurCount{ Point{ 200, 140 }, 300, 20, "Quantity:" },
	inboxPurPrice{ Point{ 200, 160 }, 300, 20, "Price:" },
	buttonFind{ Point{ 200, 180 }, 150, 20, "Find in file",
		[](Address, Address pw) { reference_to<My_window>(pw).Find(); } },
	textFind{ Point{ 370, 195 }, "" },

	buttonRecordOrders{ Point{ 600, 60 }, 150, 40, "Record orders",
		[](Address, Address pw) { reference_to<My_window>(pw).RecordOrders(); } },
	textRecordOrders{ Point{ 770, 85 }, "" },

	buttonPrintOrders{ Point{ 600, 100 }, 150, 40, "Print orders",
		[](Address, Address pw) { reference_to<My_window>(pw).PrintOrders(); } },
	textPrintOrders{ Point{ 770, 125 }, "" },

	buttonTotalValue{ Point{ 600, 140 }, 150, 40, "Total value",
		[](Address, Address pw) { reference_to<My_window>(pw).TotalValue(); } },
	textTotalValue{ Point{ 770, 165 }, "" },

	textMessage{ Point{ 200, 235 }, "" },
	mtextPrint{ Point{ 200, 240 }, 40, defFontSize, defLineSpacing },

	buttonClear{ Point{ x_max() - 150, 0 }, 70, 20, "Clear",
		[](Address, Address pw) { reference_to<My_window>(pw).Clear(); } },
	buttonQuit{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<My_window>(pw).quit(); } },
	quitPushed{ false }
{
	attach(inboxOutputFile);
	attach(buttonOpenOutput);
	textOutputFile.set_font(defFont);
	textOutputFile.set_font_size(defFontSize);
	textOutputFile.set_color(Color::black);
	attach(textOutputFile);

	attach(inboxInputFile);
	attach(buttonOpenInput);
	textInputFile.set_font(defFont);
	textInputFile.set_font_size(defFontSize);
	textInputFile.set_color(Color::black);
	attach(textInputFile);

	attach(inboxCustName);
	attach(inboxCustAddr);
	attach(inboxCustData);
	attach(inboxPurName);
	attach(inboxPurCount);
	attach(inboxPurPrice);
	attach(buttonFind);
	textFind.set_font(defFont);
	textFind.set_font_size(defFontSize);
	textFind.set_color(Color::black);
	attach(textFind);

	attach(buttonRecordOrders);
	textRecordOrders.set_font(defFont);
	textRecordOrders.set_font_size(defFontSize);
	textRecordOrders.set_color(Color::black);
	attach(textRecordOrders);

	attach(buttonPrintOrders);
	textPrintOrders.set_font(defFont);
	textPrintOrders.set_font_size(defFontSize);
	textPrintOrders.set_color(Color::black);
	attach(textPrintOrders);

	attach(buttonTotalValue);
	textTotalValue.set_font(defFont);
	textTotalValue.set_font_size(defFontSize);
	textTotalValue.set_color(Color::black);
	attach(textTotalValue);

	textMessage.set_font(defFontBold);
	textMessage.set_font_size(defFontSize);
	textMessage.set_color(Color::black);
	attach(textMessage);
	attach(mtextPrint);

	attach(buttonClear);
	attach(buttonQuit);
}

void My_window::OpenInputFile()
{
	if (ifs.is_open()) ifs.close();
	string file = inboxInputFile.get_string();
	ifs.open(file);
	if (ifs) {
		textInputFile.set_label("File is opened");
		textInputFile.set_color(Color::dark_green);
	}
	else {
		textInputFile.set_label("File is not open");
		textInputFile.set_color(Color::dark_red);
	}
	redraw();
}

void My_window::OpenOutputFile()
{
	if (ofs.is_open()) ofs.close();
	string file = inboxOutputFile.get_string();
	ofs.open(file, fstream::app);
	if (ofs) {
		textOutputFile.set_label("File is opened");
		textOutputFile.set_color(Color::dark_green);
	}
	else {
		textOutputFile.set_label("File is not open");
		textOutputFile.set_color(Color::dark_red);
	}
	redraw();
}

void My_window::Find()
{
	if (!ifs.is_open()) {
		textMessage.set_label("File is not open");
		textMessage.set_color(Color::dark_red);
		textFind.set_label("Failure");
		textFind.set_color(Color::dark_red);
		redraw();
		return;
	}
	ifs.clear();
	ifs.seekg(ios_base::beg);
	orders.resize(0);
	string custName = inboxCustName.get_string();
	string custAddr = inboxCustAddr.get_string();
	string custData = inboxCustData.get_string();
	string prodName = inboxPurName.get_string();
	string s = inboxPurCount.get_string();
	int prodCount = 0;
	if (s.size() > 0) {
		istringstream iss;
		iss.str(s);
		if (!(iss >> prodCount)) prodCount = 0;

	}
	s = inboxPurPrice.get_string();
	double prodPrice = 0.0;
	if (s.size() > 0) {
		istringstream iss;
		iss.str(s);
		if (!(iss >> prodPrice)) prodPrice = 0.0;

	}
	while (!ifs.eof()) {
		Order ord;
		if (ifs >> ord) {
			if (custName.size() > 0 && custName != ord.GetName()) continue;
			if (custAddr.size() > 0 && custAddr != ord.GetAddress()) continue;
			if (custData.size() > 0 && custData != ord.GetData()) continue;
			if (prodName.size() == 0 && prodCount == 0 && prodPrice == 0.0) {
				orders.push_back(ord);
				continue;
			}
			bool add = false;
			for (int i = 0; !add && i < ord.GetPurchaseSize(); ++i) {
				add = true;
				if (prodName.size() > 0 && prodName != ord.GetPurchase(i).GetName()) add = false;
				if (prodCount > 0 && prodCount != ord.GetPurchase(i).GetCount()) add = false;
				if (prodPrice > 0.0 && prodPrice != ord.GetPurchase(i).GetPrice()) add = false;
			}
			if (add) orders.push_back(ord);
		}
		if (ifs.eof()) break;
		if (!ifs) {
			textMessage.set_label("Error. Can't read input file");
			textMessage.set_color(Color::dark_red);
			redraw();
			return;
		}
	}
	if (orders.size() == 0) {
		textMessage.set_label("No orders with these conditions were found");
		textMessage.set_color(Color::black);
	}
	else {
		ostringstream oss;
		oss << orders.size();
		textMessage.set_label("Orders found: " + oss.str());
		textMessage.set_color(Color::dark_green);
	}
	textFind.set_label("Succsess");
	textFind.set_color(Color::dark_green);
	redraw();
}

void My_window::RecordOrders()
{
	if (!ofs.is_open()) {
		textMessage.set_label("File is not open");
		textMessage.set_color(Color::dark_red);
		textRecordOrders.set_label("Failure");
		textRecordOrders.set_color(Color::dark_red);
		redraw();
		return;
	}
	for (int i = 0; i < orders.size(); ++i) {
		if (!(ofs << orders[i])) {
			textMessage.set_label("Recording failed");
			textMessage.set_color(Color::dark_red);
			textRecordOrders.set_label("Failure");
			textRecordOrders.set_color(Color::dark_red);
			redraw();
			return;
		}
	}
	textMessage.set_label("The orders were recorded in the file: " + inboxOutputFile.get_string());
	textMessage.set_color(Color::dark_green);
	textRecordOrders.set_label("Succsess");
	textRecordOrders.set_color(Color::dark_green);
	redraw();
}

void My_window::PrintOrders()
{
	if (orders.size() == 0) {
		textMessage.set_label("First, search");
		textMessage.set_color(Color::dark_red);
		textPrintOrders.set_label("Failure");
		textPrintOrders.set_color(Color::dark_red);
		redraw();
		return;
	}
	static int i = 0;
	static int j = 0;
	static bool print = true;
	int k = -1;
	mtextPrint.Hide();
	for (; i < orders.size(); ++i) {
		if (print && ++k < mtextPrint.NumberOfLines()) {
			string s = "Customer \"" + orders[i].GetName();
			if (orders[i].GetName().size() > 0) s += "\"    Address \"" + orders[i].GetAddress();
			if (orders[i].GetData().size() > 0) s += "\"    Additional info \"" + orders[i].GetData();
			s += "\"";
			mtextPrint.Set(k, s, defFont, Color::black);
			print = false;
		}
		for (; j < orders[i].GetPurchaseSize(); ++j) {
			if (++k < mtextPrint.NumberOfLines()) {
				ostringstream oss;
				oss << "    " << "Product: " << setw(60) << left << orders[i].GetPurchase(j).GetName()
					<< " Qty: " << setw(4) << left << orders[i].GetPurchase(j).GetCount()
					<< " Price: " << orders[i].GetPurchase(j).GetPrice();
				mtextPrint.Set(k, oss.str(), defFont, Color::black);
			}
			else break;
		}
		if (k >= mtextPrint.NumberOfLines()) break;
		if (j >= orders[i].GetPurchaseSize()) j = 0;
		print = true;
	}
	if (i >= orders.size()) i = 0;
	textMessage.set_label("The orders:");
	textMessage.set_color(Color::dark_green);
	textPrintOrders.set_label("Succsess");
	textPrintOrders.set_color(Color::dark_green);
	redraw();
}

void My_window::TotalValue()
{
	if (orders.size() == 0) {
		textMessage.set_label("First, search");
		textMessage.set_color(Color::dark_red);
		textTotalValue.set_label("Failure");
		textTotalValue.set_color(Color::dark_red);
		redraw();
		return;
	}
	double total{ 0.0 };
	for (int i = 0; i < orders.size(); ++i) {
		for (int j = 0; j < orders[i].GetPurchaseSize(); ++j) {
			total += (orders[i].GetPurchase(j).GetCount() * orders[i].GetPurchase(j).GetPrice());
		}
	}
	ostringstream oss;
	oss << "Total value: " << total;
	textMessage.set_label(oss.str());
	textMessage.set_color(Color::dark_green);
	textTotalValue.set_label("Succsess");
	textTotalValue.set_color(Color::dark_green);
	redraw();
}

void My_window::Clear()
{
	orders.resize(0);
	mtextPrint.Hide();
	if (ifs.is_open()) ifs.close();
	if (ofs.is_open()) ofs.close();
	textInputFile.set_label("File is not open");
	textInputFile.set_color(Color::black);
	textOutputFile.set_label("File is not open");
	textOutputFile.set_color(Color::black);
	textFind.set_label("");
	textRecordOrders.set_label("");
	textMessage.set_label("");
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
	hide();
}

#include <FL/Fl_Output.H>
string Graph_lib::In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	string s;
	return s.assign(pi.value());
}

Graph_lib::MText::MText(Point x, int numberOfLines, int fontSize, int lineSpacing)
	: nLines{ numberOfLines }, fntSz{ fontSize }, lineSp{ lineSpacing }
{
	add(x);
	lab.resize(numberOfLines);
	fnt.resize(numberOfLines, Font{ defFont });
	col.resize(numberOfLines, Color{ Color::black });
	show.resize(numberOfLines, false);
}

void Graph_lib::MText::draw_lines() const
{
	int ofnt = fl_font();
	int osz = fl_size();
	for (int i = 0; i < nLines; ++i) {
		if (show[i]) {
			fl_color(col[i].as_int());
			fl_font(fnt[i].as_int(), fntSz);
			fl_draw(lab[i].c_str(), point(0).x, point(0).y + lineSp * i + (lineSp * 90) / 100);
		}
	}
	fl_font(ofnt, osz);
}

void Graph_lib::MText::Resize(int numberOfLines)
{
	lab.resize(numberOfLines);
	fnt.resize(numberOfLines, Font{ defFont });
	col.resize(numberOfLines, Color{ Color::black });
	show.resize(numberOfLines, false);
	nLines = numberOfLines;
}

void Graph_lib::MText::Hide()
{
	for (int i = 0; i < nLines; ++i) show[i] = false;
}

void Graph_lib::MText::Set(int index, const string& s, Font f, Color c)
{
	lab[index] = s;
	fnt[index] = f;
	col[index] = c;
	show[index] = true;
}

ofstream& Shop::operator<<(ofstream& ofs, Order& ord)
{
	ofs << oSep << ' ' << ord.cName << ' ' << fSep << ' ' << ord.addr
		<< ' ' << fSep << ' ' << ord.data;
	for (int i = 0; i < ord.pur.size(); ++i) {
		ofs << ' ' << fSep << ' ' << ord.pur[i].pName << ' ' << fSep << ' ' << ord.pur[i].count
			<< ' ' << fSep << ' ' << ord.pur[i].uPrice;
	}
	ofs << endl;
	return ofs;
}

ifstream& Shop::operator>>(ifstream& ifs, Order& ord)
{
	constexpr int numberOfField = 3;
	string s;
	if (!getline(ifs, s)) return ifs;
	istringstream iss;
	iss.str(s);
	if (!(iss >> s) || s != oSep) return SetFailbit(ifs);
	vector<string> vs(numberOfField);
	for (int i = 0; i < vs.size(); ++i) {
		while (true) {
			if (!(iss >> s)) return SetFailbit(ifs);
			if (s == fSep) break;
			if (vs[i].size() > 0) vs[i] = vs[i] + ' ' + s;
			else vs[i] = s;
		}
	}
	ord = Order{ vs[0], vs[1], vs[2] };
	while (!iss.eof()) {
		string prodName;
		int prodCount;
		double prodPrice;
		while (true) {
			if (!(iss >> s)) return SetFailbit(ifs);
			if (s == fSep) break;
			if (prodName.size() > 0) prodName = prodName + ' ' + s;
			else prodName = s;
		}
		if (iss >> prodCount >> s >> prodPrice) {
			if (s != fSep) return SetFailbit(ifs);
		}
		else return SetFailbit(ifs);
		ord.Find(Purchase{ prodName, prodCount, prodPrice });
		if ((iss >> s).eof()) continue;
		if (s != fSep) return SetFailbit(ifs);
	}
	return ifs;
}

void Order::Print(ostream& os)
{
	os << "Customer: \"" << cName;
	if (addr.size() > 0) os << "\" Address: \"" << addr;
	if (data.size() > 0) os << "\" Additional info: \"" << data;
	os << "\"" << endl;
	for (int i = 0; i < pur.size(); ++i) {
		os << '\t' << "Product: " << setw(60) << left << pur[i].pName
			<< " Qty: " << setw(4) << left << pur[i].count
			<< " Price: " << pur[i].uPrice << endl;
	}
}
