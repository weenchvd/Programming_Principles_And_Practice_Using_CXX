/* Exercise 11.9 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"C11_Exercise_11.9.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

const string errMessageInputFile = "Error. Can't open input file: ";
const string errMessageOutputFile = "Error. Can't open output file: ";

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		TEXTTOBINARY, BINARYTOTEXT, COMPAREFILES, COMPARENUMBERS
	};
	const string actionList = "\tList of actions:\n"
	"  (1) TextToBinary(), (2) BinaryToText(), (3) CompareFiles(), (4) CompareNumbersInFiles()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		switch (action) {
		case TEXTTOBINARY: {
			string inFileName;
			cout << "Please enter the name of input file: ";
			if (!(cin >> inFileName)) { ClearInput(cin); error("Error. Incorrect input"); }
			string outFileName;
			cout << "Please enter the name of output file: ";
			if (!(cin >> outFileName)) { ClearInput(cin); error("Error. Incorrect input"); }
			TextToBinary(inFileName, outFileName);
			break;
		}
		case BINARYTOTEXT: {
			string inFileName;
			cout << "Please enter the name of input file: ";
			if (!(cin >> inFileName)) { ClearInput(cin); error("Error. Incorrect input"); }
			string outFileName;
			cout << "Please enter the name of output file: ";
			if (!(cin >> outFileName)) { ClearInput(cin); error("Error. Incorrect input"); }
			BinaryToText(inFileName, outFileName);
			break;
		}
		case COMPAREFILES: {
			string inFileName1;
			cout << "Please enter the name of input file 1: ";
			if (!(cin >> inFileName1)) { ClearInput(cin); error("Error. Incorrect input"); }
			string inFileName2;
			cout << "Please enter the name of input file 2: ";
			if (!(cin >> inFileName2)) { ClearInput(cin); error("Error. Incorrect input"); }
			(CompareFiles(inFileName1, inFileName2)) ? (cout << "These files are identical\n") :
				(cout << "These files are not identical\n");
			break;
		}
		case COMPARENUMBERS: {
			string inFileName1;
			cout << "Please enter the name of input file 1: ";
			if (!(cin >> inFileName1)) { ClearInput(cin); error("Error. Incorrect input"); }
			string inFileName2;
			cout << "Please enter the name of input file 2: ";
			if (!(cin >> inFileName2)) { ClearInput(cin); error("Error. Incorrect input"); }
			(CompareNumbersInFiles(inFileName1, inFileName2)) ? (cout << "Numbers in these files are identical\n") :
				(cout << "Numbers in these files are not identical\n");
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

void TextToBinary(const string& inputFileName, const string& outputFileName)
{
	ifstream ifs;
	ifs.open(inputFileName);
	if (!ifs) error(errMessageInputFile, inputFileName);
	ofstream ofs;
	ofs.open(outputFileName, ios_base::binary);
	if (!ofs) error(errMessageOutputFile, outputFileName);
	for (int n; ifs >> n; ) {
		ofs.write((char*) &n, sizeof(int));
	}
	ifs.close();
	ofs.close();
}

void BinaryToText(const string& inputFileName, const string& outputFileName)
{
	ifstream ifs;
	ifs.open(inputFileName, ios_base::binary);
	if (!ifs) error(errMessageInputFile, inputFileName);
	ofstream ofs;
	ofs.open(outputFileName);
	if (!ofs) error(errMessageOutputFile, outputFileName);
	bool space = false;
	for (int n; ifs.read((char*)&n, sizeof(int)); ) {
		if (space) ofs << ' ';
		ofs << n;
		space = true;
	}
	ifs.close();
	ofs.close();
}

bool CompareFiles(const string& inputFileName1, const string& inputFileName2)
{
	ifstream ifs1;
	ifs1.open(inputFileName1);
	if (!ifs1) error(errMessageInputFile, inputFileName1);
	ifstream ifs2;
	ifs2.open(inputFileName2);
	if (!ifs2) error(errMessageInputFile, inputFileName2);
	char ch1;
	char ch2;
	while (ifs1.get(ch1) && ifs2.get(ch2)) {
		if (ch1 != ch2) return false;
	}
	if (ifs1.eof() && !ifs2.eof()) ifs2.get(ch2);
	if (!(ifs1.eof() && ifs2.eof())) return false;
	return true;
}

bool CompareNumbersInFiles(const string& inputFileName1, const string& inputFileName2)
{
	ifstream ifs1;
	ifs1.open(inputFileName1);
	if (!ifs1) error(errMessageInputFile, inputFileName1);
	ifstream ifs2;
	ifs2.open(inputFileName2);
	if (!ifs2) error(errMessageInputFile, inputFileName2);
	int n1;
	int n2;
	while (ifs1 >> n1 && ifs2 >> n2) {
		if (n1 != n2) return false;
	}
	if (ifs1.eof() && !ifs2.eof()) ifs2 >> n2;
	if (!(ifs1.eof() && ifs2.eof())) return false;
	return true;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
