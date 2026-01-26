#include <bits/stdc++.h>
using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>> pq;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;
  while(T--){
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> brights(n), prev(n, -1), parent(n);
    vector<bool> leaf(n, true), visited(n, false), safe(n, false);
    bool one_safe = false;
    
    for(int i = 0; i < n; i++) cin >> brights[i];
    
    for(int i = 0; i < n-1; i++){
      int u,v; 
      cin >> u >> v;
      prev[v] = u;
      leaf[u] = false;
    }
    
    for (int i = 0; i < n; i++){
      if (leaf[i]){
        pq pq_min, pq_max;
        int curr = i;
        for (int j = 0; curr != -1; j++, curr = prev[curr]){
          parent[j] = curr;
          pq_min.push({-brights[curr], j});
          pq_max.push({brights[curr], j});
          while (pq_min.top().second + m <= j) pq_min.pop();
          while (pq_max.top().second + m <= j) pq_max.pop();
          if (j + 1 - m >= 0){
            if (pq_min.top().first + pq_max.top().first <= k) safe[curr] = one_safe = true;
            if (visited[parent[j + 1 - m]]) break;
            visited[parent[j + 1 - m]] = true;
          }
        }
      }
    }
    if (one_safe){
       for (int i = 0; i < n; i++) {
         if (safe[i]) cout << i << ' ';
       } 
       cout << endl;
    }
    else cout << "Abort mission" << endl;
  }
}