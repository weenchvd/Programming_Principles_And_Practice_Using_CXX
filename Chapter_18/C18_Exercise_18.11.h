/* Exercise 18.11 */

using namespace std;

namespace OrderedList {
	class SkipList;

	class DataNode {
	public:
		DataNode(int number, string string) : num{ number }, s{ string } {}
		int GetNumber() const { return num; }
		const string& GetString() const { return s; }

		void SetString(const string& string) { s = string; }
	protected:
		friend SkipList;
		~DataNode() {}
	private:
		int num;
		string s;
	};

	struct LineNode {
		LineNode() : right{ nullptr }, bottom{ nullptr }, data{ nullptr } {}
		LineNode(DataNode* data) : right{ nullptr }, bottom{ nullptr }, data{ data } {}
		LineNode* right;
		LineNode* bottom;
		DataNode* data;
	};

	class SkipList {
	public:
		SkipList() : el{ nullptr }, nl{ nullptr }, sz{ 0 } {}
		void Print() const;

		void Add(int number, string string);
		DataNode* Find(int number);
		void Remove(int number);
		~SkipList() { DeleteExpressLine(); DeleteNormalLineAndData(); }
	private:
		void Print(LineNode* node, int shift) const;
		void Print(DataNode* node, int shift) const;
		string PrintAddress(void* p) const;
		LineNode* FindPreviousInNormalLine(int i);
		void RebuildExpressLine();
		void DeleteExpressLine();
		void DeleteNormalLineAndData();

		LineNode* el;												// express line
		LineNode* nl;												// normal line
		int sz;														// size
	};
}

void ClearInput(istream& is);
