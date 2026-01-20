///4
using namespace std;
#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <bits/stdc++.h>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc2;
typedef traits::edge_descriptor edge_desc2;

const int INF = 100000000;

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
  return dist_map[t];
}

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
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--){
    int r, m, d;
    cin >> r >> m >> d;
    vector<int> carrots(r);
    for(int i = 0; i < r; i++){
      int ni,mi,ci; cin >> ni >> mi >> ci;
      weighted_graph G(ni);
      edge_desc e;
      weight_map weights = boost::get(boost::edge_weight, G);
      for(int j = 0; j < mi; j++){
        int u,v; cin >> u >> v;
        e = boost::add_edge(u, v, G).first; weights[e]=1;
      }
      int path = dijkstra_dist(G, 0, ni-1);
      if(path >= 2147483647) carrots[i] = 0;
      else carrots[i] = ci - path;
    }
    graph G(r*2+2);
    graph G2(r*2+2);
    edge_adder adder(G);
    edge_adder adder2(G2);
    int v_source = 0;
    int rabbits_in = 0;
    int rabbits_out = r+2;
    int v_sink = 1+r;
    int INF = 300;
    for(int i = 0; i < r; i++){
      int u = i+1;
      adder.add_edge(u + rabbits_in, u + rabbits_out, carrots[i]);
      if(carrots[i] >= 1) adder2.add_edge(u + rabbits_in, u + rabbits_out, 1);
    }
    for(int i = 0; i < m; i++){
      int u,v; cin >> u >> v;
      if(u == v_source) {
        adder.add_edge(v_source, v, INF);
        adder2.add_edge(v_source, v, INF);
      }
      else {
        adder.add_edge(u + rabbits_out, v + rabbits_in, INF);
        adder2.add_edge(u + rabbits_out, v + rabbits_in, INF);
      }
    }
    long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
    if(d == 0) cout << flow << " " << 0 << endl;
    else {
      long flow2 = boost::push_relabel_max_flow(G2, v_source, v_sink);
      cout << flow << " " << flow2 << endl;
    }
  }
}
 