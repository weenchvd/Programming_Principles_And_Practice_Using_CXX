/* Exercise 19.13 */

#include<iostream>
#include<istream>
#include<string>
#include<vector>
#include<iomanip>
#include<sstream>
#include"C19_Exercise_19.13.h"

using namespace std;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }

Tracer<int> globVar1;
Tracer<int> globVar2{ 999 };

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		TRACER
	};
	const string actionList = "\tList of actions:\n"
	"  (1) Tracer()\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case TRACER: {
			cout << vsp_3;
			PrintCode("Tracer<int> locVar_1;");
			Tracer<int> locVar_1;
			PrintState("locVar_1", locVar_1);

			cout << vsp_3;
			PrintCode("Tracer<int> locVar_2{ 2 };");
			Tracer<int> locVar_2{ 2 };
			PrintState("locVar_2", locVar_2);

			cout << vsp_3;
			PrintCode("Tracer<Tracer<int>> locVar_3_1;");
			Tracer<Tracer<int>> locVar_3_1;
			PrintState("locVar_3_1", locVar_3_1);

			cout << vsp_3;
			PrintCode("Tracer<Tracer<int>> locVar_3_2{ Tracer<int>{8888} };");
			Tracer<Tracer<int>> locVar_3_2{ Tracer<int>{8888} };
			PrintState("locVar_3_2", locVar_3_2);

			cout << vsp_3;
			PrintCode("Tracer<Tracer<int>> locVar_3_3{ locVar_2 };");
			Tracer<Tracer<int>> locVar_3_3{ locVar_2 };
			PrintState("locVar_3_3", locVar_3_3);

			cout << vsp_3;
			PrintCode("Tracer<Tracer<Tracer<int>>> locVar_4{ Tracer<Tracer<int>>{ Tracer<int>{9999}} };");
			Tracer<Tracer<Tracer<int>>> locVar_4{ Tracer<Tracer<int>>{ Tracer<int>{9999}} };
			PrintState("locVar_4", locVar_4);
			
			//cout << vsp_3;
			//Tracer2 locVarTr2;

			cout << vsp_3;
			PrintCode("TracerAsMember tam{ Tracer<string>{\"YYYY\"}, Tracer<string>{\"XXXX\"} };");
			//TracerAsMember tam{ {"YYYY"}, {"XXXX"} }; // error because "explicit"
			TracerAsMember tam{ Tracer<string>{"YYYY"}, Tracer<string>{"XXXX"} };
			PrintState("tam.tr1", tam.tr1);
			PrintState("tam.tr2", tam.tr2);

			cout << vsp_3;
			PrintCode("vector<Tracer<int>> vtr{ Tracer<int>{-4}, Tracer<int>{-5}, Tracer<int>{-6}, Tracer<int>{-7}, Tracer<int>{-8} };");
			vector<Tracer<int>> vtr{ Tracer<int>{-4}, Tracer<int>{-5}, Tracer<int>{-6}, Tracer<int>{-7}, Tracer<int>{-8} };
			PrintState("vtr[0]", vtr[0]);
			PrintState("vtr[1]", vtr[1]);
			PrintState("vtr[2]", vtr[2]);
			PrintState("vtr[3]", vtr[3]);
			PrintState("vtr[4]", vtr[4]);

			cout << vsp_3;
			PrintCode("Tracer<int> locVar_11 = ReturnArgument(locVar_2);");
			PrintStartScope();
			Tracer<int> locVar_11 = ReturnArgument(locVar_2);
			PrintEndScope();
			PrintState("locVar_11", locVar_11);
			PrintState("locVar_2", locVar_2);

			cout << vsp_3;
			PrintCode("Tracer<int> locVar_12 = ReturnArgumentRef(locVar_2);");
			PrintStartScope();
			Tracer<int> locVar_12 = ReturnArgumentRef(locVar_2);
			PrintEndScope();
			PrintState("locVar_12", locVar_12);
			PrintState("locVar_2", locVar_2);

			cout << vsp_3;
			PrintCode("Tracer<int> locVar_13 = ReturnRefToArgumentRef(locVar_2);");
			PrintStartScope();
			Tracer<int> locVar_13 = ReturnRefToArgumentRef(locVar_2);
			PrintEndScope();
			PrintState("locVar_13", locVar_13);
			PrintState("locVar_2", locVar_2);
			
			cout << vsp_3;
			PrintCode("locVar_2.val = 2;");
			locVar_2.val = 2;
			PrintState("locVar_2", locVar_2);

			cout << vsp_3;
			PrintCode("Tracer<int> locVar_21 = ReturnLocalVariable(locVar_2);");
			PrintStartScope();
			Tracer<int> locVar_21 = ReturnLocalVariable(locVar_2);
			PrintEndScope();
			PrintState("locVar_21", locVar_21);
			PrintState("locVar_2", locVar_2);

			cout << vsp_3;
			PrintCode("Tracer<int> locVar_22 = ReturnLocalVariable2(locVar_2);");
			PrintStartScope();
			Tracer<int> locVar_22 = ReturnLocalVariable2(locVar_2);
			PrintEndScope();
			PrintState("locVar_22", locVar_22);
			PrintState("locVar_2", locVar_2);

			cout << vsp_3;
			PrintCode("Tracer<int>* pLocVar_31 = ReturnTracerOnHeap(33);");
			PrintStartScope();
			Tracer<int>* pLocVar_31 = ReturnTracerOnHeap(33);
			PrintEndScope();
			PrintState("(*pLocVar_31)", *pLocVar_31);
			PrintCode("delete pLocVar_31;");
			delete pLocVar_31;

			cout << vsp_3;
			PrintCode("Tracer<int>* pLocVar_32 = new Tracer<int>{ 44 };");
			Tracer<int>* pLocVar_32 = new Tracer<int>{ 44 };
			PrintState("(*pLocVar_32)", *pLocVar_32);
			PrintCode("delete pLocVar_32;");
			delete pLocVar_32;

			cout << vsp_3;
			PrintCode("Tracer<int>* pLocVar_33 = new Tracer<int>[3];");
			Tracer<int>* pLocVar_33 = new Tracer<int>[3];
			PrintState("pLocVar_33[0]", pLocVar_33[0]);
			PrintState("pLocVar_33[1]", pLocVar_33[1]);
			PrintState("pLocVar_33[2]", pLocVar_33[2]);
			PrintCode("delete[] pLocVar_33;");
			delete[] pLocVar_33;

			cout << vsp_3;
			cout << sp_2 << "End of 'case TRACER'" << endl;
			break;
		}
		case PRINTACTIONLIST:
			cout << actionList;
			break;
		case EXIT:
			cond = false;
			break;
		default:
			error("Error. Incorrect action number");
			break;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Error. Exception\n";
		return 1;
	}
	return 0;
}

