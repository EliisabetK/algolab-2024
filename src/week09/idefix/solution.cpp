///4
#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

using namespace std;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

typedef std::size_t Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Delaunay;

typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

int main(){
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  std::ios_base::sync_with_stdio(false);
  int T; cin >> T;
  while(T--){
    int n,m,k; long s;
    cin >> n >> m >> s >> k;
    typedef pair<K::Point_2,Index> IPoint;
    vector<IPoint> trees;
    trees.reserve(n);
    for (int i = 0; i < n; ++i) {
      long x, y;
      cin >> x >> y;
      trees.emplace_back(K::Point_2(x, y), i);
    }
    Delaunay t;
    t.insert(trees.begin(), trees.end());
    
    EdgeV edges_bones;
    vector<int> sizes(n,0);
    
    for(int i = 0; i < m; i++){ // finds for each bone what tree it belongs to
      long x,y;
      cin >> x >> y;
      P bone = P(x,y);
      auto v1 =  t.nearest_vertex(bone);
      K::FT distance = 4*CGAL::squared_distance(bone, v1->point());
      if(distance <= s) sizes[v1->info()]++;
      edges_bones.push_back({v1->info(), n+i, distance});
    }
    
    EdgeV edges;
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
      Index i1 = e->first->vertex((e->second+1)%3)->info();
      Index i2 = e->first->vertex((e->second+2)%3)->info();
      // ensure smaller index comes first
      if (i1 > i2) std::swap(i1, i2);
      edges.emplace_back(i1, i2, t.segment(e).squared_length());
    }
    std::sort(edges.begin(), edges.end(),
        [](const Edge& e1, const Edge& e2) -> bool {
          return std::get<2>(e1) < std::get<2>(e2);
              });
    
    boost::disjoint_sets_with_storage<> uf(n); // link edges, like what trees are close enough together
    int n_components = n;
    for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
      Index c1 = uf.find_set(std::get<0>(*e));
      Index c2 = uf.find_set(std::get<1>(*e));
      K::FT distance = get<2>(*e);
      if (c1 != c2 && distance <= s) {
        int s1 = sizes[c1], s2 = sizes[c2];
        uf.link(c1, c2);
        Index c3 = uf.find_set(c1);
        sizes[c3] = s1+s2;
        if (--n_components == 1) break;
      }
      if(distance > s) break;
    }
    long a = *std::max_element(sizes.begin(), sizes.end()); // answer to part 1
    
    vector<long> sizes_2(n+m,0);
    for(int i = 0; i < m; i++){
      edges.push_back(edges_bones[i]);
      sizes_2[n+i] = 1;
    }
    std::sort(edges.begin(), edges.end(),
        [](const Edge& e1, const Edge& e2) -> bool {
          return std::get<2>(e1) < std::get<2>(e2);
              });
              
    boost::disjoint_sets_with_storage<> uf2(n+m); // link bones and edges
    n_components = n+m;
    K::FT q = 4*s;
    for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
      Index c1 = uf2.find_set(std::get<0>(*e));
      Index c2 = uf2.find_set(std::get<1>(*e));
      if (c1 != c2) {
        long s1 = sizes_2[c1], s2 = sizes_2[c2];
        uf2.link(c1, c2);
        Index c3 = uf2.find_set(c1);
        sizes_2[c3] = s1+s2;
        if(sizes_2[c3] >= k) {
          q = get<2>(*e);
          break;
        }
      }
    }
    cout << a << " " << q << endl;
  }
}