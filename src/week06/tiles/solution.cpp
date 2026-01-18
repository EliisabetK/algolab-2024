///3

#include <iostream>
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

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

int main() {
  int T; cin >> T;
  while(T--){
    int w,h; cin >> w >> h;
    int n = 0;
    map<pair<int,int>, int> nodes;
    for(int i = 0; i < h; i++){
      for(int j = 0; j < w; j++){
        char t; 
        cin >> t;
        if(t == '.') {
          n++;
          nodes[{i,j}] = n;
        }
      }
    }
    graph G(n);
    for(auto& pair : nodes){
      int i = pair.first.first;
      int j = pair.first.second;
      int index = pair.second;
      if(nodes.count({i-1,j}) > 0) boost::add_edge(index, nodes[{i-1,j}], G);
      if(nodes.count({i+1,j}) > 0) boost::add_edge(index, nodes[{i+1,j}], G);
      if(nodes.count({i,j-1}) > 0) boost::add_edge(index, nodes[{i,j-1}], G);
      if(nodes.count({i,j+1}) > 0) boost::add_edge(index, nodes[{i,j+1}], G);
    }
    int matching = maximum_matching(G);
    if(matching * 2 == n) cout << "yes" << endl;
    else cout << "no" << endl;
  }
}
