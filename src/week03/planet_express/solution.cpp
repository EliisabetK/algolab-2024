///3

#include<bits/stdc++.h>
using namespace std;

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths_no_color_map.hpp>
#include <boost/graph/strong_components.hpp>

typedef boost::adjacency_list<
  boost::vecS, 
  boost::vecS, 
  boost::directedS,
  boost::no_property, 
  boost::property<boost::edge_weight_t, int>
> weighted_graph;

typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor    vertex_desc;    // Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)). 

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

int main(){
  int T; cin >> T;
  while(T--){
    int n,m,k,t;
    cin >> n >> m >> k >> t;
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    edge_desc e;
    
    vector<int> teleports;
    for(int i = 0; i < t; i++){
      int planet; cin >> planet;
      teleports.push_back(planet);
    }
    for(int i = 0; i < m; i++){
      int u,v,c; cin >> u >> v >> c;
      e = boost::add_edge(u, v, G).first; weights[e]=c;
    }
    vector<int> component_map(n);  // shows for each vertix i0...in which component it belongs to (0,0,0,1,2)
    int scc = boost::strong_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 
    unordered_map<int, vector<int>> network;
    for (auto& tel : teleports){
      network[component_map[tel]].push_back(tel); // cpmponent_map[tel] is the scc index 0,1,2 etc
    }
    
    for(auto& component : network){
      int hub = boost::add_vertex(G);
      int cost = component.second.size() - 1;
      if(cost <= 0) continue;
      for(auto& teleport : component.second){
        e = boost::add_edge(teleport, hub, G).first; weights[e]=cost;
        e = boost::add_edge(hub, teleport, G).first; weights[e]=0;
      }
    }
    
    int fakenode = boost::add_vertex(G);
    for(int i = 0; i < k; i++){
      e = boost::add_edge(fakenode, i, G).first; weights[e]=0;
    }
    
    int time = dijkstra_dist(G, fakenode, n-1);
    if(time <= 1000000)
      cout << time << endl;
    else cout << "no" << endl;
  }
}