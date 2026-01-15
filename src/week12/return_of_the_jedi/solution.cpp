///2

#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
using namespace std;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--){
    int n; int Tatooine;
    cin >> n >> Tatooine;
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    edge_desc e;
    vector<vector<int>> costs(n, vector<int>(n,0)); // matrix for the costs
    for(int i = 0; i < n; i++){
      for(int j = i+1; j < n; j++){
        cin >> costs[i][j];
        costs[j][i] = costs[i][j];
        e = boost::add_edge(i, j, G).first; weights[e] = costs[i][j];
      }
    }
    vector<edge_desc> mst_edges;
    boost::kruskal_minimum_spanning_tree(G, back_inserter(mst_edges));
    vector<vector<bool>> edge_in_mst(n, vector<bool>(n,false));
    int mst_cost = 0;
    vector<vector<int>> mst(n);
    
    for(auto& edge : mst_edges){
      int u = boost::source(edge, G), v = boost::target(edge, G), d = weights[edge];
      edge_in_mst[u][v] = edge_in_mst[v][u] = true;
      mst_cost += d;
      mst[u].push_back(v);
      mst[v].push_back(u);
    }
    vector<vector<int>> most_expensive(n, vector<int>(n,0));
    for(int u = 0; u < n; u++){ // DFS
      stack<int> stackk;
      vector<bool> visited(n,false);
      stackk.push(u);
      while(!stackk.empty()){
        int v = stackk.top();
        stackk.pop();
        visited[v] = true;
        for(int k : mst[v]){
          if(visited[k]) continue;
          stackk.push(k);
          most_expensive[u][k] = max(most_expensive[u][v], costs[v][k]);
        }
      }
    }
    int cost_to_change = 1000000000;
    for(int i = 0; i < n-1; i++){
      for(int j = i+1; j < n; j++){
        if(edge_in_mst[i][j]) continue;
        cost_to_change = min(cost_to_change, costs[i][j]-most_expensive[i][j]);
      }
    }
    cout << mst_cost + cost_to_change << endl;
  }
}