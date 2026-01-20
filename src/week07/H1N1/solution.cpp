///1
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<double, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 P;

long INF = 1000000000000000;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  while (cin >> n && n != 0) {
    vector<P> infected(n);
    for(int i = 0; i < n; i++){
      long x, y; cin>> x >> y;
      infected[i] = P(x,y); 
    }
    Triangulation t;
    t.insert(infected.begin(), infected.end());
    
    priority_queue<pair<double, Triangulation::Face_handle>> pq;
    
    for(auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f){
      if(t.is_infinite(f)){
        f->info() = INF;
        pq.push({INF, f});
      }
      else f->info() = -1;
    } 
    
    while(!(pq.empty())){
      auto top = pq.top();
      pq.pop();
      double val = top.first;
      auto f = top.second;
      if(val < f->info()) continue;
      
      for(int i = 0; i < 3; i++){
        auto neighbor = f->neighbor(i);
        if(neighbor->info() >= val) continue;
        P p1 = f->vertex((i + 1) % 3)->point();
        P p2 = f->vertex((i + 2) % 3)->point();
        double d = CGAL::squared_distance(p1,p2);
        double new_val = min(d, val);
        if(new_val > neighbor->info()){
          neighbor->info() = new_val;
          pq.push({new_val, neighbor});
        }
      }
    }
    
    int m; cin >> m;
    for(int i = 0; i < m; i++){
      long x,y; double d; cin >> x >> y >> d;
      P person = P(x,y);
      auto nearest = t.nearest_vertex(person)->point();
      if(CGAL::squared_distance(person, nearest) < d){
        cout << "n"; 
        continue;
      }
      auto start = t.locate(person);
      double info = start->info();
      if(info >= 4.0 * d) cout << "y";
      else cout << "n";
    }
    cout << endl;
  }
}