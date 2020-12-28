/* Exercise 27.9 */

#ifndef C27_Exercise_27_9_H
#define C27_Exercise_27_9_H

#define SIZEOFWORD 256

enum ReturnTypeCommon { FAILURE = -1, SUCCESS };

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

struct List {
	struct Link* first;
	struct Link* last;
};

struct Link {								/* link for doubly-linked list */
	struct Link* pre;
	struct Link* suc;
};

struct LLWord {
	struct Link lnk;						/* the Link required by List operations */
	char* ps;								/* the name string */
};

typedef struct {
	char** arr;
	size_t sz;
	size_t maxsz;
} Word;

void Init(struct List* lst);
struct List* Create();
void Clear(struct List* lst);
void Destroy(struct List* lst);
void PushBack(struct List* lst, struct Link* p);
void PushFront(struct List* lst, struct Link* p);
void Insert(struct List* lst, struct Link* p, struct Link* q);
struct Link* Erase(struct List* lst, struct Link* p);
struct Link* Advance(struct Link* p, int n);

struct LLWord* MakeWord(char* n);
void PrintWordList(struct List* lst);
void PrintError(const char* message);

char* CreateString(size_t size);
bool GetString(char* string, size_t size);
bool Extend(Word* w, size_t newSize);
bool AddWord(Word* w, char* word);
bool AddWordToLinkedList(struct List* lst, char* word);
int CompareWords(const void* word1, const void* word2);

#endif