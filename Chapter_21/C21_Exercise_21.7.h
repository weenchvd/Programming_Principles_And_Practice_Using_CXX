/* Exercise 21.7 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

template<class T> typename vector<T>::iterator BinarySearch(vector<T>& v, const T& val);
template<class T> typename list<T>::iterator BinarySearch(list<T>& l, const T& val);

template<class T> void SearchAndPrint(vector<T>& v, const string& name, const string& type, const T& val);
template<class T> void SearchAndPrint(list<T>& l, const string& name, const string& type, const T& val);
