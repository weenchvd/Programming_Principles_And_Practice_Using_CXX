/* Exercise 27.14 */

#ifndef C27_Exercise_27_14_H
#define C27_Exercise_27_14_H

enum ReturnTypeCommon { FAILURE = -1, SUCCESS };

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

typedef struct StructValue {
	int largest;
	int smallest;
	double median;
	double mean;
} Value;

void PrintError(const char* message);
Value* LargestSmallestMedianMean(int* arr, size_t size);
int CompareInt(const void* a, const void* b);

#endif