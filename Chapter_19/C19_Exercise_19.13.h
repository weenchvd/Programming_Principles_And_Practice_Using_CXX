/* Exercise 19.13 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

struct Tracer1 {
	int i;
	int x{ -1 };
	
	explicit Tracer1() : i{ 0 } {}
	explicit Tracer1(int value) : i{ value } {}
};

struct Tracer2 {
	Tracer1 tr1;
	int y{ -2 };
	
	explicit Tracer2() : tr1{ Tracer1{} } {}
	explicit Tracer2(Tracer1 value) : tr1{ value } {}
};

template<class T> class Tracer {
public:
	int a{ -1 };
	T val;
	//int b{ -2 };

	explicit Tracer();
	explicit Tracer(T value);
	~Tracer();
	Tracer(const Tracer<T>& tracer);
	Tracer<T>& operator=(const Tracer<T>& tracer);
	Tracer(Tracer<T>&& tracer);
	Tracer<T>& operator=(Tracer<T>&& tracer);

	void State(const char* message, const T& newValue);
	void StateDtor(const char* message);
};

struct TracerAsMember {
	Tracer<string> tr1;
	Tracer<string> tr2;
};

template<class T> ostream& operator<<(ostream& os, const Tracer<T>& tracer);
template<class T> Tracer<T> ReturnArgument(Tracer<T> tracer);
template<class T> Tracer<T> ReturnArgumentRef(Tracer<T>& tracer);
template<class T> Tracer<T>& ReturnRefToArgumentRef(Tracer<T>& tracer);
template<class T> Tracer<T> ReturnLocalVariable(Tracer<T> tracer);
template<class T> Tracer<T> ReturnLocalVariable2(Tracer<T>& tracer);
Tracer<int>* ReturnTracerOnHeap(int value);
void PrintCode(const char* message);
void PrintFunctionCode(const char* message);
void PrintStartScope();
void PrintEndScope();
template<class T> void PrintState(const char* message, const Tracer<T>& t);
void ClearInput(istream& is);
