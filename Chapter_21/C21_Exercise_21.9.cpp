/* Exercise 21.9 */

#include<iostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include<iomanip>
#include"C21_Exercise_21.9.h"

using namespace std;
using namespace Shop;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Order,\n"
		"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case CASE1: {
			cout << endl;
			string file1{ "C21_Exercise_21.9_Orders_001.ord" };
			string file2{ "C21_Exercise_21.9_Orders_002.ord" };
			string file3{ "C21_Exercise_21.9_Orders_003.ord" };
			ifstream ifs1;
			ifs1.open(file1);
			if (!ifs1) error("Error. Can't open input file: ", file1);
			ifstream ifs2;
			ifs2.open(file2);
			if (!ifs2) error("Error. Can't open input file: ", file2);

			vector<Order> vo;
			while (true) {
				Order ord;
				if (ifs1 >> ord) vo.push_back(ord);
				if (ifs1.eof()) break;
				if (!ifs1) error("Error. Can't read input file: ", file1);
			}
			sort(vo.begin(), vo.end(),
				[](const Order& ord1, const Order& ord2) { return ord1.GetName() < ord2.GetName(); });
			cout << endl << sp_2 << file1 << " sorted by name:" << endl;
			for (int i = 0; i < vo.size(); ++i) vo[i].Print(cout);
			
			list<Order> lo;
			while (true) {
				Order ord;
				if (ifs2 >> ord) lo.push_back(ord);
				if (ifs2.eof()) break;
				if (!ifs2) error("Error. Can't read input file: ", file2);
			}
			lo.sort([](const Order& ord1, const Order& ord2) { return ord1.GetAddress() < ord2.GetAddress(); });
			cout << endl << sp_2 << file2 << " sorted by address:" << endl;
			for (auto it = lo.begin(); it != lo.end(); ++it) it->Print(cout);

			ofstream ofs1;
			ofs1.open(file1);
			if (!ofs1) error("Error. Can't open output file: ", file1);
			ofstream ofs2;
			ofs2.open(file2);
			if (!ofs2) error("Error. Can't open output file: ", file2);

			for (int i = 0; i < vo.size(); ++i) {
				if (!(ofs1 << vo[i])) error("Error. Can't write output file: ", file1);
			}

			for (auto it = lo.begin(); it != lo.end(); ++it) {
				if (!(ofs2 << *it)) error("Error. Can't write output file: ", file2);
			}

			vector<Order> result(vo.size() + lo.size());
			merge(vo.begin(), vo.end(), lo.begin(), lo.end(), result.begin(),
				[](const Order& ord1, const Order& ord2) { return ord1.GetName() < ord2.GetName(); });
			cout << endl << sp_2 << file1 << " + " << file2 << " merged by name:" << endl;
			for (int i = 0; i < result.size(); ++i) result[i].Print(cout);

			ofstream ofs3;
			ofs3.open(file3);
			if (!ofs3) error("Error. Can't open output file: ", file3);

			for (int i = 0; i < result.size(); ++i) {
				if (!(ofs3 << result[i])) error("Error. Can't write output file: ", file3);
			}

			cout << vsp_2;
			break;
		}
		case PRINTACTIONLIST:
			cout << actionList;
			break;
		case EXIT:
			cond = false;
			break;
		default:
			error("Error. Incorrect action number");
			break;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Error. Exception\n";
		return 1;
	}
	return 0;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
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
