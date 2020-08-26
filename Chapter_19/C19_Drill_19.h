/* Drill 19 */

using namespace std;

template<typename T> struct S {
	S(T value) : val{ value } {}
	const T* Get() const;
	T* Get();
	void Set(T value);
	T& operator=(const T& value);
private:
	T val;
};

template<typename T> istream& operator>>(istream& is, vector<T>& v);
template<typename T> void read_val(T& v);

void ClearInput(istream& is);
