///1
#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;

double ceil_to_double(const K::FT& x) {
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a - 1 >= x) a -= 1;
  return a;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n && n != 0) {
    long long l,b,r,t; cin >> l >> b >> r >> t;
    vector<pair<P, int>> bacteria(n);
    vector<double> death_distances(n);
    for(int i = 0; i < n; i++){
      long long x,y; cin >> x >> y;
      bacteria[i] = {P(x,y), i};
      death_distances[i] = pow(min(min(y-b, t-y),min(x-l, r-x)),2);
    }
    
    Triangulation T;
    T.insert(bacteria.begin(), bacteria.end());
    
    for (auto e = T.finite_edges_begin(); e != T.finite_edges_end(); ++e) {
      auto u = e->first->vertex((e->second+1)%3);
      auto v = e->first->vertex((e->second+2)%3);
      int i1 = e->first->vertex((e->second+1)%3)->info();
      int i2 = e->first->vertex((e->second+2)%3)->info();
      auto v1 = u->point();
      auto v2 = v->point();
      double d = CGAL::squared_distance(v1,v2) / 4.0; // max radius before touching another
      death_distances[i1] = min(death_distances[i1], d);
      death_distances[i2] = min(death_distances[i2], d);
    }
    
    vector<long long> death_times(n);
    for(int i = 0; i < n; i++){
      death_times[i] = (long long) ceil_to_double(sqrt(max(0.0,sqrt(death_distances[i])-0.5)));
    }
    
    sort(death_times.begin(), death_times.end());
    cout << death_times[0] << " " << death_times[n/2] << " " << death_times[n-1] << endl;
  }
}