/* Exercise 20.4 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

double* get_from_jack(int* count);
vector<double>* get_from_jill();
template<class Iterator > Iterator high(Iterator first, Iterator last);
void fct();
