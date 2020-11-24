/* Exercise 24.9 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

template<class R, class T> R Triple(const T& t) { return static_cast<R>(t * 3); }
template<class R, class T> R TripleArg(const T& t, const R& argument) { return static_cast<R>(t * 3) + argument; }
template<class R, class T> R Multiply(const T& t, const T& multiplier) { return static_cast<R>(t * multiplier); }

namespace MyApply {
	template<class F, class T> auto apply(F f, Numeric_lib::Matrix<T,2> x)
	{
		using ReturnType = result_of<F(T)>::type;
		Numeric_lib::Matrix<ReturnType, 2> result(x.dim1(), x.dim2());
		T* xData = x.data();
		ReturnType* resultData = result.data();
		for (Numeric_lib::Index i = 0; i < x.size(); ++i) {
			resultData[i] = f(xData[i]);
		}
		return result;
	}

	template<class F, class T, class Arg> auto apply(F f, Numeric_lib::Matrix<T,2> x, Arg a)
	{
		using ReturnType = result_of<F(T, Arg)>::type;
		Numeric_lib::Matrix<ReturnType, 2> result(x.dim1(), x.dim2());
		T* xData = x.data();
		ReturnType* resultData = result.data();
		for (Numeric_lib::Index i = 0; i < x.size(); ++i) {
			resultData[i] = f(xData[i], a);
		}
		return result;
	}
}
