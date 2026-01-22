#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h> // Include Gmpz

using namespace std;

using ET = CGAL::Gmpz; 
using QT = CGAL::Quotient<ET>; 
using Program = CGAL::Quadratic_program<ET>;
using Solution = CGAL::Quadratic_program_solution<ET>;

static long floor_to_long_qt(const QT& x) {
  double val = CGAL::to_double(x);
  if (val >= numeric_limits<long>::max()) return numeric_limits<long>::max();
  if (val <= numeric_limits<long>::min()) return numeric_limits<long>::min();
  
  long a = (long)floor(val);
  while (QT(ET(a)) > x) --a;
  while (QT(ET(a + 1)) <= x) ++a;
  return a;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    long xs, ys;
    int n;
    cin >> xs >> ys >> n;

    // variables: x=0, y=1, t=2
    // CGAL::SMALLER means <= constraint by default
    Program lp(CGAL::SMALLER, false, 0, false, 0);
    lp.set_l(2, true, 0); // t >= 0

    for (int i = 0; i < n; i++) {
      long a, b, c, v;
      cin >> a >> b >> c >> v;

      ET val = ET(a) * ET(xs) + ET(b) * ET(ys) + ET(c);
      int s = (val > 0) ? 1 : -1; 
      
      // If val is 0 (point on line), sign doesn't strictly matter for inequality direction 
      // relative to distance, but we must be consistent. 
      // Usually, 's' determines the "inside" of the half-plane.

      long long sq = (long long)a * a + (long long)b * b;
      long L = lround(sqrt(sq));
      long D = L * v; 

      // Constraint: D*t - s*a*x - s*b*y <= s*c
      lp.set_a(0, i, ET(-s * a));
      lp.set_a(1, i, ET(-s * b));
      lp.set_a(2, i, ET(D));
      lp.set_b(i, ET(s * c));
    }

    // maximize t <=> minimize -t
    lp.set_c(2, ET(-1));

    Solution sol = CGAL::solve_linear_program(lp, ET());
    QT tmax = -sol.objective_value();
    cout << floor_to_long_qt(tmax) << "\n";
  }
  return 0;
}