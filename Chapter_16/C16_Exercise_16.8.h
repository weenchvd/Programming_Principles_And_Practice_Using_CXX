/* Exercise 16.8 */

using namespace std;
using namespace Graph_lib;

namespace Graph_lib {
	struct MyText : Text {
		MyText(Point x, const string& s)
			: Text(x, s) { }
		void draw_lines() const;
	};

	struct Currency {
		Currency()
			: rate{ 0.0 } {}
		Currency(string symolName, string description, double rate)
			: symbol{ symolName }, descr{ description }, rate{ rate } {}
		string symbol;
		string descr;
		double rate;
	};

	class CurrencyRate {
	public:
		CurrencyRate() {}
		void SetMainCurrency(const Currency& mainCurrency) { main = mainCurrency; }
		void AddCurrency(const Currency& currency) { cur.push_back(currency); }
		bool Get(const string& symbolName, Currency& currency) const;
		void Get(Currency& mainCurrency) const { mainCurrency = main; }
	private:
		Currency main;
		vector<Currency> cur;
	};

	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);
		bool wait_for_button();
		
		CurrencyRate cr;
	private:
		Text textSourceName{ Point{ x_max() / 2 - 200, 295 }, "EURO" };
		Text textDestinationName{ Point{ x_max() / 2 + 100, 295 }, "EURO" };
		MyText textInvalidInput{ Point{ x_max() / 2 - 95, 320 }, "Invalid input" };

		In_box ibCurrency;
		Out_box obCurrency;

		Menu menuSrc;											// Source menu
		Menu menuDst;											// Destination menu

		Button buttonConvert;
		Button buttonMenuSrc;
		Button buttonMenuDst;
		Button buttonQuit;

		bool quitPushed;

		void ConvertCurrency();
		void MenuSourcePressed() { buttonMenuSrc.hide(); menuSrc.show(); }
		void MenuDestinationPressed() { buttonMenuDst.hide(); menuDst.show(); }
		void SetSourceName(const string symbolName);
		void SetDestinationName(const string symbolName);
		void SetSourceToEUR() { ibCurrency.label = "EUR"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToAUD() { ibCurrency.label = "AUD"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToBYN() { ibCurrency.label = "BYN"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToCAD() { ibCurrency.label = "CAD"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToCHF() { ibCurrency.label = "CHF"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToCNY() { ibCurrency.label = "CNY"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToGBP() { ibCurrency.label = "GBP"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToJPY() { ibCurrency.label = "JPY"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToKPW() { ibCurrency.label = "KPW"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToKRW() { ibCurrency.label = "KRW"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToNZD() { ibCurrency.label = "NZD"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToRUB() { ibCurrency.label = "RUB"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToSGD() { ibCurrency.label = "SGD"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToUAH() { ibCurrency.label = "UAH"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetSourceToUSD() { ibCurrency.label = "USD"; obCurrency.put(""); SetSourceName(ibCurrency.label); menuSrc.hide(); buttonMenuSrc.show(); }
		void SetDestinationToEUR() { obCurrency.label = "EUR"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToAUD() { obCurrency.label = "AUD"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToBYN() { obCurrency.label = "BYN"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToCAD() { obCurrency.label = "CAD"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToCHF() { obCurrency.label = "CHF"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToCNY() { obCurrency.label = "CNY"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToGBP() { obCurrency.label = "GBP"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToJPY() { obCurrency.label = "JPY"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToKPW() { obCurrency.label = "KPW"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToKRW() { obCurrency.label = "KRW"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToNZD() { obCurrency.label = "NZD"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToRUB() { obCurrency.label = "RUB"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToSGD() { obCurrency.label = "SGD"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToUAH() { obCurrency.label = "UAH"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void SetDestinationToUSD() { obCurrency.label = "USD"; obCurrency.put(""); SetDestinationName(obCurrency.label); menuDst.hide(); buttonMenuDst.show(); }
		void quit();
	};

	istream& operator>>(istream& is, Currency& cur);
}
