﻿/* Exercise 20.11 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

template<class T> ostream& operator<<(ostream& os, const vector<T>& v);
vector<double>* Copy(list<int>& listInt);
