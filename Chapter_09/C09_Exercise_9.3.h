/* Exercise 9.3 */


class Name_pair {
public:
	Name_pair() : name(0), age(0) { }
	void read_names();
	void read_ages();
	void sort();
	bool isSizeEqual();
	friend std::ostream& operator<<(std::ostream& os, const Name_pair& np);
	friend bool operator==(const Name_pair& np1, const Name_pair& np2);
	friend bool operator!=(const Name_pair& np1, const Name_pair& np2);
private:
	std::vector<std::string> name;
	std::vector<double> age;
};
