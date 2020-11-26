/* Exercise 25.1 */

#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<bitset>
#include"C25_Exercise_25.1.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }
inline int randint(int max) { return rand() % max; }
inline int randint(int min, int max) { return randint(max - min) + min; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const string actionList = "\tList of actions:\n"
		"  (1) Memory fragmentation, (2) Bits, (3) Infinite loop, (4) si = 128\n"
		"  (5) Encrypt(), (6) Decrypt()\n"
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
			cout << sp_2 << "sizeof(Message) = " << sizeof(Message) << " bytes" << endl;
			cout << sp_2 << "sizeof(Node) = " << sizeof(Node) << " bytes" << endl;
			cout << endl;

			constexpr int n = 10;
			vector<int> randoms;
			for (int i = 0; i < n * 2; ++i) {
				randoms.push_back(randint(n));
			}
			int i = 0;
			while (i < n) {
				cout << sp_4 << right << setw(4) << i + 1 << ") ";
				Message* p1 = new Message{ randoms[i], randoms[i], randoms[i] };
				p1->id += randoms[i * 2];
				cout << "p1->" << p1 << ", ";
				Node* n1 = new Node(p1->id, p1->id);
				n1->id += p1->id;
				cout << "n1->" << n1 << ", ";
				delete p1;
				Node* n2 = new Node(n1->id, n1->id);
				n2->id += n1->id;
				cout << "n2->" << n2 << endl;
				i++;
			}
			cout << vsp_4;

			i = 0;
			while (i < n) {
				cout << sp_4 << right << setw(4) << i + 1 << ") ";
				Node* n1 = new Node(randoms[i], randoms[i]);
				n1->id += n1->id;
				cout << "n1->" << n1 << ", ";
				Node* n2 = new Node(n1->id, n1->id);
				n2->id += n1->id;
				cout << "n2->" << n2 << ", ";
				Message* p1 = new Message{ n2->id, n2->id, n2->id };
				p1->id += n2->id;
				cout << "p1->" << p1 << endl;
				delete p1;
				i++;
			}

			cout << vsp_2 << "This example does not work correctly. "
				"This is probably caused by compiler optimization." << endl;

			cout << vsp_2;
			break;
		}
		case CASE2: {
			cout << endl;
			for (unsigned int i; cin >> i; ) {
				cout << dec << i << " == "
					<< hex << "0x" << i << " == "
					<< bitset<8 * sizeof(int)>{i} << '\n';
			}


			cout << vsp_2;
			break;
		}
		case CASE3: {
			cout << endl;
			unsigned char max = 160; // very large
			for (signed char i = 0; i < max; ++i) cout << int(i) << '\n';

			cout << vsp_2;
			break;
		}
		case CASE4: {
			cout << endl;
			int si = 128;
			unsigned int ui = si;
			cout << dec << si << " == "
				<< hex << "0x" << si << " == "
				<< bitset<8 * sizeof(int)>{ui} << '\n';

			cout << vsp_2;
			break;
		}
		case CASE5: {
			cout << endl;
			Encrypt();
			cout << vsp_2;
			break;
		}
		case CASE6: {
			cout << endl;
			Decrypt();
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

void Encrypt()
{
	const int nchar = 2 * sizeof(long); // 64 bits
	const int kchar = 2 * nchar; // 128 bits
	string op;
	string key;
	string infile;
	string outfile;
	cout << "please enter input file name, output file name, and key:\n";
	cin >> infile >> outfile >> key;
	while (key.size() < kchar) key += '0'; // pad key
	ifstream inf(infile);
	ofstream outf(outfile);
	if (!inf || !outf) error("bad file name");
	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());
	unsigned long outptr[2];
	char inbuf[nchar];
	unsigned long* inptr = reinterpret_cast<unsigned long*>(inbuf);
	int count = 0;
	while (inf.get(inbuf[count])) {
		outf << hex; // use hexadecimal output
		if (++count == nchar) {
			encipher(inptr, outptr, k);
			// pad with leading zeros:
			outf << setw(8) << setfill('0') << outptr[0] << ' '
				<< setw(8) << setfill('0') << outptr[1] << ' ';
			count = 0;
		}
	}
	if (count) { // pad
		while (count != nchar) inbuf[count++] = '0';
		encipher(inptr, outptr, k);
		outf << outptr[0] << ' ' << outptr[1] << ' ';
	}
}

void Decrypt()
{
	const int nchar = 2 * sizeof(long); // 64 bits
	const int kchar = 2 * nchar; // 128 bits
	string op;
	string key;
	string infile;
	string outfile;
	cout << "please enter input file name, output file name, and key:\n";
	cin >> infile >> outfile >> key;
	while (key.size() < kchar) key += '0'; // pad key
	ifstream inf(infile);
	ofstream outf(outfile);
	if (!inf || !outf) error("bad file name");
	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());
	unsigned long inptr[2];
	char outbuf[nchar + 1];
	outbuf[nchar] = 0; // terminator
	unsigned long* outptr = reinterpret_cast<unsigned long*>(outbuf);
	inf.setf(ios_base::hex, ios_base::basefield); // use hexadecimal input
	while (inf >> inptr[0] >> inptr[1]) {
		decipher(inptr, outptr, k);
		outf << outbuf;
	}
}

void encipher(
	const unsigned long* const v,
	unsigned long* const w,
	const unsigned long* const k)
{
	static_assert(sizeof(long) == 4, "size of long wrong for TEA");
	unsigned long y = v[0];
	unsigned long z = v[1];
	unsigned long sum = 0;
	const unsigned long delta = 0x9E3779B9;
	for (unsigned long n = 32; n-- > 0; ) {
		y += (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
		sum += delta;
		z += (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
	}
	w[0] = y;
	w[1] = z;
}

void decipher(
	const unsigned long* const v,
	unsigned long* const w,
	const unsigned long* const k)
{
	static_assert(sizeof(long) == 4, "size of long wrong for TEA");
	unsigned long y = v[0];
	unsigned long z = v[1];
	unsigned long sum = 0xC6EF3720;
	const unsigned long delta = 0x9E3779B9;
	// sum = delta<<5, in general sum = delta * n
	for (unsigned long n = 32; n-- > 0; ) {
		z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
	}
	w[0] = y;
	w[1] = z;
}
