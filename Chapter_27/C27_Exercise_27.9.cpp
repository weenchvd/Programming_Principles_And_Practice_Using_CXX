/* Exercise 27.9 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"C27_Exercise_27.9.h"


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const char* actionList = "\tList of actions:\n"
		"  (1) Read and sort words\n"
		"  (-1) Exit, (0) Print the list of actions\n\n";
	printf("%s", actionList);
	int action;
	bool cond = true;
	while (cond) {
		printf("\nPlease enter the action: ");
		int ret = scanf("%d", &action);
		char ch;
		while ((ch = getchar()) != '\n');
		if (ret <= 0) {
			printf("\n\n\t\tError. Incorrect input\n");
			continue;
		}
		switch (action) {
		case CASE1: {
			putchar('\n');
			
			printf("Please enter words (press \'ENTER, CTRL+Z, ENTER\' to end):\n");
			struct List* list = Create();
			Word words;
			words.arr = NULL;
			words.sz = 0;
			words.maxsz = 100;
			if (Extend(&words, words.maxsz) == false) break;
			while (!feof(stdin)) {
				char* newWord = CreateString(SIZEOFWORD);
				if (newWord == NULL) break;
				if (GetString(newWord, SIZEOFWORD) == false) break;
				if (AddWord(&words, newWord) == false) break;
				if (AddWordToLinkedList(list, newWord) == false) break;
			}
			qsort(words.arr, words.sz, sizeof(char*), CompareWords);

			printf("\tSorted list:\n");
			for (int i = 0; i < words.sz; ++i) {
				printf("%d: %s\n", i + 1, words.arr[i]);
			}
			printf("%s", vsp_2);
			PrintWordList(list);
			
			for (int i = 0; i < words.sz; ++i) {
				free(words.arr[i]);
			}
			Destroy(list);

			putchar('\n');
			break;
		}
		case PRINTACTIONLIST:
			printf("%s", actionList);
			break;
		case EXIT:
			cond = false;
			break;
		default:
			printf("\t\tError. Incorrect action number\n");
			break;
		}
	}
	return SUCCESS;
}

void Init(struct List* lst)					/* initialize *lst to the empty list */
{
	if (lst == NULL)
		return PrintError("Init(): arg1 == NULL");
	lst->first = lst->last = NULL;
}

struct List* Create()						/* make a new empty list */
{
	struct List* lst = (struct List*)malloc(sizeof(struct List));
	Init(lst);
	return lst;
}

void Clear(struct List* lst)				/* free all elements of lst */
{
	if (lst == NULL)
		return PrintError("Clear(): arg1 == NULL");
	struct Link* curr = lst->first;
	while (curr) {
		struct Link* next = curr->suc;
		free(curr);
		curr = next;
	}
	lst->first = lst->last = NULL;
}

void Destroy(struct List* lst)				/* free all elements of lst; then free lst */
{
	Clear(lst);
	free(lst);
}

void PushBack(struct List* lst, struct Link* p)				/* add p at end of lst */
{
	if (lst == NULL) 
		return PrintError("PushBack(): arg1 == NULL");
	if (p == NULL)
		return PrintError("PushBack(): arg2 == NULL");
	struct Link* last = lst->last;
	if (last) {
		last->suc = p;					/* add p after last */
		p->pre = last;
	}
	else {
		lst->first = p;					/* p is the first element */
		p->pre = NULL;
	}
	lst->last = p;						/* p is the new last element */
	p->suc = NULL;
}

void PushFront(struct List* lst, struct Link* p)				/* add p at front of lst */
{
	if (lst == NULL)
		return PrintError("PushFront(): arg1 == NULL");
	if (p == NULL)
		return PrintError("PushFront(): arg2 == NULL");
	struct Link* first = lst->first;
	if (first) {
		p->suc = first;
		first->pre = p;
	}
	else {
		lst->last = p;
		p->suc = NULL;
	}
	lst->first = p;
	p->pre = NULL;
}

void Insert(struct List* lst, struct Link* p, struct Link* q)	/* insert q before p in lst: */
{
	if (lst == NULL)
		return PrintError("Insert(): arg1 == NULL");
	if (p == NULL)
		return PrintError("Insert(): arg2 == NULL");
	if (q == NULL)
		return;
	q->pre = p->pre;
	q->suc = p;
	if (p == lst->first) {
		lst->first = q;
	}
	else {
		p->pre->suc = q;
	}
	p->pre = q;
}

