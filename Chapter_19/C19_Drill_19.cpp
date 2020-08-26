/* Drill 19 */

#include<iostream>
#include<istream>
#include<string>
#include<vector>
#include<iomanip>
#include<sstream>
#include"C19_Drill_19.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

const char* space_c2 = "  ";
const char* space_c4 = "    ";
//const char* errMessageInputFile = "Error. Can't open input file: ";
//const char* errMessageOutputFile = "Error. Can't open output file: ";

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		DRILL
	};
	const string actionList = "\tList of actions:\n"
	"  (1) Drill\n"
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
		case DRILL: {
			S<int> i{ 100 };
			S<char> ch{ 'z' };
			S<double> d{ 3.14 };
			S<string> s{ "Drill" };
			S<vector<int>> vi{ {2, 4, 8, 16, 32} };
			
			cout << space_c2 << "S<int> i == " << *(i.Get()) << endl;
			cout << space_c2 << "S<char> ch == " << *(ch.Get()) << endl;
			cout << space_c2 << "S<double> d == " << *(d.Get()) << endl;
			cout << space_c2 << "S<string> s == " << *(s.Get()) << endl;
			cout << space_c2 << "S<vector<int>> vi == " << endl;
			const vector<int>* temp = vi.Get();
			for (int i = 0; i < temp->size(); i++) cout << space_c4 << temp->at(i) << endl;
			cout << endl;

			i.Set(-100);
			ch.Set('q');
			d.Set(9.9999);
			s.Set("ASDF");
			vi.Set({ 1, 2 ,3 });

			cout << space_c2 << "S<int> i == " << *(i.Get()) << endl;
			cout << space_c2 << "S<char> ch == " << *(ch.Get()) << endl;
			cout << space_c2 << "S<double> d == " << *(d.Get()) << endl;
			cout << space_c2 << "S<string> s == " << *(s.Get()) << endl;
			cout << space_c2 << "S<vector<int>> vi == " << endl;
			temp = vi.Get();
			for (int i = 0; i < temp->size(); i++) cout << space_c4 << temp->at(i) << endl;
			cout << endl;

			i = -5;
			ch = 'W';
			d = 5.5555;
			s = "ZXCVBN";
			vi = { -3, -2, -1 };

			cout << space_c2 << "S<int> i == " << *(i.Get()) << endl;
			cout << space_c2 << "S<char> ch == " << *(ch.Get()) << endl;
			cout << space_c2 << "S<double> d == " << *(d.Get()) << endl;
			cout << space_c2 << "S<string> s == " << *(s.Get()) << endl;
			cout << space_c2 << "S<vector<int>> vi == " << endl;
			temp = vi.Get();
			for (int i = 0; i < temp->size(); i++) cout << space_c4 << temp->at(i) << endl;
			cout << endl;

			read_val(*(i.Get()));
			read_val(*(ch.Get()));
			read_val(*(d.Get()));
			read_val(*(s.Get()));
			read_val(*(vi.Get()));

			cout << space_c2 << "S<int> i == " << *(i.Get()) << endl;
			cout << space_c2 << "S<char> ch == " << *(ch.Get()) << endl;
			cout << space_c2 << "S<double> d == " << *(d.Get()) << endl;
			cout << space_c2 << "S<string> s == " << *(s.Get()) << endl;
			cout << space_c2 << "S<vector<int>> vi == " << endl;
			temp = vi.Get();
			for (int i = 0; i < temp->size(); i++) cout << space_c4 << temp->at(i) << endl;
			cout << endl;

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

template<typename T> const T* S<T>::Get() const
{
	return &val;
}

template<typename T> T* S<T>::Get()
{
	return &val;
}

template<typename T> void S<T>::Set(T value)
{
	val = value;
}

template<typename T> T& S<T>::operator=(const T& value)
{
	val = value;
	return val;
}

template<typename T> istream& operator>>(istream& is, vector<T>& v)
{
	T val1;
	T val2;
	T val3;
	if (is >> val1 >> val2 >> val3) {
		v = { val1, val2, val3 };
	}
	return is;
}

template<typename T> void read_val(T& v)
{
	cin >> v;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
