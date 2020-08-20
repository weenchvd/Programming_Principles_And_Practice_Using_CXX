/* Exercise 18.10 */

using namespace std;

constexpr int defaultBufferSize = 10;

struct BufferChar {
	BufferChar() : size{ defaultBufferSize } { buf = new char[size]; }
	BufferChar(int size) : size{ size } { buf = new char[size]; }
	~BufferChar() { delete[] buf; }
	char* buf;
	int size;

	void Increase(int n);
};

bool is_palindrome(const char s[], int n);
istream& read_word(istream& is, char* buffer, int max);
istream& read_word(istream& is, BufferChar& buffer);
void ClearInput(istream& is);
