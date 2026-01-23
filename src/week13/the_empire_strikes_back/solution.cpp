#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;

using namespace std;

struct Asteroid{
  P p;
  long d;
};

int main(){
  int T; cin >> T;
  while(T--){
    int a, s, b; cin >> a >> s >> b;
    ET e; cin >> e;
    vector<Asteroid> asses(a);
    for(int i = 0; i < a; i++){
      long long x,y,d; cin >> x >> y >> d;
      asses[i] = {P(x,y), d};
    }
    vector<P> shots(s);
    for(int i = 0; i < s; i++){
      long long x,y; cin >> x >> y;
      shots[i] = P(x,y);
    }
    vector<P> bountys(b);
    for(int i = 0; i < b; i++){
      long long x,y; cin >> x >> y;
      bountys[i] = P(x,y);
    }
    Triangulation t;
    t.insert(bountys.begin(), bountys.end());
    
    Program lp (CGAL::SMALLER, true, 0, false, 0); 
    
    for(int i = 0; i < s; i++){
      ET max_radius = 1000000000000;
      if(b > 0){
        auto nearest = t.nearest_vertex(shots[i])->point();
        max_radius = CGAL::squared_distance(nearest, shots[i]);
      }
      for(int j = 0; j < a; j++){
        ET distance = CGAL::squared_distance(asses[j].p, shots[i]);
        if(distance <= max_radius){
          ET coeff = ((ET) 1) / (max((ET) 1, distance));
          lp.set_a(i, j, -coeff); // set coefficent to each energy
        }
      }
      for(int j = 0; j < a; j++){
        lp.set_b(j, -asses[j].d); // greater than density (flipped sign since we want greater or equal)
      }
      lp.set_c(i, 1); // objective, minimize energy
    }
    
    Solution sol = CGAL::solve_linear_program(lp, ET());
    if(sol.is_optimal() && sol.objective_value() <= e) cout << "y" << endl;
    else cout << "n" << endl;
  }
}