/* Exercise 10.4 */

using namespace std;

class EndOfFile{};

struct Reading {		// a temperature reading
	int hour;			// hour after midnight [0:23]
	double tempCelsius;	// in Celsius
};

ostream& operator<<(ostream& os, const Reading& r);
istream& operator>>(istream& is, Reading& r);

Reading ReadReadingsFromFile(ifstream& ifs);
double FahrenheitToCelsius(double tempFahr);
void ClearInput(istream& is);
