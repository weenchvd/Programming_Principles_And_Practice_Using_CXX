/* Exercise 27.2 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include"C27_Exercise_27.2.h"


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const char* actionList = "\tList of actions:\n"
		"  (1) Test\n"
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
			PushBack(list, (struct Link*)MakeName("Petra"));
			PushBack(list, (struct Link*)MakeName("Alexa"));
			PushFront(list, (struct Link*)MakeName("Alisa"));
			PushFront(list, (struct Link*)MakeName("Naomi"));
			PushBack(list, (struct Link*)MakeName("Siri"));
			PrintNameList(list);
			struct Link* alisa = Advance(list->first, 1);
			Erase(list, alisa);
			struct Link* petra = Advance(list->last, -2);
			Erase(list, petra);
			PrintNameList(list);
			Insert(list, list->first, alisa);
			Insert(list, alisa, petra);
			PrintNameList(list);
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
	assert(lst);
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
	assert(lst);
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
	assert(lst);
	Clear(lst);
	free(lst);
}

void PushBack(struct List* lst, struct Link* p)				/* add p at end of lst */
{
	assert(lst);
	if (p == NULL) return;
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
	assert(lst);
	if (p == NULL) return;
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
	assert(lst);
	if (q == NULL) return;
	assert(p);
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
	assert(lst);
	if (p == NULL) return NULL;				/* OK to erase(0) */
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
	assert(p);
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
	if (p == NULL) return NULL;
	p->ps = n;
	return p;
}

void PrintNameList(struct List* lst)
{
	printf("\tName list:\n");
	int num = 0;
	for (struct Link* cur = lst->first; cur != NULL; cur = cur->suc) {
		printf("Element %d: %s\n", ++num, ((struct Name*)cur)->ps);
	}
}
