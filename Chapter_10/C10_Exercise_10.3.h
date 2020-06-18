/* Exercise 10.3 */

using namespace std;

class EndOfFile{};

struct Reading {		// a temperature reading
	int hour;			// hour after midnight [0:23]
	double tempCelsius;	// in Celsius
};

ostream& operator<<(ostream& os, const Reading& r);
istream& operator>>(istream& is, Reading& r);

Reading ReadReadingsFromFile(ifstream& ifs);
void ClearInput(istream& is);
