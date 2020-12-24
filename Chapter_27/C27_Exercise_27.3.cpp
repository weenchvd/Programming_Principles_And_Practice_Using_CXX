/* Exercise 27.3 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"C27_Exercise_27.3.h"


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const char* actionList = "\tList of actions:\n"
		"  (1) Test (the test only works in the debug configuration)\n"
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
			
			struct List* list = Create();
			assert(list != NULL);
			PushBack(list, (struct Link*)MakeName("Alexa"));
			assert(list->first != NULL);
			assert(list->first == list->last);
			assert(list->first->pre == NULL);
			assert(list->first->suc == NULL);
			assert(strcmp(((struct Name*)list->first)->ps, "Alexa") == 0);
			PushBack(list, (struct Link*)MakeName("Siri"));
			assert(list->first != NULL);
			assert(list->last != NULL);
			assert(list->first->suc == list->last);
			assert(list->last->pre == list->first);
			assert(list->first->pre == NULL);
			assert(list->last->suc == NULL);
			assert(strcmp(((struct Name*)list->first)->ps, "Alexa") == 0);
			assert(strcmp(((struct Name*)list->last)->ps, "Siri") == 0);

			Clear(list);
			assert(list->first == NULL);
			assert(list->first == list->last);
			PushFront(list, (struct Link*)MakeName("Alexa"));
			assert(list->first != NULL);
			assert(list->first == list->last);
			assert(list->first->pre == NULL);
			assert(list->first->suc == NULL);
			assert(strcmp(((struct Name*)list->first)->ps, "Alexa") == 0);
			PushFront(list, (struct Link*)MakeName("Siri"));
			assert(list->first != NULL);
			assert(list->last != NULL);
			assert(list->first->suc == list->last);
			assert(list->last->pre == list->first);
			assert(list->first->pre == NULL);
			assert(list->last->suc == NULL);
			assert(strcmp(((struct Name*)list->first)->ps, "Siri") == 0);
			assert(strcmp(((struct Name*)list->last)->ps, "Alexa") == 0);

			struct Link* alexa = Advance(list->first, 1);
			assert(alexa != NULL);
			assert(strcmp(((struct Name*)alexa)->ps, "Alexa") == 0);
			struct Link* siri = Advance(list->last, -1);
			assert(siri != NULL);
			assert(strcmp(((struct Name*)siri)->ps, "Siri") == 0);
			alexa = Advance(list->last, 0);
			assert(alexa != NULL);
			assert(strcmp(((struct Name*)alexa)->ps, "Alexa") == 0);
			struct Link* empty = Advance(list->first, 2);
			assert(empty == NULL);
			empty = Advance(list->last, -2);
			assert(empty == NULL);

			Destroy(list);
			printf("\t\tAll tests passed\n");

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

struct Name* MakeName(char* n)
{
	struct Name* p = (struct Name*)malloc(sizeof(struct Name));
	if (p == NULL) {
		PrintError("MakeName(): no memory allocated");
		return NULL;
	}
	p->ps = n;
	return p;
}

void PrintNameList(struct List* lst)
{
	if (lst == NULL)
		return PrintError("PrintNameList(): arg1 == NULL");
	printf("\tName list:\n");
	int num = 0;
	for (struct Link* cur = lst->first; cur != NULL; cur = cur->suc) {
		printf("Element %d: %s\n", ++num, ((struct Name*)cur)->ps);
	}
}

void PrintError(const char* message)
{
	fprintf(stderr, "\t\tError -> ");
	fprintf(stderr, message);
	fprintf(stderr, "\n");
}
