/* Exercise 27.13 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"C27_Exercise_27.13.h"


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const char* actionList = "\tList of actions:\n"
		"  (1) Read string\n"
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
			FILE* pOut;
			pOut = fopen("C27_Exercise_27.13.txt", "w");
			if (pOut == NULL) break;
			String s;
			Initialize(&s, 5);
			printf("Enter a string (press ENTER -> CONTROL+Z -> ENTER to end input):\n");
			while (GetString(stdin, &s)) {
				fprintf(pOut, "%s\n", s.str);
			}
			Destroy(&s);
			fclose(pOut);
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

void PrintError(const char* message)
{
	fprintf(stderr, "\t\tError -> ");
	fprintf(stderr, message);
	fprintf(stderr, "\n");
}

bool Initialize(String* string, size_t size)
{
	if (string == NULL) {
		PrintError("Initialize(): arg1 == NULL");
		return false;
	}
	if (size == 0) {
		PrintError("Initialize(): arg2 == 0");
		return false;
	}
	string->str = (char*)malloc(sizeof(char) * size);
	if (string->str == NULL) {
		PrintError("Initialize(): no memory allocated");
		return false;
	}
	string->sz = 0;
	string->maxsz = size;
	return true;
}

bool Extend(String* string)
{
	if (string == NULL) {
		PrintError("Extend(): arg1 == NULL");
		return false;
	}
	char* newBlock = (char*)realloc(string->str, sizeof(char) * string->maxsz * EXTENDMULTIPLIER);
	if (newBlock == NULL) {
		PrintError("Extend(): no memory reallocated");
		return false;
	}
	string->str = newBlock;
	string->maxsz *= EXTENDMULTIPLIER;
	return true;
}

bool Destroy(String* string)
{
	if (string == NULL) {
		PrintError("Destroy(): arg1 == NULL");
		return false;
	}
	free(string->str);
	string->str = NULL;
	string->sz = string->maxsz = 0;
	return true;
}

bool GetString(FILE* stream, String* string)
{
	if (string == NULL) {
		PrintError("GetString(): arg1 == NULL");
		return false;
	}
	if (feof(stream)) return false;
	int c;
	while (true) {
		c = getc(stream);
		if (c == EOF) return false;
		if (isspace(c) == false) {
			ungetc(c, stream);
			break;
		}
	}
	string->sz = 0;
	string->str[string->sz] = '\0';
	while (true) {
		c = getc(stream);
		if (string->sz == string->maxsz) {
			if (Extend(string) == false) {
				ungetc(c, stream);
				ungetc(string->str[--string->sz], stream);
				string->str[string->sz] = '\0';
				return false;
			}
		}
		if (isspace(c)) {
			string->str[string->sz++] = '\0';
			return true;
		}
		string->str[string->sz++] = c;
	}
}
