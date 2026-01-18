using namespace std;
#include<bits/stdc++.h>

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;
// Custom edge adder class, highly recommended
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
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int n, b, k, m;
    cin >> n >> b >> k >> m;
    vector<int> affinity(n);
    int total_happiness = 0;
    for(int i = 0; i < n; i++) {
      cin >> affinity[i]; 
      total_happiness += abs(affinity[i]);
    }
    int f_happiness = 0;
    vector<vector<int>> friendships(n, vector<int>(n));
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        cin >> friendships[i][j];
        f_happiness +=friendships[i][j];
      }
    }
    total_happiness += f_happiness/2;
    
    // case simba on team A, nala on B
    graph G(n+2);
    edge_adder adder(G);  
    const int v_source = n; //  team A
    const int v_sink = n+1; // team B
    adder.add_edge(v_source, k, 100000000);
    adder.add_edge(m, v_sink, 100000000);
    for(int i = 0; i < n; i++){
      if(affinity[i] > 0) adder.add_edge(v_source, i, abs(affinity[i]));
      else adder.add_edge(i, v_sink, abs(affinity[i]));
    }
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        adder.add_edge(i, j, friendships[i][j]);
      }
    }
    
    // case simba team B, nala team A
    graph G2(n+2);
    edge_adder adder2(G2);  
    adder2.add_edge(k, v_sink, 100000000);
    adder2.add_edge(v_source, m, 100000000);
    for(int i = 0; i < n; i++){
      if(affinity[i] > 0) adder2.add_edge(v_source, i, abs(affinity[i]));
      else adder2.add_edge(i, v_sink, abs(affinity[i]));
    }
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        adder2.add_edge(i, j, friendships[i][j]);
      }
    }
    
    long flow1 = boost::push_relabel_max_flow(G, v_source, v_sink);
    long flow2 = boost::push_relabel_max_flow(G2, v_source, v_sink);
    if(b == 0){
      cout << total_happiness - 2*min(flow1,flow2) << endl;
    }
    else cout << min(flow1,flow2)<< endl;
  }
}