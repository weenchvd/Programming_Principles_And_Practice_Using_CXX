/* Exercise 14.15 */

using namespace std;

class Iterator {
public:
	virtual double* next() = 0;
};

class Vector_iterator : public Iterator {
public:
	Vector_iterator(vector<double>& vector)
		: i{ 0 }, v{ vector } { }
	double* next() { return (i < v.size()) ? &v[i++] : nullptr; }
private:
	int i;
	vector<double>& v;
};

class List_iterator : public Iterator {
public:
	List_iterator(list<double>& list)
		: it{ list.begin() }, l {list} { }
	double* next() { return (it != l.end()) ? &(*(it++)) : nullptr; }
private:
	list<double>::iterator it;
	list<double>& l;
};

void print(Iterator& it);
void ClearInput(istream& is);
