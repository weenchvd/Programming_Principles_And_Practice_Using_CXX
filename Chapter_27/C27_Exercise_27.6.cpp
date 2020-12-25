/* Exercise 27.6 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"C27_Exercise_27.6.h"


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
			for (int i = 0; i < list->sz; ++i) {
				assert(list->arr[i] == NULL);
			}
			PushBack(list, (struct Link*)MakeName("Alexa"));
			assert(list->first != NOTINDEX);
			assert(list->first == list->last);
			assert(list->arr[list->first]->pre == NOTINDEX);
			assert(list->arr[list->first]->suc == NOTINDEX);
			assert(strcmp(((struct Name*)list->arr[list->first])->ps, "Alexa") == 0);
			PushBack(list, (struct Link*)MakeName("Siri"));
			assert(list->first != NOTINDEX);
			assert(list->last != NOTINDEX);
			assert(list->arr[list->first]->suc == list->last);
			assert(list->arr[list->last]->pre == list->first);
			assert(list->arr[list->first]->pre == NOTINDEX);
			assert(list->arr[list->last]->suc == NOTINDEX);
			assert(strcmp(((struct Name*)list->arr[list->first])->ps, "Alexa") == 0);
			assert(strcmp(((struct Name*)list->arr[list->last])->ps, "Siri") == 0);
			assert(list->arr[0] != NULL);
			assert(list->arr[1] != NULL);
			for (int i = 2; i < list->sz; ++i) {
				assert(list->arr[i] == NULL);
			}
			PrintNameList(list);
			Clear(list);


			for (int i = 0; i < list->sz; ++i) {
				assert(list->arr[i] == NULL);
			}
			assert(list != NULL);
			assert(list->first == NOTINDEX);
			assert(list->first == list->last);
			PushFront(list, (struct Link*)MakeName("Alexa"));
			assert(list->first != NOTINDEX);
			assert(list->first == list->last);
			assert(list->arr[list->first]->pre == NOTINDEX);
			assert(list->arr[list->first]->suc == NOTINDEX);
			assert(strcmp(((struct Name*)list->arr[list->first])->ps, "Alexa") == 0);
			PushFront(list, (struct Link*)MakeName("Siri"));
			assert(list->first != NOTINDEX);
			assert(list->last != NOTINDEX);
			assert(list->arr[list->first]->suc == list->last);
			assert(list->arr[list->last]->pre == list->first);
			assert(list->arr[list->first]->pre == NOTINDEX);
			assert(list->arr[list->last]->suc == NOTINDEX);
			assert(strcmp(((struct Name*)list->arr[list->first])->ps, "Siri") == 0);
			assert(strcmp(((struct Name*)list->arr[list->last])->ps, "Alexa") == 0);
			assert(list->arr[0] != NULL);
			assert(list->arr[1] != NULL);
			for (int i = 2; i < list->sz; ++i) {
				assert(list->arr[i] == NULL);
			}
			PrintNameList(list);

			struct Link* alexa = Advance(list, list->arr[list->first], 1);
			assert(alexa != NULL);
			assert(strcmp(((struct Name*)alexa)->ps, "Alexa") == 0);
			struct Link* siri = Advance(list, list->arr[list->last], -1);
			assert(siri != NULL);
			assert(strcmp(((struct Name*)siri)->ps, "Siri") == 0);
			alexa = Advance(list, list->arr[list->last], 0);
			assert(alexa != NULL);
			assert(strcmp(((struct Name*)alexa)->ps, "Alexa") == 0);
			struct Link* empty = Advance(list, list->arr[list->first], 2);
			assert(empty == NULL);
			empty = Advance(list, list->arr[list->last], -2);
			assert(empty == NULL);

			Insert(list, alexa, (struct Link*)MakeName("Petra"));
			Insert(list, alexa, (struct Link*)MakeName("Naomi"));
			Insert(list, alexa, (struct Link*)MakeName("Alisa"));
			assert(list->first != NOTINDEX);
			assert(list->last != NOTINDEX);
			assert(list->arr[list->first]->pre == NOTINDEX);
			assert(list->arr[list->last]->suc == NOTINDEX);
			assert(strcmp(((struct Name*)list->arr[list->first])->ps, "Siri") == 0);
			assert(strcmp(((struct Name*)Advance(list, list->arr[list->first], 1))->ps, "Petra") == 0);
			assert(strcmp(((struct Name*)Advance(list, list->arr[list->first], 2))->ps, "Naomi") == 0);
			assert(strcmp(((struct Name*)Advance(list, list->arr[list->last], -1))->ps, "Alisa") == 0);
			assert(strcmp(((struct Name*)list->arr[list->last])->ps, "Alexa") == 0);
			assert(strcmp(((struct Name*)list->arr[0])->ps, "Alexa") == 0);
			assert(strcmp(((struct Name*)list->arr[1])->ps, "Siri") == 0);
			assert(strcmp(((struct Name*)list->arr[2])->ps, "Petra") == 0);
			assert(strcmp(((struct Name*)list->arr[3])->ps, "Naomi") == 0);
			assert(strcmp(((struct Name*)list->arr[4])->ps, "Alisa") == 0);
			for (int i = 5; i < list->sz; ++i) {
				assert(list->arr[i] == NULL);
			}
			PrintNameList(list);

			struct Name* nsiri = (struct Name*)list->arr[list->first];
			assert(strcmp(nsiri->ps, "Siri") == 0);
			struct Name* npetra = (struct Name*)Erase(list, (struct Link*)nsiri);
			assert(strcmp(nsiri->ps, "Siri") == 0);
			free(nsiri);
			assert(strcmp(npetra->ps, "Petra") == 0);
			assert(list->arr[1] == NULL);

			struct Name* nalisa = (struct Name*)Advance(list, list->arr[list->last], -1);
			assert(strcmp(nalisa->ps, "Alisa") == 0);
			struct Name* nalexa = (struct Name*)Erase(list, (struct Link*)nalisa);
			assert(strcmp(nalisa->ps, "Alisa") == 0);
			free(nalisa);
			assert(strcmp(nalexa->ps, "Alexa") == 0);
			assert(list->arr[4] == NULL);

			assert(strcmp(((struct Name*)Advance(list, list->arr[list->first], 0))->ps, "Petra") == 0);
			assert(strcmp(((struct Name*)Advance(list, list->arr[list->first], 1))->ps, "Naomi") == 0);
			assert(strcmp(((struct Name*)Advance(list, list->arr[list->first], 2))->ps, "Alexa") == 0);
			assert(list->arr[1] == NULL);
			assert(list->arr[4] == NULL);
			assert(strcmp(((struct Name*)list->arr[0])->ps, "Alexa") == 0);
			assert(strcmp(((struct Name*)list->arr[2])->ps, "Petra") == 0);
			assert(strcmp(((struct Name*)list->arr[3])->ps, "Naomi") == 0);
			for (int i = 5; i < list->sz; ++i) {
				assert(list->arr[i] == NULL);
			}
			PrintNameList(list);

			npetra = (struct Name*)list->arr[list->first];
			Erase(list, (struct Link*)npetra);
			assert(strcmp(npetra->ps, "Petra") == 0);
			free(npetra);
			nalexa = (struct Name*)list->arr[list->last];
			Erase(list, (struct Link*)nalexa);
			assert(strcmp(nalexa->ps, "Alexa") == 0);
			free(nalexa);
			struct Name* nnaomi = (struct Name*)list->arr[list->first];
			Erase(list, (struct Link*)nnaomi);
			assert(strcmp(nnaomi->ps, "Naomi") == 0);
			free(nnaomi);
			for (int i = 0; i < list->sz; ++i) {
				assert(list->arr[i] == NULL);
			}

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
	lst->first = lst->last = NOTINDEX;
	lst->sz = DEFAULTSIZEOFLIST;
	lst->ff = 0;
	lst->arr = (struct Link**)malloc(sizeof(struct Link*) * lst->sz);
	if (lst->arr == NULL)
		return PrintError("Init(): no memory allocated");
	for (int i = 0; i < DEFAULTSIZEOFLIST; ++i) {
		lst->arr[i] = NULL;
	}
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
	for (int i = 0; i < lst->sz; ++i) {
		free(lst->arr[i]);
		lst->arr[i] = NULL;
	}
	lst->first = lst->last = NOTINDEX;
	lst->ff = 0;
}

void Destroy(struct List* lst)				/* free all elements of lst; then free lst */
{
	Clear(lst);
	free(lst->arr);
	free(lst);
}

