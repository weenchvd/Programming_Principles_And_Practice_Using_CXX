/* Exercise 27.1 */

#ifndef C27_Exercise_27_1_H
#define C27_Exercise_27_1_H

enum ReturnTypeCommon { FAILURE = -1, SUCCESS };

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

size_t StrLen(const char* s);
int StrCmp(const char* str1, const char* str2);
char* StrCpy(char* destination, const char* source);

#endif