///3

#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

int main(){
  int T; cin >> T;
  while(T--){
    int n;
    cin >> n;
    graph G(n*n+2);
    edge_adder adder(G);
    const int v_source = n*n;
    const int v_sink = n*n+1;
    int total = 0;
    vector<pair<int,int>> positions = {{-1,-2}, {-1, 2}, {1,-2}, {1, 2}, {-2,-1},{2,-1}, {2, 1}, {-2, 1}};
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        int x; cin >> x;
        if (x == 0) continue;
        total++;
        if((i+j) % 2 != 0){ // connect black squares to sink
          adder.add_edge(i*n+j, v_sink, 1);
          continue;
        }
        adder.add_edge(v_source, i*n+j, 1); // white squares
        for(auto& pos : positions){
          int newI = i + pos.first;
          int newJ = j + pos.second;
          if(newI >= 0 && newI < n && newJ >= 0 && newJ < n) adder.add_edge(i*n+j, newI*n+newJ, 1);
        }
      }
    }
    long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
    cout << total - flow << "\n";
  }
}