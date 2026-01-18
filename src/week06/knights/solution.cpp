///2
#include <iostream>
#include <vector>
#include<bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

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
    int m,n,k,c;
    cin >> m >> n >> k >> c;
    map<pair<int,int>, int> intersections;
    for(int i = 0; i < n; i++){
      for(int j = 0; j < m; j++){
        intersections[{i,j}] = 0;
      }
    }
    
    for(int i = 0; i < k; i++){
      int x,y; cin >> x >> y;
      intersections[{y,x}] = 1;
    }
  
    graph G(2+2*n*m);
    edge_adder adder(G);
    const int v_source = 0;
    const int intersection_in = 1;
    const int intersection_out = 1+n*m;
    const int v_sink = 1+2*n*m;
    int i = 0;
    for(auto& inter : intersections){
      if(inter.second > 0) adder.add_edge(v_source, i + intersection_in, 1); // source to intersection
      adder.add_edge(i + intersection_in, i + intersection_out, c); // vertex capacity
      // tunnels:
      if(inter.first.first - 1 >= 0) adder.add_edge(i + intersection_out, i-m + intersection_in, 1);
      if(inter.first.first + 1 <= n-1) adder.add_edge(i + intersection_out, i+m + intersection_in, 1);
      if(inter.first.second + 1 <= m-1) adder.add_edge(i + intersection_out, i+1 + intersection_in, 1);
      if(inter.first.second - 1 >= 0) adder.add_edge(i + intersection_out, i-1 + intersection_in, 1);
      int exits = 0; 
      // intersection to sink
      if(inter.first.first == 0) exits++;
      if(inter.first.first == n - 1) exits++;
      if(inter.first.second == 0) exits++;
      if(inter.first.second == m - 1) exits++;
      adder.add_edge(i + intersection_out, v_sink, exits);
        i++;
    }
    long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
    cout << flow << endl;
  }
}