/* Exercise 27.6 */

#ifndef C27_Exercise_27_6_H
#define C27_Exercise_27_6_H

#define NOTINDEX -1
#define DEFAULTSIZEOFLIST 10
#define DEFAULTMULTIPLIEREXPAND 2

enum ReturnTypeCommon { FAILURE = -1, SUCCESS };

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

struct List {
	int first;
	int last;
	struct Link** arr;
	int sz;									// size of array
	int ff;									// first free pointer
};

struct Link {								/* link for doubly-linked list */
	int pre;
	int suc;
};

struct Name {
	struct Link lnk;						/* the Link required by List operations */
	char* ps;								/* the name string */
};

void Init(struct List* lst);
struct List* Create();
void Clear(struct List* lst);
void Destroy(struct List* lst);
void PushBack(struct List* lst, struct Link* p);
void PushFront(struct List* lst, struct Link* p);
void Insert(struct List* lst, struct Link* p, struct Link* q);
struct Link* Erase(struct List* lst, struct Link* p);
struct Link* Advance(struct List* lst, struct Link* p, int n);
bool Expand(struct List* lst);
void FindFreePointer(struct List* lst);
int FindIndex(struct List* lst, struct Link* p);

struct Name* MakeName(char* n);
void PrintNameList(struct List* lst);
void PrintError(const char* message);

#endif