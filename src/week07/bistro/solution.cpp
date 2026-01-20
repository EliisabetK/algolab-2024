///2

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;
#include <bits/stdc++.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

int main() {
  while(true){
    int n;
    cin >> n;
    if(n == 0) break;
    vector<K::Point_2> restaurants;
    restaurants.reserve(n);
    for (int i = 0; i < n; ++i) {
      long x, y;
      cin >> x >> y;
      restaurants.push_back(K::Point_2(x, y));
    }
    // construct triangulation
    Triangulation t;
    t.insert(restaurants.begin(), restaurants.end());
    
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
      long x, y;
      cin >> x >> y;
      auto loc = K::Point_2(x, y);
      auto nearest = t.nearest_vertex(loc)->point();
      cout << (long) CGAL::squared_distance(loc, nearest) << endl;
    }
  }
}
