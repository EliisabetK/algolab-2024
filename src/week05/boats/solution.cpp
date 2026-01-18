///1

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; cin >> T;
  while (T--) {
    int n; cin >> n;
    vector<pair<int, int>> boats(n);
    for (int i = 0; i < n; i++) {
      int l, p;
      cin >> l >> p;
      boats[i] = {p, l};
    }

    sort(boats.begin(), boats.end());
    int count = 1;
    int endpoint = boats[0].first; // current endpoint position
    for (int i = 1; i < n;) {
      int next = 1000000000; // large starting value for the position
      // move forward as long as boat i overlaps with the endpoint
      while (i < n && next > boats[i].first) {
        next = min(next, max(endpoint + boats[i].second, boats[i].first));
        i++;
      }
      endpoint = next;
      count++;
    }
    cout << count << "\n";
  }
}
