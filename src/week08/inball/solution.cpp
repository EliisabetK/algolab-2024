#include <iostream>
#include <vector>
#include <cmath>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

double floor_to_double(const auto& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while (true) {
    int n, d;
    cin >> n;
    if (!cin || n == 0) break;
    cin >> d;
    Program lp (CGAL::SMALLER, false, 0, false, 0); // we want to maximise the radius
    for(int i = 0; i < n; i++){ // n equations
      int norm2 = 0;
      for(int j = 0; j < d; j++){ // j + 1 variables in the equation
        int a; cin >> a;
        norm2 += a*a;
        lp.set_a(j, i, -a); // -a since we want to maximize so everzthing is multiplied by -1
      }
      lp.set_a(d, i, sqrt(norm2)); // radius multiplier
      int b; cin >> b;
      lp.set_b(i, b);  
    }
    lp.set_l(d, true, 0); // sets lower bound for r to 0
    lp.set_c(d, -1); // minimize r
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()) cout << "none" << endl;
    else if(s.is_unbounded()) cout << "inf" << endl;
    else{
      cout << floor_to_double(-s.objective_value()) << endl;
    }
  }
  return 0;
}

