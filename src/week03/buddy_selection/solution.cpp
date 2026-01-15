#include <iostream>
#include <vector>
#include <unordered_set>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using namespace std;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

int maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc> mate_map(n);  // exterior property map
  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

  return matching_size;
}

int main(){
  int T; cin >> T;
  while(T--){
    int n,c,f; cin >> n >> c >> f;
    vector<unordered_set<string>> cs;
    for(int i = 0; i < n; i++){
      unordered_set<string> css;
      for(int j = 0; j < c; j++){
        string hobby; cin >> hobby;
        css.insert(hobby);
      }
      cs.push_back(css);
    }
    graph G(n);
    for(int i = 0; i < n; i++){
      for(int j = i+1; j < n; j++){
        int total = 0;
        for(auto& hobby : cs[j]){
          if(cs[i].count(hobby) >= 1) total++;
        }
        if(total > f) 
          boost::add_edge(i, j, G);
      }
    }
    int size = maximum_matching(G);
    if(n / 2 == size) cout << "not optimal" << endl;
    else cout << "optimal" << endl;
  }
}