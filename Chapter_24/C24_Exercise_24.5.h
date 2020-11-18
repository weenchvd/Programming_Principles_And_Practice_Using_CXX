/* Exercise 24.5 */

using namespace std;

const char* sp_2 = "  ";
const char* sp_4 = "    ";
const char* sp_6 = "      ";
const char* sp_8 = "        ";
const char* vsp_2 = "\n\n";
const char* vsp_3 = "\n\n\n";
const char* vsp_4 = "\n\n\n\n";

void ClearInput(istream& is);

using Matrix = Numeric_lib::Matrix<double, 2>;
using Vector = Numeric_lib::Matrix<double, 1>;

template<class T> string to_string(const T& t)
{
    ostringstream os;
    os << t;
    return os.str();
}

// An exception of this type is thrown when elimination fails.
struct Elim_failure : std::domain_error {
    Elim_failure(std::string s) : std::domain_error(s) { }
};

// An exception of this type is thrown when back substitution fails.
struct Back_subst_failure : std::domain_error {
    Back_subst_failure(std::string s) : std::domain_error(s) { }
};

Vector classical_gaussian_elimination(Matrix A, Vector b);
void classical_elimination(Matrix& A, Vector& b);
Vector back_substitution(const Matrix& A, const Vector& b);
Vector pivotal_elimination(Matrix A, Vector b);
void elim_with_partial_pivot(Matrix& A, Vector& b);
