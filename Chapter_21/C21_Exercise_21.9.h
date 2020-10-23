/* Exercise 21.9 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

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
		void AddPurchase(const Purchase& purchase) { pur.push_back(purchase); }
		void Print(ostream& os);

		friend ofstream& operator<<(ofstream& ofs, Order& ord);
		friend ifstream& operator>>(ifstream& ifs, Order& ord);
	};

	ifstream& SetFailbit(ifstream& ifs) { ifs.setstate(ios_base::failbit); return ifs; }
};
