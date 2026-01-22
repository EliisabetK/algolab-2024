#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
using namespace std;

typedef double ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct Stable{
  long long f,c,k,l,m;
};

// calculate if solution is feasable with certain extra flow
bool is_feasible_in_hours(double flowA, double flowB, vector<Stable> stables){
  const int h1 = 0, h2 = 1, h3 = 2;
   
  Program lp (CGAL::SMALLER, true, 0, true, 1); 
  for(int i = 0; i < stables.size(); i++){
    long f = stables[i].f, c = stables[i].c, k = stables[i].k, l = stables[i].l, m = stables[i].m;
    lp.set_a(h1, i, -(k+ flowA*flowA)); lp.set_a(h2, i, -(l + flowB*flowB)); lp.set_a(h3, i, -(m+ flowA*flowB)); 
    lp.set_b(i, c-f);
  }
  Solution s = CGAL::solve_linear_program(lp, ET());
  return !s.is_infeasible();
}

int main(){
  int T; cin >> T;
  while(T--){
    int n; cin >> n;
    vector<Stable> stables(n);
    for(int i = 0; i < n; i++){
      long long f,c,k,l,m; cin >> f >> c >> k >> l >> m;
      stables[i] = {f,c,k,l,m};
    }
    vector<double> prefixA(25, 0);
    vector<double> prefixB(25, 0);
    for(int i = 1; i < 25; i++){
      double flow; cin >> flow;
      prefixA[i] = prefixA[i-1] + flow;
    }
    for(int i = 1; i < 25; i++){
      double flow; cin >> flow;
      prefixB[i] = prefixB[i-1] + flow;
    }
    if(!is_feasible_in_hours(prefixA[24], prefixB[24], stables)) {cout << "Impossible!" << endl; continue;}
    // binary search on the hours
    int low = 0, high = 48, best = 48;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      // check every combination that sums up to mid
      bool possible = false;
      for(int i = max(0, mid - 24); i <= min(24, mid); i++){ // hours spent on river A, cant spend more than 24 hours, cant spend less than 0
        int j = min(24, mid - i); // time spent river B
        if(is_feasible_in_hours(prefixA[i], prefixB[j], stables)){
          possible = true;
          break;
        }
      }
      if (possible) {
        best = mid;
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }
    cout << best << endl;
  }
}