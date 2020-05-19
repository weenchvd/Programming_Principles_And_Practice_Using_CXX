/* Exercise 9.2 */


class Name_pair {
public:
	Name_pair() : name(0), age(0) { }
	void read_names();
	void read_ages();
	void print();
	void sort();
private:
	std::vector<std::string> name;
	std::vector<double> age;
};
