/* Exercise 25.2 */

#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<vector>
#include"C25_Exercise_25.2.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Hexadecimal notation\n"
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
			string fileInput{ "C25_Exercise_25.2_words_alpha.txt" };
			string fileOutput{ "C25_Exercise_25.2_words_hex.txt" };
			ifstream ifs{ fileInput };
			if (!ifs) error("Error. Can't open input file: ", fileInput);
			ofstream ofs{ fileOutput };
			if (!ofs) error("Error. Can't open output file: ", fileOutput);
			
			string hexSymbols{ "abcdef" };
			vector<Conforming> conforming;
			conforming.push_back(Conforming{ '1', 'l' });
			conforming.push_back(Conforming{ '2', 'z' });
			conforming.push_back(Conforming{ '5', 's' });
			conforming.push_back(Conforming{ '7', 'v' });
			conforming.push_back(Conforming{ '9', 'g' });
			
			while (true) {
				string alphaWord;
				ifs >> alphaWord;
				if (!ifs) {
					if (ifs.eof()) break;
					else error("Error. Read error");
				}
				string hexWord;
				bool proceed = true;
				int i = 0;
				for (i = 0; i < alphaWord.size(); ++i) {
					proceed = true;
					for (int j = 0; j < hexSymbols.size(); ++j) {
						if (alphaWord[i] == hexSymbols[j]) {
							hexWord += hexSymbols[j];
							proceed = false;
							break;
						}
					}
					if (proceed == false) continue;
					for (int j = 0; j < conforming.size(); ++j) {
						if (alphaWord[i] == conforming[j].letter) {
							hexWord += conforming[j].hex;
							proceed = false;
							break;
						}
					}
					if (proceed == false) continue;
					break;
				}
				if (i >= alphaWord.size()) ofs << hexWord << endl;
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
