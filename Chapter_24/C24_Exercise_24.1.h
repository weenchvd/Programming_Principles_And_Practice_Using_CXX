﻿/* Exercise 24.1 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

void triple1(int& elem) { elem *= 3; }
int triple2(const int& elem) { return elem * 3; }
int triple(int& elem) { return elem *= 3; }
