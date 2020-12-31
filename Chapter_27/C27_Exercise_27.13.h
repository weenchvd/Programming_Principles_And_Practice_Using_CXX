/* Exercise 27.13 */

#ifndef C27_Exercise_27_13_H
#define C27_Exercise_27_13_H

#define EXTENDMULTIPLIER 2

enum ReturnTypeCommon { FAILURE = -1, SUCCESS };

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

typedef struct StructString {
	char* str;
	int sz;
	int maxsz;
} String;

void PrintError(const char* message);
bool Initialize(String* string, size_t size);
bool Extend(String* string);
bool Destroy(String* string);
bool GetString(FILE* stream, String* string);

#endif