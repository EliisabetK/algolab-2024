#include <boost/config.hpp>
#include <vector>
#include <list>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iterator>
#include <iostream>
using namespace std;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS    // Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
    >          graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;

int main(){
  int T; cin >> T;
  while(T--){
    int n,m;
    cin >> n >> m;
    graph G(n);
    for(int i = 0; i < m; i++){
      int u,v; cin >> u >> v;
      add_edge(u, v, G);
    }
    map<edge_desc,int> edge_map;
    int bcc = boost::biconnected_components(G, boost::make_assoc_property_map(edge_map));
    vector<int> counts(bcc,0);
    for(auto& pair : edge_map) counts[pair.second]++;
    
    int k = 0;
    set<pair<int,int>> bridges;
    for(auto& pair : edge_map){
      if(counts[pair.second] == 1){
        k++;
        int source  = boost::source(pair.first, G);
        int target  = boost::target(pair.first, G);
        bridges.insert({min(source, target), max(source, target)});
      }
    }
    cout << k << endl;
    for(auto& bridge : bridges){
      cout << bridge.first << " "<< bridge.second << endl;
    }
  }
}