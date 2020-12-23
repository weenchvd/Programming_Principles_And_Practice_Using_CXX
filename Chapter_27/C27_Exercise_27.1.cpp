/* Exercise 27.1 */

#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include"C27_Exercise_27.1.h"


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const char* actionList = "\tList of actions:\n"
		"  (1) StrLen(), (2) StrCmp(), (3) StrCpy()\n"
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
			const char* str1 = "C string";
			printf("\tSize of string \'%s\': %d", str1, StrLen(str1));
			putchar('\n');
			break;
		}
		case CASE2: {
			putchar('\n');
			{
				const char* str1 = "bbb";
				const char* str2 = "bbbaaa";
				int result = StrCmp(str1, str2);
				char sign;
				if (result < 0) sign = '<';
				else if (result > 0) sign = '>';
				else sign = '=';
				printf("\t\'%s\' %c \'%s\'\n", str1, sign, str2);
			}
			{
				const char* str1 = "abc";
				const char* str2 = "abc";
				int result = StrCmp(str1, str2);
				char sign;
				if (result < 0) sign = '<';
				else if (result > 0) sign = '>';
				else sign = '=';
				printf("\t\'%s\' %c \'%s\'\n", str1, sign, str2);
			}
			{
				const char* str1 = "adc";
				const char* str2 = "abc";
				int result = StrCmp(str1, str2);
				char sign;
				if (result < 0) sign = '<';
				else if (result > 0) sign = '>';
				else sign = '=';
				printf("\t\'%s\' %c \'%s\'\n", str1, sign, str2);
			}
			putchar('\n');
			break;
		}
		case CASE3: {
			putchar('\n');
			const char* source = "abc";
			char dest[4];
			StrCpy(dest, source);
			printf("\tSource: %s\n\tDestination: %s", source, dest);
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

size_t StrLen(const char* s)
{
	size_t sz = 0;
	while (s[sz] != '\0') ++sz;
	return sz;
}

int StrCmp(const char* str1, const char* str2)
{
	size_t i = 0;
	while (str1[i] != '\0' && str2[i] != '\0') {
		if (str1[i] == str2[i]) ++i;
		else break;
	}
	return str1[i] - str2[i];
}

char* StrCpy(char* destination, const char* source)
{
	size_t i = 0;
	while ((destination[i] = source[i]) != '\0') ++i;
	return destination;
}
