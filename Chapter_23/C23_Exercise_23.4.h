/* Exercise 23.4 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

using Line_iter = vector<string>::const_iterator;

class Message {								// a Message points to the first and the last lines of a message
	Line_iter first;
	Line_iter last;
public:
	Message(Line_iter p1, Line_iter p2) :first{ p1 }, last{ p2 } { }
	Line_iter begin() const { return first; }
	Line_iter end() const { return last; }
	//...
};

using Mess_iter = vector<Message>::const_iterator;

struct Mail_file {							// a Mail_file holds all the lines from a file
											// and simplifies access to messages
	string name;							// file name
	vector<string> lines;					// the lines in order
	vector<Message> m;						// Messages in order
	Mail_file(const string& n);				// read file n into lines
	Mess_iter begin() const { return m.begin(); }
	Mess_iter end() const { return m.end(); }
};

// find the name of the sender in a Message;
// return true if found
// if found, place the sender’s name in s:
bool find_from_addr(const Message* m, string& s);
string find_from(const Message* m);
// return the subject of the Message, if any, otherwise "":
string find_subject(const Message* m);