template<class T> Tracer<T>::Tracer()
{
	State("Tracer()", T());
	val = T();
}

template<class T> Tracer<T>::Tracer(T value)
{
	ostringstream oss;
	oss << "Tracer(T{ " << value << " })";
	State(oss.str().c_str(), value);
	val = value;
}

template<class T> Tracer<T>::~Tracer()
{
	StateDtor("~Tracer()");
}

template<class T> Tracer<T>::Tracer(const Tracer<T>& tracer)
{
	ostringstream oss;
	oss << "Tracer(const Tracer<T>&{ " << tracer << " })";
	State(oss.str().c_str(), tracer.val);
	val = tracer.val;
}

template<class T> Tracer<T>& Tracer<T>::operator=(const Tracer<T>& tracer)
{
	ostringstream oss;
	oss << "Tracer<T>& operator=(const Tracer<T>&{ " << tracer << " })";
	State(oss.str().c_str(), tracer.val);
	val = tracer.val;
	return *this;
}

template<class T> Tracer<T>::Tracer(Tracer<T>&& tracer)
{
	ostringstream oss;
	oss << "Tracer(Tracer<T>&&{ " << tracer << " })";
	State(oss.str().c_str(), tracer.val);
	val = tracer.val;
}

template<class T> Tracer<T>& Tracer<T>::operator=(Tracer<T>&& tracer)
{
	ostringstream oss;
	oss << "Tracer<T>& operator=(Tracer<T>&&{ " << tracer << " })";
	State(oss.str().c_str(), tracer.val);
	val = tracer.val;
	return *this;
}

template<class T> ostream& operator<<(ostream& os, const Tracer<T>& tracer)
{
	os << &tracer << "->val{ " << tracer.val << " }";
	return os;
}

