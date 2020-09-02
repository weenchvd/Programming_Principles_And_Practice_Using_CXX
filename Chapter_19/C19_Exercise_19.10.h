/* Exercise 19.10 */

using namespace std;

const char* space_c2 = "  ";
const char* space_c4 = "    ";
const char* space_c6 = "      ";
const char* space_c8 = "        ";

template<class T> class UniquePtr {
public:
	UniquePtr(T* val) : up{ val } { cout << space_c8 << "Ctor of UniquePtr\n"; }
	~UniquePtr() { delete up; cout << space_c8 << "Dtor of UniquePtr: 'delete up' done\n"; }
	T& operator*() { return *up; }
	T* operator->() { return up; }
	T* Release();

	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;
private:
	T* up;
};

int* CreateInt();
void ClearInput(istream& is);