void PushBack(struct List* lst, struct Link* p)				/* add p at end of lst */
{
	if (lst == NULL)
		return PrintError("PushBack(): arg1 == NULL");
	if (p == NULL)
		return PrintError("PushBack(): arg2 == NULL");
	if (lst->ff == NOTINDEX && Expand(lst) == false)
		return;
	int last = lst->last;
	if (last != NOTINDEX) {
		lst->arr[last]->suc = lst->ff;
		p->pre = last;
	}
	else {
		lst->first = lst->ff;
		p->pre = NOTINDEX;
	}
	lst->last = lst->ff;
	p->suc = NOTINDEX;
	lst->arr[lst->ff] = p;
	FindFreePointer(lst);
}

void PushFront(struct List* lst, struct Link* p)				/* add p at front of lst */
{
	if (lst == NULL)
		return PrintError("PushFront(): arg1 == NULL");
	if (p == NULL)
		return PrintError("PushFront(): arg2 == NULL");
	if (lst->ff == NOTINDEX && Expand(lst) == false)
		return;
	int first = lst->first;
	if (first != NOTINDEX) {
		lst->arr[first]->pre = lst->ff;
		p->suc = first;
	}
	else {
		lst->last = lst->ff;
		p->suc = NOTINDEX;
	}
	lst->first = lst->ff;
	p->pre = NOTINDEX;
	lst->arr[lst->ff] = p;
	FindFreePointer(lst);
}

