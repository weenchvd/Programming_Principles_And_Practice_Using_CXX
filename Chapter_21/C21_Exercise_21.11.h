﻿/* Exercise 21.11 */

using namespace std;
using namespace Graph_lib;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

namespace Shop {
	class Purchase {
		string pName;							// product name
		int count;
		double uPrice;							// unit price
	public:
		friend class Order;
		Purchase(const string& productName, int count, double unitPrice)
			: pName{ productName }, count{ count }, uPrice{ unitPrice } {}
		string GetName() const { return pName; }
		int GetCount() const { return count; }
		double GetPrice() const { return uPrice; }

		friend ofstream& operator<<(ofstream& ofs, Order& ord);
		friend ifstream& operator>>(ifstream& ifs, Order& ord);
	};

	const string oSep{ "%" };				// order separator
	const string fSep{ "^" };				// field separator in order

	class Order {
		string cName;							// customer name
		string addr;							// address
		string data;
		vector<Purchase> pur;					// purchases
	public:
		Order() {}
		Order(const string& customerName, const string& address, const string& data)
			: cName{ customerName }, addr{ address }, data{ data } {}
		string GetName() const { return cName; }
		string GetAddress() const { return addr; }
		string GetData() const { return data; }
		int GetPurchaseSize() const { return pur.size(); }
		const Purchase& GetPurchase(int index) const { return pur[index]; }
		void AddPurchase(const Purchase& purchase) { pur.push_back(purchase); }
		void Print(ostream& os);

		friend ofstream& operator<<(ofstream& ofs, Order& ord);
		friend ifstream& operator>>(ifstream& ifs, Order& ord);
	};

	ifstream& SetFailbit(ifstream& ifs) { ifs.setstate(ios_base::failbit); return ifs; }
};

namespace Graph_lib {
	constexpr int defaultFontSize = 14;
	constexpr int defaultFont = int(Font::helvetica);

	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);
		bool wait_for_button();
	private:
		In_box inboxFileName;
		ofstream ofs;
		Button buttonOpen;
		Text textFile{ Point{ 520, 35 }, "" };

		In_box inboxCustName;
		In_box inboxCustAddr;
		In_box inboxCustData;
		Button buttonCreateOrder;
		Text textCustomer{ Point{ 520, 135 }, "" };
		In_box inboxPurName;
		In_box inboxPurCount;
		In_box inboxPurPrice;
		Button buttonAddPurchase;
		Text textPurchase{ Point{ 520, 235 }, "" };
		Button buttonWriteToFile;
		Shop::Order* pOrder{ nullptr };
		Text textWrite{ Point{ 520, 285 }, "" };

		Button buttonReset;
		Button buttonQuit;
		bool quitPushed;

		void OpenFile();
		void CreateOrder();
		void AddPurchase();
		void WriteToFile();
		void Reset();
		void quit();
	};
}
