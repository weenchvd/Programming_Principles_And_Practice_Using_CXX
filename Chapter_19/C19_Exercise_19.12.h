/* Exercise 19.12 */

using namespace std;

const char* space_c2 = "  ";
const char* space_c4 = "    ";
const char* space_c6 = "      ";
const char* space_c8 = "        ";

template<class T> class FileHandle {
public:
	FileHandle(const string& fileName)
	{
		fs.open(fileName);
		cout << space_c8 << space_c2 << "FileHandle(const string& \"" << fileName << "\")\n";
	}
	~FileHandle() { cout << space_c8 << space_c2 << "~FileHandle()\n"; }
	T& Get() { return fs; }

	operator bool() const { return fs; }
	bool operator!() const { return !fs; }
private:
	T fs;
};

void ClearInput(istream& is);
