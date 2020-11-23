/* Exercise 24.12 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

Numeric_lib::Matrix<double> operator*(Numeric_lib::Matrix<double, 2>& A, Numeric_lib::Matrix<double>& B);
Numeric_lib::Matrix<double, 1> operator+(Numeric_lib::Matrix<double, 1>& A, Numeric_lib::Matrix<double, 1>& B);
Numeric_lib::Matrix<double, 2> operator+(Numeric_lib::Matrix<double, 2>& A, Numeric_lib::Matrix<double, 2>& B);
