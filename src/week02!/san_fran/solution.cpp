///3

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v;
    int p;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;  
  cin >> t;
  while (t--) {
    int n, m, k;
    long long x;
    cin >> n >> m >> x >> k;
    vector<vector<Edge>> adj(n); // vector of all u's that shows the outgoing edges from u
    for (int i = 0; i < m; i++) {
      int u, v, p;
      cin >> u >> v >> p;
      adj[u].push_back({v, p});
    }

    vector<int> sinks; // holes with no outgoing 
    for (int u = 0; u < n; u++) {
      if (adj[u].empty()) sinks.push_back(u);
    }

    const long long NEG = -100000000000;
    //maximum score standing at hole u after current number of moves
    // if it is neg than its not reachable 
    vector<long long> dpCur(n, NEG), dpNext(n, NEG); //store best scores for next step
    dpCur[0] = 0;
    bool possible = false;

    for (int step = 0; step <= k; step++) {
      // free reset
      for (int u : sinks) {
        dpCur[0] = max(dpCur[0], dpCur[u]);
      }
      // check if score reached
      long long bestCur = *max_element(dpCur.begin(), dpCur.end());
      if (bestCur >= x) {
        cout << step << "\n";
        possible = true;
        break;
      }
      if (step == k) break; // no moves left
      // relax edges
      for (int u = 0; u < n; u++) {
        if (dpCur[u] == NEG) continue; //not reachable
        for (auto &edge : adj[u]) {
            int v = edge.v;
            int p = edge.p;
            dpNext[v] = max(dpNext[v], dpCur[u] + p);
        }
      }
      dpCur.swap(dpNext); // update dpCur with new values after relax
    }
    if (!possible) {
      cout << "Impossible\n";
    }
  }
}
