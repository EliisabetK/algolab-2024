#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef std::pair<K::Point_2,int> IPoint;

using namespace std;

int main(){
  int T; cin >> T;
  while(T--){
    int n; long long r;
    cin >> n >> r;
    vector<IPoint> planets(n);
    
    for (int i = 0; i < n; ++i) {
      long long x, y;
      cin >> x >> y;
      planets[i] = IPoint(K::Point_2(x, y),i);
    }
    
    int low = 2, high = n/2; // binary search over the number of planets
    while(low <= high){
      int mid = low + (high-low)/2;
      Delaunay t;
      t.insert(planets.begin() + mid, planets.end());

      boost::disjoint_sets_with_storage<> uf(n);
      vector<int> sizes(n, 1);
      
      for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        int i1 = e->first->vertex((e->second+1)%3)->info();
        int i2 = e->first->vertex((e->second+2)%3)->info();
        long d = t.segment(e).squared_length();
        int c1 = uf.find_set(i1);
        int c2 = uf.find_set(i2);
        if (c1 != c2 && d <= r*r) {
          int s1 = sizes[c1], s2 = sizes[c2];
          uf.link(c1, c2);
          int c3 = uf.find_set(i1);
          sizes[c3] = s1+s2;
        }
      }
      int best = *max_element(sizes.begin(), sizes.end());
      if(best >= mid) {
        low = mid+1;
      }
      else high = mid -1;
    }
    cout << low-1 << endl;
  }
}
