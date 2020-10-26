/* Exercise 21.11 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<iomanip>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C21_Exercise_21.11.h"

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
	inboxFileName{ Point{ 200, 0 }, 300, 20, "File name:" },
	buttonOpen{ Point{ 200, 20 }, 300, 20, "Open file",
		[](Address, Address pw) { reference_to<My_window>(pw).OpenFile(); } },

	inboxCustName{ Point{ 200, 60 }, 300, 20, "Customer name:" },
	inboxCustAddr{ Point{ 200, 80 }, 300, 20, "Customer address:" },
	inboxCustData{ Point{ 200, 100 }, 300, 20, "Additional info:" },
	buttonCreateOrder{ Point{ 200, 120 }, 300, 20, "Create order",
		[](Address, Address pw) { reference_to<My_window>(pw).CreateOrder(); } },

	inboxPurName{ Point{ 200, 160 }, 300, 20, "Product name:" },
	inboxPurCount{ Point{ 200, 180 }, 300, 20, "Quantity:" },
	inboxPurPrice{ Point{ 200, 200 }, 300, 20, "Price:" },
	buttonAddPurchase{ Point{ 200, 220 }, 300, 20, "Add purchase",
		[](Address, Address pw) { reference_to<My_window>(pw).AddPurchase(); } },

	buttonWriteToFile{ Point{ 200, 260 }, 300, 40, "Write to file",
		[](Address, Address pw) { reference_to<My_window>(pw).WriteToFile(); } },
	
	buttonReset{ Point{ x_max() - 150, 0 }, 70, 20, "Reset",
		[](Address, Address pw) { reference_to<My_window>(pw).Reset(); } },
	buttonQuit{ Point{ x_max() - 70, 0 }, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<My_window>(pw).quit(); } },
	quitPushed{ false }
{
	attach(inboxFileName);
	attach(buttonOpen);
	textFile.set_font(defaultFont);
	textFile.set_font_size(defaultFontSize);
	attach(textFile);
	attach(inboxCustName);
	attach(inboxCustAddr);
	attach(inboxCustData);
	attach(buttonCreateOrder);
	textCustomer.set_font(defaultFont);
	textCustomer.set_font_size(defaultFontSize);
	attach(textCustomer);
	attach(inboxPurName);
	attach(inboxPurCount);
	attach(inboxPurPrice);
	attach(buttonAddPurchase);
	textPurchase.set_font(defaultFont);
	textPurchase.set_font_size(defaultFontSize);
	attach(textPurchase);
	attach(buttonWriteToFile);
	textWrite.set_font(defaultFont);
	textWrite.set_font_size(defaultFontSize);
	attach(textWrite);
	attach(buttonReset);
	attach(buttonQuit);
}

void My_window::OpenFile()
{
	if (ofs.is_open()) ofs.close();
	string file = inboxFileName.get_string();
	ofs.open(file, fstream::app);
	if (ofs) {
		textFile.set_label("OK");
		textFile.set_color(Color::dark_green);
	}
	else {
		textFile.set_label("Error. Can't open input file: " + file);
		textFile.set_color(Color::dark_red);
	}
	redraw();
}

void My_window::CreateOrder()
{
	if (pOrder != nullptr) {
		delete pOrder;
		pOrder = nullptr;
	}
	string name = inboxCustName.get_string();
	string address = inboxCustAddr.get_string();
	if (name.size() > 0 && address.size() > 0) {
		pOrder = new Order{ name, address, inboxCustData.get_string() };
		textCustomer.set_label("OK");
		textCustomer.set_color(Color::dark_green);
	}
	else {
		textCustomer.set_label("Fields 'Customer name' and 'Customer address' must be filled in");
		textCustomer.set_color(Color::dark_red);
	}
	redraw();
}

void My_window::AddPurchase()
{
	if (pOrder == nullptr) {
		textPurchase.set_label("First create an order");
		textPurchase.set_color(Color::dark_red);
		redraw();
		return;
	}
	string name = inboxPurName.get_string();
	if (name.size() <= 0) {
		textPurchase.set_label("Field 'Product name' must be filled in");
		textPurchase.set_color(Color::dark_red);
		redraw();
		return;
	}
	string s = inboxPurCount.get_string();
	istringstream iss;
	iss.str(s);
	int count;
	if (!(iss >> count)) {
		textPurchase.set_label("Field 'Quantity' must be filled in");
		textPurchase.set_color(Color::dark_red);
		redraw();
		return;
	}
	s = inboxPurPrice.get_string();
	iss.clear();
	iss.str(s);
	double price;
	if (!(iss >> price)) {
		textPurchase.set_label("Field 'Price' must be filled in");
		textPurchase.set_color(Color::dark_red);
		redraw();
		return;
	}
	pOrder->AddPurchase(Purchase{ name, count, price });
	ostringstream oss;
	oss << pOrder->GetPurchaseSize();
	textPurchase.set_label("OK. Number of purchases: " + oss.str());
	textPurchase.set_color(Color::dark_green);
	redraw();
}

void My_window::WriteToFile()
{
	if (!ofs.is_open()) {
		textWrite.set_label("File not open");
		textWrite.set_color(Color::dark_red);
		redraw();
		return;
	}
	if (pOrder == nullptr) {
		textWrite.set_label("First create an order");
		textWrite.set_color(Color::dark_red);
		redraw();
		return;
	}
	if (pOrder->GetPurchaseSize() <= 0) {
		textWrite.set_label("At least one purchase must be added");
		textWrite.set_color(Color::dark_red);
		redraw();
		return;
	}
	if (!(ofs << *pOrder)) {
		textWrite.set_label("Error. The order was not recorded");
		textWrite.set_color(Color::dark_red);
		redraw();
		return;
	}
	textWrite.set_label("OK");
	textWrite.set_color(Color::dark_green);
	Reset();
}

void My_window::Reset()
{
	if (pOrder != nullptr) {
		delete pOrder;
		pOrder = nullptr;
	}
	textCustomer.set_label("");
	textPurchase.set_label("");
	textWrite.set_label("");
	redraw();
}

bool My_window::wait_for_button()
{
	show();
	quitPushed = false;
	while (!quitPushed) Fl::wait();
	Fl::redraw();
	if (pOrder != nullptr) delete pOrder;
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
		ord.AddPurchase(Purchase{ prodName, prodCount, prodPrice });
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
