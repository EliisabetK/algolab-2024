///4
#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex;

using namespace std;

vector<int> dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;
}

int maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc> mate_map(n);  // exterior property map
  const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  return matching_size;
}

int main(){
  int T; cin >> T;
  while(T--){
    int n,m,b,p,d; cin >> n >> m >> b >> p >> d;
    vector<int> barracks(b);
    for(int i = 0; i < b; i++)
      cin >> barracks[i];
    unordered_map<int, int> plazas;
    for (int i = 0; i < p; i++){ 
      int pl; cin >> pl;
      plazas[pl] = n + i;
    }
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    edge_desc e;
    vector<edge_desc> edges;
    for(int i = 0; i < m; i++){
      int x,y,l;
      cin >> x >> y >> l;
      e = boost::add_edge(x, y, G).first; weights[e]=l;
      edges.push_back(e);
    }
    vector<bool> reachable(n, false);
    for(auto& barrack : barracks){
      vector<int> dists = dijkstra_dist(G, barrack);
      for(int i = 0; i < n; i++){
        if(dists[i] <= d) reachable[i] = true;
      }
    }
    graph G2(n+p);
    for(auto& edge : edges){
      int u = boost::source(edge, G);
      int v = boost::target(edge, G);
      if (!reachable[u] || !reachable[v]) continue;
      add_edge(u, v, G2);
      if(plazas.find(u)!=plazas.end()){
        add_edge(plazas[u], v, G2);
      }
      if(plazas.find(v)!=plazas.end()) {
        add_edge(plazas[v], u, G2);
      }
    }
    int safes = maximum_matching(G2);
    cout << safes << endl;
  }
}