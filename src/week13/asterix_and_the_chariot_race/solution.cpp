using namespace std;
#include<bits/stdc++.h>

struct City{
  long save, fix, ignore;
};

City cost(int current, vector<vector<int>>& graph, vector<int>& costs){
  if(graph[current].empty()) return {costs[current], costs[current], 0}; // leaf node, must fix or not
  
  long save_children = 0, ignore_children = 0, min_diff = 1000000000;
  for(int neighbour : graph[current]){
    auto city = cost(neighbour, graph, costs);
    save_children += city.save;
    ignore_children += city.ignore;
    min_diff = min(min_diff, city.fix - city.save);
  }
  long fix_cost = costs[current] + ignore_children;
  long save_cost = min(save_children + min_diff, fix_cost);
  long ignore_cost = min(fix_cost, save_children);
  return {save_cost, fix_cost, ignore_cost};
}

int main(){
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  int T; cin >> T;
  while(T--){
    int n; cin >> n;
    
    vector<vector<int>> graph(n);
    for(int i = 0; i < n-1; i++){
      int u,v; cin >> u >> v;
      graph[u].push_back(v);
    }
    
    vector<int> costs(n);
    for(int i = 0; i < n; i++){
      cin >> costs[i];
    }
    
    cout << cost(0, graph, costs).save << endl;
    
  }
}