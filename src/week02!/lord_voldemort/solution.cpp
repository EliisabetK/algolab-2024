///

#include <bits/stdc++.h>
using namespace std;

// We maximize total destroyed horcruxes using exactly m disjoint segments,
// each segment must have sum exactly k.
// If impossible -> "fail".
static const int NEG_INF = -1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        long long k;
        cin >> n >> m >> k;

        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];

        // 1) Two pointers: for each end r, store the unique start l such that sum(l..r) == k (or -1).
        vector<int> startForEnd(n, -1);
        int l = 0;
        long long sum = 0;
        for (int r = 0; r < n; r++) {
          sum += v[r];
          while (sum > k && l <= r) {
              sum -= v[l++];
          }
          if (sum == k) {
              startForEnd[r] = l;
              // move l once so we can continue searching for the next window
              sum -= v[l++];
          }
        }
        // 2) DP over prefix length.
        // prev[i] = best total length using exactly (j-1) segments in first i elements (0..i-1).
        // dp[i]   = best total length using exactly j segments in first i elements.
        // i ranges 0..n. Segment [a..(i-1)] has length i-a and prev prefix is a.
        vector<int> prev(n + 1, 0);

        for (int j = 1; j <= m; j++) {
          vector<int> dp(n + 1, NEG_INF);
          for (int i = 1; i <= n; i++) {
              // Option 1: don't end a segment at i-1
              int best = dp[i - 1];
              // Option 2: take the segment that ends at i-1 (if exists)
              int a = startForEnd[i - 1];
              if (a != -1 && prev[a] != NEG_INF) {
                  best = max(best, prev[a] + (i - a));
              }
              dp[i] = best;
          }
          prev.swap(dp);
        }
        int ans = prev[n];
        if (ans < 0) cout << "fail\n";
        else cout << ans << "\n";
    }
    return 0;
}
