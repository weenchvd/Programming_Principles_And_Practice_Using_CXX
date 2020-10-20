/* Exercise 21.5 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

template<class InputIterator, class T>
unsigned long long int Count(InputIterator first, InputIterator last, const T& value);
template<class InputIterator, class T>
InputIterator Find(InputIterator first, InputIterator last, const T& value);
