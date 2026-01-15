///2

#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

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
    int n, e1, s, a, b;
    cin >> n >> e1 >> s >> a >> b;
    vector<weighted_graph> graphs(s + 1, weighted_graph(n)); // keep all species graphs
    vector<weight_map> weights(s + 1);  // keep all species weights
    for (int j = 0; j <= s; ++j) {
      weights[j] = boost::get(boost::edge_weight, graphs[j]);
    }
    edge_desc e;
    for(int i = 0; i < e1; i++){
      int t1,t2; cin >> t1 >> t2;
      for(int j = 0; j < s; j++){
        int weight; cin >> weight;
        e = boost::add_edge(t1,t2,graphs[j]).first; weights[j][e]=weight;
      }
    }
    vector<int> hive(s);
    for(int i = 0; i < s; i++) cin >> hive[i];
    
    vector<vector<edge_desc>> mst(s);
    for(int i = 0; i < s; i++){
      boost::kruskal_minimum_spanning_tree(graphs[i], back_inserter(mst[i]));
      for(auto edge : mst[i]){
        e = boost::add_edge(boost::source(edge, graphs[i]), boost::target(edge, graphs[i]), graphs[s]).first; 
        weights[s][e]=weights[i][edge];
      }
    }
    cout << dijkstra_dist(graphs[s], a, b) << "\n";
  }
}