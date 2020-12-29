/* Exercise 27.12 */

#ifndef C27_Exercise_27_12_H
#define C27_Exercise_27_12_H

#define BUFFERSIZE 201

enum ReturnTypeCommon { FAILURE = -1, SUCCESS };

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

typedef struct SRecord {
	int val;
	char* str;
} Record;

typedef struct STable {
	Record** rec;
	int sz;
	int maxsz;
} Table;

void PrintError(const char* message);
Record* Find(Table* table, const char* string);
bool Insert(Table* table, const char* string, int value);
bool Remove(Table* table, const char* string);
Record* CreateRecord(const char* string, int value);
void RemoveRecord(Record** record);
bool Initialize(Table* table, size_t size);
bool Extend(Table* table, size_t newSize);
bool Destroy(Table* table);
void PrintTable(Table* tab);

#endif