template<class T> void Tracer<T>::State(const char* message, const T& newValue)
{
	cout << sp_2 << sp_8 << sp_8 << this << "->" << message << ": old{ " << val << " }, new{ " << newValue << " }" << endl;
}

template<class T> void Tracer<T>::StateDtor(const char* message)
{
	cout << sp_2 << sp_8 << sp_8 << this << "->" << message << ": old{ " << val << " }" << endl;
}

template<class T> Tracer<T> ReturnArgument(Tracer<T> tracer)
{
	PrintFunctionCode("template<class T> Tracer<T> ReturnArgument(Tracer<T> tracer)");
	PrintState("tracer", tracer);
	PrintFunctionCode("tracer.val = tracer.val * tracer.val + 1;");
	tracer.val = tracer.val * tracer.val + 1;
	PrintState("tracer", tracer);
	PrintFunctionCode("return tracer;");
	return tracer;
}

template<class T> Tracer<T> ReturnArgumentRef(Tracer<T>& tracer)
{
	PrintFunctionCode("template<class T> Tracer<T> ReturnArgumentRef(Tracer<T>& tracer)");
	PrintState("tracer", tracer);
	PrintFunctionCode("tracer.val = tracer.val * tracer.val + 10;");
	tracer.val = tracer.val * tracer.val + 10;
	PrintState("tracer", tracer);
	PrintFunctionCode("return tracer;");
	return tracer;
}

template<class T> Tracer<T>& ReturnRefToArgumentRef(Tracer<T>& tracer)
{
	PrintFunctionCode("template<class T> Tracer<T>& ReturnRefToArgumentRef(Tracer<T>& tracer)");
	PrintState("tracer", tracer);
	PrintFunctionCode("tracer.val = tracer.val * tracer.val + 100;");
	tracer.val = tracer.val * tracer.val + 100;
	PrintState("tracer", tracer);
	PrintFunctionCode("return tracer;");
	return tracer;
}

template<class T> Tracer<T> ReturnLocalVariable(Tracer<T> tracer)
{
	PrintFunctionCode("template<class T> Tracer<T> ReturnLocalVariable(Tracer<T> tracer)");
	PrintState("tracer", tracer);
	PrintFunctionCode("Tracer<T> tr{ tracer };");
	Tracer<T> tr{ tracer };
	PrintState("tr", tr);
	PrintFunctionCode("tr.val = tr.val * tr.val - 1;");
	tr.val = tr.val * tr.val - 1;
	PrintState("tr", tr);
	PrintFunctionCode("return tr;");
	return tr;
}

template<class T> Tracer<T> ReturnLocalVariable2(Tracer<T>& tracer)
{
	PrintFunctionCode("template<class T> Tracer<T> ReturnLocalVariable2(Tracer<T>& tracer)");
	PrintState("tracer", tracer);
	PrintFunctionCode("Tracer<T> tr;");
	Tracer<T> tr;
	PrintState("tr", tr);
	PrintFunctionCode("tr.val = tracer.val * tracer.val - 10;");
	tr.val = tracer.val * tracer.val - 10;
	PrintState("tr", tr);
	PrintFunctionCode("return tr;");
	return tr;
}

Tracer<int>* ReturnTracerOnHeap(int value)
{
	PrintFunctionCode("Tracer<int>* ReturnTracerOnHeap(int value)");
	PrintFunctionCode("Tracer<int> tr{ 66 };");
	Tracer<int> tr{ value };
	PrintState("tr", tr);
	PrintFunctionCode("tr.val = tr.val * 2;");
	tr.val = tr.val * 2;
	PrintState("tr", tr);
	PrintFunctionCode("return new Tracer<int>{ tr };");
	return new Tracer<int>{ tr };
}

void PrintCode(const char* message)
{
	cout << sp_2 << message << endl;
}

void PrintFunctionCode(const char* message)
{
	cout << sp_2 << sp_4 << message << endl;
}

void PrintStartScope()
{
	cout << sp_2 << "{" << endl;
}

void PrintEndScope()
{
	cout << sp_2 << "}" << endl;
}

template<class T> void PrintState(const char* message, const Tracer<T>& t)
{
	cout << sp_2 << sp_8 << sp_8 << sp_2 << "&" << message << "{ " << &t << " }, "
		<< message << ".val{ " << t.val << " }" << endl;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
