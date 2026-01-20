#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <bits/stdc++.h>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

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
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

int main(){
  int T;
  cin >> T;
  while(T--){
    int n,pg,ph,eg,eh,fg,fh,sg,sh;
    cin >>n>>pg>>ph>>eg>>eh>>fg>>fh>>sg>>sh;
    graph GRAPH(2+ph+pg+2*n);
    edge_adder adder(GRAPH);
    int maxP = 1024;
    const int v_source = 0;
    const int G = 1;
    const int islands_in = 1+pg;
    const int islands_out = 1+pg+n;
    const int H = 1+pg+2*n;
    const int v_sink = 1+pg+2*n+ph;
    
    for(int i = 0; i < n; i++){ //island to island
      int pref; cin >> pref;
      adder.add_edge(islands_in+i, islands_out+i, 1, maxP-pref);
    }
    
    adder.add_edge(v_source, G, sg, 0); //source to G
    
    for(int i = 0; i < eg; i++){ // between cities in G
      int u,v,c; cin >> u >> v >> c;
      adder.add_edge(G+u, G+v, c, 0);
    }
    
    adder.add_edge(H, v_sink, sh, 0); // H to sink
    
    for(int i = 0; i < eh; i++){ //between cities H
      int u,v,c; cin >> u >> v >> c;
      adder.add_edge(H+v, H+u, c, 0); ////IDISKDJASKDKSDKSAKDKSADKSA v to u
    }
    for(int i = 0; i < fg; i++){ // between G and islands
      int u,v,c; cin >> u >> v >> c;
      adder.add_edge(G+u, islands_in+v, c, 0);
    }
    for(int i = 0; i < fh; i++){ //between H and islands
      int u,v,c; cin >> u >> v >> c;
      adder.add_edge(islands_out+v, H+u, c, 0);
    }
    
    int flow = boost::push_relabel_max_flow(GRAPH, v_source, v_sink);
    boost::successive_shortest_path_nonnegative_weights(GRAPH, v_source, v_sink);
    int cost = boost::find_flow_cost(GRAPH);
    cout << flow << " "<<flow*maxP - cost << endl;
  }
}