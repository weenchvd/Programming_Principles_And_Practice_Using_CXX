/* Exercise 27.12 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"C27_Exercise_27.12.h"


int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10
	};
	const char* actionList = "\tList of actions:\n"
		"  (1) Find(), (2) Insert(), (3) Remove(), (4) PrintTable()\n"
		"  (-1) Exit, (0) Print the list of actions\n\n";
	printf("%s", actionList);
	Table tab;
	Initialize(&tab, 5);
	size_t bufSize = BUFFERSIZE;
	char buf[BUFFERSIZE];
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
			printf("\tEnter a string without a space to search: ");
			if (scanf("%199s", buf) <= 0) {
				PrintError("Read error");
				break;
			}
			Record* result = Find(&tab, buf);
			if (result == NULL) {
				printf("\t\tString not found\n");
				break;
			}
			else {
				printf("\t\tString \'%s\', value \'%d\'\n", result->str, result->val);
			}
			break;
		}
		case CASE2: {
			printf("\tEnter a string without a space (max length is %d): ", BUFFERSIZE - 1);
			if (scanf("%200s", buf) <= 0) {
				PrintError("Read error");
				break;
			}
			int value;
			printf("\tEnter value: ");
			if (scanf("%d", &value) <= 0) {
				PrintError("Read error");
				break;
			}
			if (Insert(&tab, buf, value) == false) {
				PrintError("Insert() error");
			}
			break;
		}
		case CASE3: {
			printf("\tEnter a string without a space: ");
			if (scanf("%199s", buf) <= 0) {
				PrintError("Read error");
				break;
			}
			if (Remove(&tab, buf) == false) {
				PrintError("Remove() error");
			}
			break;
		}
		case CASE4:
			PrintTable(&tab);
			break;
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

Record* Find(Table* table, const char* string)
{
	if (table == NULL) {
		PrintError("Find(): arg1 == NULL");
		return NULL;
	}
	if (string == NULL) {
		PrintError("Find(): arg2 == NULL");
		return NULL;
	}
	for (int i = 0; i < table->maxsz; ++i) {
		if (table->rec[i] != NULL && strcmp(table->rec[i]->str, string) == 0) {
			return table->rec[i];
		}
	}
	return NULL;
}

bool Insert(Table* table, const char* string, int value)
{
	if (table == NULL) {
		PrintError("Insert(): arg1 == NULL");
		return false;
	}
	if (string == NULL) {
		PrintError("Insert(): arg2 == NULL");
		return false;
	}
	if (table->sz == table->maxsz) {
		if (Extend(table, table->maxsz * 2) == false)
			return false;
	}
	for (int i = 0; i < table->maxsz; ++i) {
		if (table->rec[i] == NULL) {
			table->rec[i] = CreateRecord(string, value);
			if (table->rec[i] == NULL) return false;
			++table->sz;
			return true;
		}
	}
	return false;
}

bool Remove(Table* table, const char* string)
{
	if (table == NULL) {
		PrintError("Remove(): arg1 == NULL");
		return false;
	}
	if (string == NULL) {
		PrintError("Remove(): arg2 == NULL");
		return false;
	}
	Record* record = Find(table, string);
	if (record == NULL) {
		PrintError("Remove(): not found");
		return false;
	}
	Record** ptr = NULL;
	for (int i = 0; i < table->maxsz; ++i) {
		if (record == table->rec[i]) {
			ptr = &table->rec[i];
			break;
		}
	}
	RemoveRecord(ptr);
	--table->sz;
	return true;
}

Record* CreateRecord(const char* string, int value)
{
	Record* record = (Record*)malloc(sizeof(Record));
	if (record == NULL) {
		PrintError("CreateRecord(): no memory allocated");
		return NULL;
	}
	record->str = (char*)malloc(sizeof(char) * strlen(string) + 1);
	if (record->str == NULL) {
		PrintError("CreateRecord(): no memory allocated");
		return NULL;
	}
	strcpy(record->str, string);
	record->val = value;
	return record;
}

void RemoveRecord(Record** record)
{
	free((*record)->str);
	free(*record);
	*record = NULL;
}

bool Initialize(Table* table, size_t size)
{
	if (table == NULL) {
		PrintError("Initialize(): arg1 == NULL");
		return false;
	}
	if (size == 0) {
		PrintError("Initialize(): arg2 == 0");
		return false;
	}
	table->rec = (Record**)malloc(sizeof(Record*) * size);
	if (table->rec == NULL) {
		PrintError("Initialize(): no memory allocated");
		return false;
	}
	table->sz = 0;
	table->maxsz = size;
	for (int i = table->sz; i < table->maxsz; ++i) {
		table->rec[i] = NULL;
	}
	return true;
}

bool Extend(Table* table, size_t newSize)
{
	if (table == NULL) {
		PrintError("Initialize(): arg1 == NULL");
		return false;
	}
	if (newSize <= table->maxsz) {
		PrintError("Initialize(): new size <= old size");
		return false;
	}
	Record** newBlock = (Record**)realloc(table->rec, sizeof(Record*) * newSize);
	if (newBlock == NULL) {
		PrintError("Initialize(): no memory reallocated");
		return false;
	}
	table->rec = newBlock;
	table->maxsz = newSize;
	for (int i = table->sz; i < table->maxsz; ++i) {
		table->rec[i] = NULL;
	}
	return true;
}

bool Destroy(Table* table)
{
	if (table == NULL) {
		PrintError("Destroy(): arg1 == NULL");
		return false;
	}
	for (int i = 0; i < table->maxsz; ++i) {
		if (table->rec[i] != NULL) {
			RemoveRecord(&table->rec[i]);
		}
	}
	return true;
}

void PrintTable(Table* table)
{
	if (table == NULL) {
		return PrintError("PrintTable(): arg1 == NULL");
	}
	for (int i = 0; i < table->maxsz; ++i) {
		if (table->rec[i] != NULL) {
			printf("\t\t#%d: \"%s\", \'%d\'\n", i + 1, table->rec[i]->str, table->rec[i]->val);
		}
	}
}
