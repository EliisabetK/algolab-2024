#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
using namespace std;

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

bool get_d_sign(long x, long y, long a, long b, long c){ // true is positive
  double d = (a*x + b*y + c) / sqrt(a*a + b*b);
  return d >= 0;
}

double floor_to_double(auto& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

int main(){
  int T; cin >> T;
  while(T--){
    long x,y,n; cin >> x >> y >> n;
    Program lp (CGAL::SMALLER, false, 0, false, 0); 
    const int X = 0; 
    const int Y = 1;
    const int D = 2;
    for(int i = 0; i < n; i++){
      long a,b,c,v; cin >> a >> b >> c >> v;
      bool positive_sign = get_d_sign(x,y,a,b,c);
      long d_coeff = sqrt(a*a + b*b) * v;
      if(positive_sign){
        lp.set_a(X, i,  -a); lp.set_a(Y, i, -b); lp.set_a(D, i, d_coeff); lp.set_b(i, c);
      }
      else {
        lp.set_a(X, i, a); lp.set_a(Y, i, b); lp.set_a(D, i, d_coeff); lp.set_b(i, -c);
      }
      lp.set_l(D, true, 0); // D has to be positive
      lp.set_c(D, -1); // obejctive is minimize -D
    }
    Solution s = CGAL::solve_linear_program(lp, ET());
    double res = CGAL::to_double(-s.objective_value());
    cout << (long long)floor(res) << endl;
  }
}
