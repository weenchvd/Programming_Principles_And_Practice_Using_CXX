/* Exercise 26.11 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

double row_sum(const Numeric_lib::Matrix<double, 2>& m, int n);
double row_accum(const Numeric_lib::Matrix<double, 2>& m, int n);
