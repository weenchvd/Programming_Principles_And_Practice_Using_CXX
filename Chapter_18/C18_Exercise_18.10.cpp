/* Exercise 18.10 */

#include<iostream>
#include<istream>
#include<string>
#include<iomanip>
#include<sstream>
#include"C18_Exercise_18.10.h"

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
		A, B
	};
	const string actionList = "\tList of actions:\n"
		"  (1) is_palindrome(const char[], int) (A), (2) is_palindrome(const char[], int) (B)\n"
		"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	const char* space2 = "  ";
	const char* space4 = "    ";
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case A: {
			constexpr int max = 5;
			cout << "\nPlease enter a string in English (only ASCII): ";
			char s[max];
			read_word(cin, s, max);
			cout << s << " is";
			if (!is_palindrome(s, strlen(s))) cout << " not";
			cout << " a palindrome\n";
			break;
		}
		case B: {
			cout << "\nPlease enter a string in English (only ASCII): ";
			BufferChar buffer;
			read_word(cin, buffer);
			cout << buffer.buf << " is";
			if (!is_palindrome(buffer.buf, strlen(buffer.buf))) cout << " not";
			cout << " a palindrome\n";
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

bool is_palindrome(const char s[], int n)
// s points to the first character of an array of n characters
{
	int first = 0;												// index of first letter
	int last = n - 1;											// index of last letter
	while (first < last) {										// we haven’t reached the middle
		if (s[first] != s[last]) return false;
		++first;												// move forward
		--last;													// move backward
	}
	return true;
}

istream& read_word(istream& is, char* buffer, int max)
// read at most max–1 characters from is into buffer
{
	char* temp = new char[max + 1];
	is.width(max + 1);		// read at most 'max – 1' characters in the next >>
	is >> temp;		// read whitespace-terminated word, add zero after the last character read into buffer
	if (!is) {
		delete[] temp;
		error("Error. Read error");
	}
	if (strlen(temp) >= max) {
		delete[] temp;
		ClearInput(cin);
		error("Error. Input string was too long");
	}
	for (int i = 0; (buffer[i] = temp[i]) != '\0'; i++);
	delete[] temp;
	return is;
}

istream& read_word(istream& is, BufferChar& buffer)
{
	char ch;
	for (streamsize i = 0; is.get(ch); i++) {
		if (i >= buffer.size) buffer.Increase(buffer.size);
		if (isspace(ch)) {
			is.unget();
			buffer.buf[i] = '\0';
			break;
		}
		else buffer.buf[i] = ch;
	}
	if (!is) error("Error. Read error");
	ClearInput(is);
	return is;
}

void BufferChar::Increase(int n)
{
	char* temp = new char[size + n];
	for (int i = 0; i < size; i++) temp[i] = buf[i];
	delete[] buf;
	buf = temp;
	size += n;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