struct Link* Erase(struct List* lst, struct Link* p)
	/*
		remove p from lst;
		return a pointer to the link after p
	*/
{
	if (lst == NULL) {
		PrintError("Erase(): arg1 == NULL");
		return NULL;
	}
	if (p == NULL)
		return NULL;						/* OK to erase(0) */
	if (p == lst->first) {
		if (p->suc) {
			lst->first = p->suc;			/* the successor becomes first */
			p->suc->pre = NULL;
			return p->suc;
		}
		else {
			lst->first = lst->last = NULL;	/* the list becomes empty */
			return NULL;
		}
	}
	else if (p == lst->last) {
		if (p->pre) {
			lst->last = p->pre;				/* the predecessor becomes last */
			p->pre->suc = NULL;
		}
		else {
			lst->first = lst->last = NULL;	/* the list becomes empty */
		}
		return NULL;
	}
	else {
		p->suc->pre = p->pre;
		p->pre->suc = p->suc;
		return p->suc;
	}
}

struct Link* Advance(struct Link* p, int n)						/* return link n “hops” before or after p: */
{
	if (p == NULL) {
		PrintError("Advance(): arg2 == NULL");
		return NULL;
	}
	while (n != 0 && p != NULL) {
		if (n > 0) {
			p = p->suc;
			--n;
		}
		else {
			p = p->pre;
			++n;
		}
	}
	return p;
}

struct LLWord* MakeWord(char* n)
{
	struct LLWord* p = (struct LLWord*)malloc(sizeof(struct LLWord));
	if (p == NULL) {
		PrintError("MakeName(): no memory allocated");
		return NULL;
	}
	p->ps = n;
	return p;
}

void PrintWordList(struct List* lst)
{
	if (lst == NULL)
		return PrintError("PrintWordList(): arg1 == NULL");
	printf("\tSorted linked list:\n");
	int num = 0;
	for (struct Link* cur = lst->first; cur != NULL; cur = cur->suc) {
		printf("%d: %s\n", ++num, ((struct LLWord*)cur)->ps);
	}
}

void PrintError(const char* message)
{
	fprintf(stderr, "\t\tError -> ");
	fprintf(stderr, message);
	fprintf(stderr, "\n");
}

char* CreateString(size_t size)
{
	char* s = (char*)malloc(sizeof(char) * size);
	if (s == NULL) {
		PrintError("CreateString(): no memory allocated");
	}
	return s;
}

bool GetString(char* string, size_t size)
{
	char ch;
	while (isspace(ch = getchar())) {
		if (feof(stdin)) {
			string[0] = '\0';
			return false;
		}
	}
	ungetc(ch, stdin);
	size_t i;
	for (i = 0; i < size - 1; ++i) {
		ch = getchar();
		if (isspace(ch) || feof(stdin)) break;
		string[i] = ch;
	}
	string[i] = '\0';
	if (i == 0) return false;
	return true;
}

bool Extend(Word* w, size_t newSize)
{
	if (newSize <= w->sz) {
		PrintError("Resize(): new size <= old size");
		return false;
	}
	char** newBlock = (char**)realloc(w->arr, newSize);
	if (newBlock == NULL) {
		PrintError("Resize(): no memory reallocated");
		return false;
	}
	w->arr = newBlock;
	w->maxsz = newSize;
	return true;
}

bool AddWord(Word* w, char* word)
{
	if (w == NULL) {
		PrintError("AddWord(): arg1 == NULL");
		return false;
	}
	if (word == NULL) {
		PrintError("AddWord(): arg2 == NULL");
		return false;
	}
	if (w->sz == w->maxsz) {
		if (Extend(w, w->maxsz * 2) == false) return false;
	}
	w->arr[w->sz++] = word;
	return true;
}

bool AddWordToLinkedList(struct List* lst, char* word)
{
	if (lst == NULL) {
		PrintError("AddWord(): arg1 == NULL");
		return false;
	}
	if (word == NULL) {
		PrintError("AddWord(): arg2 == NULL");
		return false;
	}
	struct LLWord* llw = MakeWord(word);
	if (llw == NULL) return false;
	if (lst->first == NULL) {
		PushBack(lst, (struct Link*)llw);
		return true;
	}
	for (struct Link* cur = lst->first; cur != NULL; cur = cur->suc) {
		struct LLWord* p = (struct LLWord*)cur;
		if (strcmp(llw->ps, p->ps) <= 0) {
			if (cur == lst->first) {
				PushFront(lst, (struct Link*)llw);
			}
			else {
				Insert(lst, cur, (struct Link*)llw);
			}
			return true;
		}
	}
	PushBack(lst, (struct Link*)llw);
	return true;
}

int CompareWords(const void** word1, const void** word2)
{
	return strcmp(*((char**)word1), *((char**)word2));
}
