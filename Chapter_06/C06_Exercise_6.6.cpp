/* Exercise 6.6 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>

using namespace std;

void error(string s) { throw runtime_error(s); }

constexpr char nothing = 0;
constexpr char sentence = 1;
constexpr char noun = 2;
constexpr char verb = 3;
constexpr char conj = 4;
constexpr char dot = 5;

bool Sentence();
bool Noun();
bool Verb();
bool Conjunction();
bool Dot();

class Token {
public:
	Token()
		: type(nothing) { }
	Token(char ch)
		: type(ch) { }
	Token(char ch , string str)
		: type(ch), s(str) { }
	char type;
	string s;
};

class TokenStream {
public:
	TokenStream()
		: isFull(false), buffer(0) { }
	Token Get();
	void PutBack(Token t);
	void Clear();
private:
	bool isFull;
	Token buffer;
};

TokenStream ts;
istringstream iss;

int main()
{
	try {
		string line;
		Token t;
		cout << "Please enter '-exit' to exit\n";
		while (true) {
			cout << "Please enter a sentence:\n";
			getline(cin, line);
			iss.clear();
			iss.str(line);
			ts.Clear();
			t = ts.Get();
			if (t.s == "-exit") {
				break;
			}
			else {
				ts.PutBack(t);
			}
			if (Sentence() == true && iss.eof() == true) {
				cout << "  OK\n";
			}
			else {
				cout << "  not OK\n";
			}
		}
		return 0;
	}
	catch (runtime_error& e) {
		cerr << "\n\t| RUNTIME ERROR | " << e.what() << "\n";
		return -1;
	}
	catch (...) {
		cerr << "\n\t| UNKNOWN EXCEPTION |\n";
		return -2;
	}
}

Token TokenStream::Get()
{
	Token t;
	if (isFull == true) {
		t = buffer;
		isFull = false;
	}
	else {
		iss >> t.s;
	}
	return t;
}

void TokenStream::PutBack(Token t)
{
	if (isFull == true) {
		error("PutBack() into a full buffer");
	}
	else {
		buffer = t;
		isFull = true;
	}
	return;
}

void TokenStream::Clear()
{
	isFull = false;
	return;
}

bool Sentence()
{
	char prev = nothing;
	bool cond = true;
	bool ret = false;
	while (cond) {
		switch (prev) {
		case nothing:
		case conj:
			if (Noun() == true) {
				prev = noun;
			}
			else {
				cond = false;
			}
			break;
		case noun:
			if (Verb() == true) {
				prev = sentence;
			}
			else {
				cond = false;
			}
			break;
		case sentence:
			if (Conjunction() == true) {
				prev = conj;
			}
			else {
				if (Dot() == true) {
					ret = true;
				}
				cond = false;
			}
			break;
		default:
			error("Unknown error");
			break;
		}
	}
	return ret;
}

bool Noun()
{
	Token t = ts.Get();
	if (t.s == "the") {
		t = ts.Get();
	}
	if (t.s == "birds" || t.s == "fish" || t.s == "C++") {
		t.type = noun;
		return true;
	}
	else {
		ts.PutBack(t);
		return false;
	}
}

bool Verb()
{
	Token t = ts.Get();
	if (t.s == "rules" || t.s == "fly" || t.s == "swim") {
		t.type = verb;
		return true;
	}
	else {
		ts.PutBack(t);
		return false;
	}
}

bool Conjunction()
{
	Token t = ts.Get();
	if (t.s == "and" || t.s == "or" || t.s == "but") {
		t.type = conj;
		return true;
	}
	else {
		ts.PutBack(t);
		return false;
	}
}

bool Dot()
{
	Token t = ts.Get();
	if (t.s == ".") {
		t.type = dot;
		return true;
	}
	else {
		ts.PutBack(t);
		return false;
	}
}