void Insert(struct List* lst, struct Link* p, struct Link* q)	/* insert q before p in lst: */
{
	if (lst == NULL)
		return PrintError("Insert(): arg1 == NULL");
	if (p == NULL)
		return PrintError("Insert(): arg2 == NULL");
	if (q == NULL)
		return;
	if (lst->ff == NOTINDEX && Expand(lst) == false)
		return;
	int pindex = FindIndex(lst, p);
	if (pindex == NOTINDEX)
		return PrintError("Insert(): index == NOTINDEX");
	q->pre = p->pre;
	q->suc = pindex;
	if (pindex == lst->first) {
		lst->first = lst->ff;
	}
	else {
		lst->arr[p->pre]->suc = lst->ff;
	}
	p->pre = lst->ff;
	lst->arr[lst->ff] = q;
	FindFreePointer(lst);
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
	int pindex = FindIndex(lst, p);
	if (pindex == NOTINDEX) {
		PrintError("Erase(): index == NOTINDEX");
		return NULL;
	}
	struct Link* ret = NULL;
	if (pindex == lst->first) {
		if (p->suc != NOTINDEX) {
			lst->first = p->suc;
			lst->arr[p->suc]->pre = NOTINDEX;
			ret = lst->arr[p->suc];
		}
		else {
			lst->first = lst->last = NOTINDEX;
		}
	}
	else if (pindex == lst->last) {
		if (p->pre != NOTINDEX) {
			lst->last = p->pre;
			lst->arr[p->pre]->suc = NOTINDEX;
		}
		else {
			lst->first = lst->last = NOTINDEX;
		}
	}
	else {
		lst->arr[p->suc]->pre = p->pre;
		lst->arr[p->pre]->suc = p->suc;
		ret = lst->arr[p->suc];
	}
	lst->arr[pindex] = NULL;
	lst->ff = pindex;
	return ret;
}

struct Link* Advance(struct List* lst, struct Link* p, int n)	/* return link n “hops” before or after p: */
{
	if (lst == NULL) {
		PrintError("Advance(): arg1 == NULL");
		return NULL;
	}
	if (p == NULL) {
		PrintError("Advance(): arg2 == NULL");
		return NULL;
	}
	while (n != 0) {
		if (n > 0) {
			if (p->suc == NOTINDEX)
				return NULL;
			p = lst->arr[p->suc];
			--n;
		}
		else {
			if (p->pre == NOTINDEX)
				return NULL;
			p = lst->arr[p->pre];
			++n;
		}
	}
	return p;
}

bool Expand(struct List* lst)
{
	if (lst == NULL) {
		PrintError("Expand(): arg1 == NULL");
		return false;
	}
	int newSize = lst->sz * DEFAULTMULTIPLIEREXPAND;
	struct Link** newArr = (struct Link**)realloc(lst->arr, newSize);
	if (newArr == NULL) {
		PrintError("Expand(): no memory reallocated");
		return false;
	}
	lst->arr = newArr;
	lst->ff = lst->sz;
	lst->sz = newSize;
	return true;
}

void FindFreePointer(struct List* lst)
{
	if (lst == NULL)
		return PrintError("FindNextFreePointer(): arg1 == NULL");
	for (int i = lst->ff + 1; i < lst->sz; ++i) {
		if (lst->arr[i] == NULL) {
			lst->ff = i;
			return;
		}
	}
	for (int i = 0; i < lst->ff; ++i) {
		if (lst->arr[i] == NULL) {
			lst->ff = i;
			return;
		}
	}
	lst->ff = NOTINDEX;
}

int FindIndex(struct List* lst, struct Link* p)
{
	if (lst == NULL) {
		PrintError("FindIndex(): arg1 == NULL");
		return NOTINDEX;
	}
	if (p == NULL) {
		PrintError("FindIndex(): arg2 == NULL");
		return NOTINDEX;
	}
	for (int i = 0; i < lst->sz; ++i) {
		if (lst->arr[i] == p)
			return i;
	}
	return NOTINDEX;
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
	for (int index = lst->first; index != NOTINDEX; index = lst->arr[index]->suc) {
		printf("Element %d: %s\n", ++num, ((struct Name*)lst->arr[index])->ps);
	}
}

void PrintError(const char* message)
{
	fprintf(stderr, "\t\tError -> ");
	fprintf(stderr, message);
	fprintf(stderr, "\n");
}
