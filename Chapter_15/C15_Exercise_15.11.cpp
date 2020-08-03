/* Exercise 15.11 */

#include<iostream>
#include<iomanip>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
#include"../GUI/Simple_window.h"
#include"../GUI/Graph.h"
#include"C15_Exercise_15.11.h"

using namespace std;

//inline void error(string s) { throw runtime_error(s); }
//inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

using namespace Graph_lib;


int main()
try {
	constexpr int nBars = 20;									// number of bars
	constexpr int windowLength = 1280;
	constexpr int windowHeight = 1024;
	const string errorMessageInFile = "Error. Can't open input file: ";
	// https://climate.weather.gc.ca/historical_data/search_historic_data_e.html
	const string fileSurrey = "C15_Exercise_15.11_Surrey_en_climate_daily_BC_1106CL2_2019_P1D.csv";
	const string fileVancouver = "C15_Exercise_15.11_Vancouver_en_climate_daily_BC_1105658_2019_P1D.csv";
	const string fileWindsor = "C15_Exercise_15.11_Windsor_en_climate_daily_ON_6139520_2019_P1D.csv";
	ifstream ifsSurrey;
	ifsSurrey.open(fileSurrey);
	if (!ifsSurrey) error(errorMessageInFile, fileSurrey);
	ifstream ifsVancouver;
	ifsVancouver.open(fileVancouver);
	if (!ifsVancouver) error(errorMessageInFile, fileVancouver);
	ifstream ifsWindsor;
	ifsWindsor.open(fileWindsor);
	if (!ifsWindsor) error(errorMessageInFile, fileWindsor);
	
	stringstream ssSurrey;
	GetAverageMaxTemperature(ifsSurrey, ssSurrey);
	if (!ifsSurrey && !ifsSurrey.eof()) error("Read error");
	stringstream ssVancouver;
	GetAverageMaxTemperature(ifsVancouver, ssVancouver);
	if (!ifsVancouver && !ifsVancouver.eof()) error("Read error");
	stringstream ssWindsor;
	GetAverageMaxTemperature(ifsWindsor, ssWindsor);
	if (!ifsWindsor && !ifsWindsor.eof()) error("Read error");
	
	vector<Temperature> surrey;
	vector<Temperature> vancouver;
	vector<Temperature> windsor;
	for (Temperature temp; ssSurrey >> temp; ) surrey.push_back(temp);
	for (Temperature temp; ssVancouver >> temp; ) vancouver.push_back(temp);
	for (Temperature temp; ssWindsor >> temp; ) windsor.push_back(temp);
	
	Simple_window sw{ Point{ 80, 0 }, windowLength, windowHeight, "GraphBar" };
	Point origin{ 100, windowHeight - 124 };
	GraphBar gb1{ origin, 1000, 800, "Average maximum temperatures in Celsius", 3, 25 };
	sw.attach(gb1);

	if (surrey.size() != vancouver.size() || vancouver.size() != windsor.size()) error("Vector sizes are not equal");
	for (int i = 0; i < surrey.size(); i++) {
		gb1.Add(surrey[i].max, "Surrey, " + surrey[i].lab, Color::dark_cyan);
		gb1.Add(vancouver[i].max, "Vancouver, " + vancouver[i].lab, Color::dark_green);
		gb1.Add(windsor[i].max, "Windsor, " + windsor[i].lab, Color::dark_yellow);
	}
	gb1.SetMinMax(-10, 40, 10);

	sw.wait_for_button();
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

GraphBar::GraphBar(Point origin, int width, int height, const string& label, int numberOfBarsInGroup, int intervalScale)
	: origin{ origin }, lab{ label }, fontCol{ Color::black }, font{ Font::helvetica }, fontSize{ defaultFontSize + 4 },
	width{ width }, height{ height }, barsInGroup{ numberOfBarsInGroup }
{
	if (intervalScale <= 0 || intervalScale >= 100) intScale = defaultIntervalScale;
	else intScale = double(intervalScale) / 100;
}

void GraphBar::Add(double barValue, const string& barLabel, Color barColor)
{
	bars.val.push_back(barValue);
	bars.lab.push_back(barLabel);
	bars.col.push_back(barColor);
}

void GraphBar::SetMinMax(double minValue, double maxValue, int numberOfIntervals)
{
	if (minValue >= maxValue) error("maxValue must be greater than minValue");
	if (numberOfIntervals <= 0) error("numberOfIntervals must be greater than 0");
	bars.minVal = minValue;
	bars.maxVal = maxValue;
	yAxis.nIntervals = numberOfIntervals;
}

void GraphBar::draw_lines() const
{
	// draw graph label
	fl_color(fontCol.as_int());
	fl_font(font.as_int(), fontSize);
	fl_draw(lab.c_str(), origin.x + width / 2 - fl_width(lab.c_str()) / 2, origin.y - height - fontSize);
	// draw x axis
	fl_color(xAxis.col.as_int());
	fl_line(origin.x, origin.y, origin.x + width, origin.y);
	// draw y axis
	fl_color(yAxis.col.as_int());
	fl_line(origin.x, origin.y, origin.x, origin.y - height);
	// draw notches and values for y axis
	if (bars.maxVal == 0.0) {
		return;
	}
	if (bars.minVal == 0.0) {
		return;
	}
	if (yAxis.nIntervals == 0) {
		return;
	}
	Point p{ origin };
	double distance = double(height) / yAxis.nIntervals;
	double difference = (bars.maxVal - bars.minVal) / yAxis.nIntervals;
	double notchValue = bars.minVal;
	ostringstream oss;
	fl_color(yAxis.col.as_int());
	fl_font(yAxis.font.as_int(), yAxis.fontSize);
	for (int i = 0; i <= yAxis.nIntervals; i++) {
		fl_line(p.x, p.y, p.x - yAxis.notchWidth, p.y);
		oss.str("");
		oss << notchValue;
		string notchLabel = oss.str();
		fl_draw(notchLabel.c_str(), p.x - fl_width(notchLabel.c_str()) - (yAxis.notchWidth + yAxis.fontSize),
			p.y + yAxis.fontSize / 2);
		notchValue += difference;
		p.y -= distance;
	}
	// draw bars, bar labels and bars values
	constexpr int valueAngle = 90;
	constexpr int labelAngle = 315;
	const int nBars = bars.val.size();							// number of bars
	const int groupWidth = double(width) / nBars * barsInGroup;
	const int intervalWidth = double(groupWidth) * intScale;
	const int barWidth = double(groupWidth) / barsInGroup * (1.0 - intScale);
	const int maxBarHeight = bars.maxVal - bars.minVal;
	p = origin;
	p.x -= intervalWidth / 2;
	for (int i = 0; i < nBars; ) {
		p.x += intervalWidth;									// top left point of the bar
		for (int j = 0; j < barsInGroup; j++) {
			// draw bar
			int barHeight = height * (bars.val[i + j] - bars.minVal) / maxBarHeight;
			p.y -= barHeight;									// top left point of the bar
			fl_color(bars.col[i + j].as_int());
			fl_rectf(p.x, p.y, barWidth, barHeight);
			if (bars.borderCol.visibility()) {
				fl_color(bars.borderCol.as_int());
				fl_rect(p.x, p.y, barWidth, barHeight);
			}
			// draw bar value
			Point pv{ p.x, p.y };
			pv.x += barWidth / 2 + bars.fontSize / 3;
			ostringstream oss;
			oss << fixed << setprecision(2) << bars.val[i + j];
			string s = oss.str();
			pv.y += fl_width(s.c_str()) + bars.fontSize / 2;
			fl_color(bars.fontCol.as_int());
			fl_font(bars.font.as_int(), bars.fontSize);
			fl_draw(valueAngle, s.c_str(), pv.x, pv.y);
			p.y = origin.y;
			// draw bar label
			Point pl{ p.x, p.y };
			pl.x += bars.fontSize / 2;
			pl.y += bars.fontSize;
			fl_draw(labelAngle, bars.lab[i + j].c_str(), pl.x, pl.y);
			p.x += barWidth;
		}
		i += barsInGroup;
	}
}

// assume format: -17.2, Jan 2019
istream& Graph_lib::operator>>(istream& is, Temperature& t)
{
	char comma = 0;
	double max = 0;
	string month;
	string year;
	if (is >> max >> comma >> month >> year) {
		if (comma != ',') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else return is;
	t.max = max;
	t.lab = month + ' ' + year;
	return is;
}

// assume format:
// "Longitude (x)","Latitude (y)","Station Name","Climate ID","Date/Time","Year","Month","Day","Data Quality","Max Temp (°C)","Max Temp Flag","Min Temp (°C)","Min Temp Flag","Mean Temp (°C)","Mean Temp Flag","Heat Deg Days (°C)","Heat Deg Days Flag","Cool Deg Days (°C)","Cool Deg Days Flag","Total Rain (mm)","Total Rain Flag","Total Snow (cm)","Total Snow Flag","Total Precip (mm)","Total Precip Flag","Snow on Grnd (cm)","Snow on Grnd Flag","Dir of Max Gust (10s deg)","Dir of Max Gust Flag","Spd of Max Gust (km/h)","Spd of Max Gust Flag"
istream& Graph_lib::GetAverageMaxTemperature(istream& is, stringstream& ss)
{
	bool toAdd{ false };
	char ch = 0;
	char hyphen = 0;
	char doubleQuote = 0;
	int nCommas = 0;
	int year = 0;
	int y = 0;
	int month = 0;
	int m = 0;
	int counter = 0;
	double maxTemp = 0.0;
	double sumTemp = 0.0;
	string firstLine;
	// skip first line
	getline(is, firstLine);
	while (true) {
		nCommas = 0;
		// skip unnecessary data
		while (is.get(ch)) {
			if (ch == ',') {
				if (++nCommas >= 4) break;
			}
		}
		if (!is) {
			if (is.eof()) {
				ss << sumTemp / counter << ", " << GetMonthName(m) << ' ' << y << '\n';
				break;
			}
			is.clear(ios_base::failbit);
			return is;
		}
		// get year and month
		if (is >> doubleQuote >> year >> hyphen >> month) {
			if (doubleQuote != '"' || hyphen != '-') {
				is.clear(ios_base::failbit);
				return is;
			}
		}
		else return is;
		// skip unnecessary data
		while (is.get(ch)) {
			if (ch == ',') {
				if (++nCommas >= 9) break;
			}
		}
		if (!is) {
			is.clear(ios_base::failbit);
			return is;
		}
		// get max temperature
		if (is >> doubleQuote) {
			if (doubleQuote != '"') {
				is.clear(ios_base::failbit);
				return is;
			}
		}
		else return is;
		if (is.get(ch)) {
			if (ch != '"') {
				toAdd = true;
				is.unget();
				is >> maxTemp;
				if (!is) return is;
			}
			else toAdd = false;
		}
		else return is;
		// skip unnecessary data to the end
		while (is.get(ch)) {
			if (ch == '\n') break;
		}
		if (!is && !is.eof()) {
			is.clear(ios_base::failbit);
			return is;
		}
		// send the required data to the stringstream
		if (!toAdd) continue;
		if (y && m) {
			if (year == y && month == m) {
				sumTemp += maxTemp;
				counter++;
			}
			else {
				ss << sumTemp / counter << ", " << GetMonthName(m) << ' ' << y << '\n';
				sumTemp = maxTemp;
				counter = 1;
				y = year;
				m = month;
			}
		}
		else {
			sumTemp = maxTemp;
			counter = 1;
			y = year;
			m = month;;
		}
	}
	return is;
}

string Graph_lib::GetMonthName(int monthNumber)
{
	switch (monthNumber) {
	case 1:
		return "Jan";
	case 2:
		return "Feb";
	case 3:
		return "Mar";
	case 4:
		return "Apr";
	case 5:
		return "May";
	case 6:
		return "Jun";
	case 7:
		return "Jul";
	case 8:
		return "Aug";
	case 9:
		return "Sep";
	case 10:
		return "Oct";
	case 11:
		return "Nov";
	case 12:
		return "Dec";
	default:
		error("Wrong month number");
	}
}
