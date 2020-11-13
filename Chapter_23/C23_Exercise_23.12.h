/* Exercise 23.12 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

void ReformatDateToISO(ostream& os, const string& s);

struct bad_from_string : std::bad_cast {						// class for reporting string cast errors
	const char* what() const override
	{
		return "bad cast from string";
	}
};

template<typename T> T from_string(const string& s)
{
	istringstream is{ s };
	T t;
	if (!(is >> t)) throw bad_from_string{};
	return t;
}

struct PatternGroup {
	int y;
	int m;
	int d;
	PatternGroup() : y{ 0 }, m{ 0 }, d{ 0 } {}
	PatternGroup(int year, int month, int day) : y{ year }, m{ month }, d{ day } {}
};
