/* Exercise 19.11 */

#define SHOWDEBUGINFO 1

using namespace std;

const char* space_c2 = "  ";
const char* space_c4 = "    ";
const char* space_c6 = "      ";
const char* space_c8 = "        ";

template<class T> class CountedPtr {
public:
	explicit CountedPtr();
	explicit CountedPtr(T val);
	~CountedPtr();
	CountedPtr(const CountedPtr<T>& p);
	CountedPtr<T>& operator=(const CountedPtr<T>& p);
	CountedPtr(CountedPtr<T>&& p);
	CountedPtr<T>& operator=(CountedPtr<T>&& p);

	T& operator*() { return *cp; }
	T* operator->() { return cp; }
private:
	T* cp;
	int* ctr;

	void ReleaseMemory();
};

template<class T> CountedPtr<T> Create(T val);
void ClearInput(istream& is);
