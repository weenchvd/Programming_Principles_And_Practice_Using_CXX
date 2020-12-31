/* Exercise 27.14 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"C27_Exercise_27.14.h"


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const char* actionList = "\tList of actions:\n"
		"  (1) LargestSmallestMedianMean()\n"
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
			printf("\nPlease enter size of array: ");
			int size;
			if (scanf("%d", &size) <= 0 || size <= 0) {
				PrintError("Incorrect input");
				break;
			}
			int* arr = (int*)malloc(sizeof(int) * size);
			if (arr == NULL) {
				PrintError("No memory reallocated");
				break;
			}
			bool proceed = true;
			for (int i = 0; i < size; ++i) {
				printf("Please enter a number #%d: ", i + 1);
				int number;
				if (scanf("%d", &number) <= 0) {
					PrintError("Incorrect input");
					proceed = false;
					break;
				}
				arr[i] = number;
			}
			Value* pval = LargestSmallestMedianMean(arr, size);
			if (pval == NULL) break;
			printf("Largest: %d\n", pval->largest);
			printf("Smallest: %d\n", pval->smallest);
			printf("Median: %f\n", pval->median);
			printf("Mean: %f\n", pval->mean);

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

Value* LargestSmallestMedianMean(int* arr, size_t size)
{
	if (arr == NULL) {
		PrintError("LargestSmallestMedianMean(): arg1 == NULL");
		return NULL;
	}
	Value* pval = (Value*)malloc(sizeof(Value));
	if (pval == NULL) {
		PrintError("LargestSmallestMedianMean(): no memory reallocated");
		return NULL;
	}
	qsort(arr, size, sizeof(int), CompareInt);
	pval->largest = arr[size - 1];
	pval->smallest = arr[0];
	if (size % 2) {
		pval->median = arr[size / 2];
	}
	else {
		pval->median = (arr[size / 2 - 1] + arr[size / 2]) / 2;
	}
	pval->mean = 0.0;
	for (int i = 0; i < size; ++i) {
		pval->mean += arr[i];
	}
	pval->mean /= size;
	return pval;
}

int CompareInt(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}