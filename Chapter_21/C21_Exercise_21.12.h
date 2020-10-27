/* Exercise 21.12 */

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
		void Find(const Purchase& purchase) { pur.push_back(purchase); }
		void Print(ostream& os);

		friend ofstream& operator<<(ofstream& ofs, Order& ord);
		friend ifstream& operator>>(ifstream& ifs, Order& ord);
	};

	ifstream& SetFailbit(ifstream& ifs) { ifs.setstate(ios_base::failbit); return ifs; }
};

namespace Graph_lib {
	constexpr int defFontSize = 14;
	constexpr int defLineSpacing = defFontSize * 140 / 100;
	constexpr int defFont = int(Font::helvetica);
	constexpr int defFontBold = int(Font::helvetica_bold);

	struct MText : Shape {
		// the point is the top left of the first letter (first line)
		MText(Point x, int numberOfLines, int fontSize, int lineSpacing);

		void draw_lines() const;

		int NumberOfLines() const { return nLines; }
		void Resize(int numberOfLines);
		void Hide();

		void Set(int index, const string& s, Font f, Color c);

		void SetLabel(int index, const string& s) { lab[index] = s; show[index] = true; }
		string GetLabel(int index) const { return lab[index]; }

		void SetFont(int index, Font f) { fnt[index] = f; }
		Font GetFont(int index) const { return fnt[index]; }

		void SetColor(int index, Color c) { col[index] = c; }
		Color GetColor(int index) const { return col[index]; }

		void SetFontSize(int size) { fntSz = size; }
		int GetFontSize() const { return fntSz; }

		void SetLineSpacing(int lineSpacing) { lineSp = lineSpacing; }
		int GetLineSpacing() const { return lineSp; }
	private:
		vector<string> lab;
		vector<Font> fnt;
		vector<Color> col;
		vector<bool> show;
		int fntSz;
		int lineSp;
		int nLines;
	};

	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);
		bool wait_for_button();
	private:
		In_box inboxInputFile;
		ifstream ifs;
		Button buttonOpenInput;
		Text textInputFile;

		In_box inboxOutputFile;
		ofstream ofs;
		Button buttonOpenOutput;
		Text textOutputFile;

		In_box inboxCustName;
		In_box inboxCustAddr;
		In_box inboxCustData;
		In_box inboxPurName;
		In_box inboxPurCount;
		In_box inboxPurPrice;
		Button buttonFind;
		Text textFind;

		Button buttonRecordOrders;
		vector<Shop::Order> orders;
		Text textRecordOrders;

		Button buttonPrintOrders;
		Text textPrintOrders;

		Button buttonTotalValue;
		Text textTotalValue;

		Text textMessage;
		MText mtextPrint;

		Button buttonClear;
		Button buttonQuit;
		bool quitPushed;

		void OpenInputFile();
		void OpenOutputFile();
		void Find();
		void RecordOrders();
		void PrintOrders();
		void TotalValue();
		void Reset(Text& text) { text.set_label(""); }
		void Clear();
		void quit();
	};
}
