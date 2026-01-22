#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

typedef long IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

int floor_to_int(const auto &x){
  int a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  while(true){
    int n,m; cin >> n >> m;
    if(n == 0 && m == 0) break;
    
    Program lp (CGAL::SMALLER, true, 0, false, 0); 
    
    for(int i = 0; i < n; i++) {
      long min,max; cin >> min >> max;
      lp.set_b(i, -min); // at least min amount of nutrient n_i
      lp.set_b(i+n, max); // at most max amount of nutrient n
    }
    // every row is one nutrient
    // minimize price
    for(int j = 0; j < m; j++){
      long cost; cin >> cost;
      for(int i = 0; i < n; i++){
        long amount; cin >> amount;
        lp.set_a(j, i, -amount);
        lp.set_a(j, i+n,  amount);
      }
       lp.set_c(j, cost);
    }
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()) cout << "No such diet." << endl;
    else if(s.is_unbounded()) cout << "No such diet." << endl;
    else { 
      auto val = s.objective_value();
      cout << floor_to_int(val) << endl;
    }
  }
  return 0;
}
