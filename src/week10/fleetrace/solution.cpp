///4

using namespace std;
#include<bits/stdc++.h>

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
typedef boost::graph_traits<graph>::in_edge_iterator in_edge_it;

class edge_adder {
 graph &G;
  public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;       // cost
    w_map[rev_e] = -cost; 
  }
};

int main(){
  int T;
  cin >> T;
  while(T--){
    int b,s,p; cin >> b >> s >> p;
    graph G(2+b+s);
    edge_adder adder(G);
    const int v_source = b+s;
    const int v_sink = b+s+1;
    for(int i = 0; i < b; i++){
      adder.add_edge(v_source, i, 1, 0);
      adder.add_edge(i, v_sink, 1, 5000);
    }
    for(int i = 0; i < p; i++){
      int boat, sailor, spectacle;
      cin >> boat >> sailor >> spectacle;
      adder.add_edge(boat, sailor + b, 1, 5000-spectacle);
    }
    for(int i = 0; i < s; i++){
       adder.add_edge(i+b, v_sink, 1, 0);
    }
    int flow= boost::push_relabel_max_flow(G, v_source, v_sink);
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
    int cost = boost::find_flow_cost(G);
    cout << 5000* flow - cost << endl;
  }
}
