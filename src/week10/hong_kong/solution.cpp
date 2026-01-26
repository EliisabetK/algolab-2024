///4

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cmath> 

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Finite_faces_iterator Face_iterator;

K::FT INF= 2e100;

int main() {
  int T; cin >> T;
  while(T--){
    int n,m; long r;
    cin >> n >> m >> r;
    vector<P> trees(n);

    for(int i = 0; i < n; i++){
      long x,y; cin >> x >> y;
      trees[i] = P(x, y);
    }

    Triangulation t;
    t.insert(trees.begin(), trees.end());
    priority_queue<pair<K::FT, Triangulation::Face_handle>> pq;
    
    for (auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f){
      if(t.is_infinite(f)){
        f->info() = INF;
      }
      else{
        auto p1 = f->vertex(0)->point();
        auto p2 = f->vertex(1)->point();
        auto p3 = f->vertex(2)->point();
        auto circ = CGAL::circumcenter(p1,p2,p3);
        K::FT dis = CGAL::squared_distance(circ, p1);
        f->info() = dis;
      }
      pq.push({f->info(), f});
    }
    
    while(!pq.empty()){
      K::FT width = pq.top().first;
      auto handle = pq.top().second;
      pq.pop();
      for(int i = 0; i < 3; i++){
        auto neighbor = handle->neighbor(i);
        auto v1 = handle->vertex((i+1)%3);
        auto v2 = handle->vertex((i+2)%3);
        K::FT new_width;
        if(t.is_infinite(v1) || t.is_infinite(v2)) new_width = INF;
        else new_width = CGAL::squared_distance(v1->point(), v2->point());
        new_width = min(new_width, width);
        if(new_width > neighbor->info()){
          neighbor->info() = new_width;
          pq.push({new_width, neighbor});
        }
      }
    }
    
    for(int i = 0; i < m; i++){
      long x,y,s;
      cin >> x >> y >> s;
      P balloon = P(x, y);
      K::FT min_inflate = K::FT(s + r) * K::FT(s + r);
      P nearest = t.nearest_vertex(balloon)->point();
      if(CGAL::squared_distance(balloon, nearest) <  min_inflate) cout << "n";
      else {
        auto start = t.locate(balloon);
        if(start->info() >= K::FT(4) * min_inflate) cout << "y";
        else cout << "n";
      }
    }
    cout << endl;
  }
}