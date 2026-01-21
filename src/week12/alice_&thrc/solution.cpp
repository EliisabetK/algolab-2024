#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const long long INF_LL = 1e18;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> rabbits(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> rabbits[i][j];
        }
    }

    vector<vector<long long>> CostSouth(n, vector<long long>(m, 0));
    vector<vector<long long>> CostEast(n, vector<long long>(m, 0));
    for (int i = 0; i < n; i++) {
        long long current_sum = 0;
        for (int j = m - 1; j >= 0; j--) {
            CostSouth[i][j] = current_sum; 
            current_sum += rabbits[i][j];
        }
    }
    for (int j = 0; j < m; j++) {
        long long current_sum = 0;
        for (int i = n - 1; i >= 0; i--) {
            CostEast[i][j] = current_sum;
            current_sum += rabbits[i][j];
        }
    }
    for (int j = 0; j < m; j++) {
        for (int i = 1; i < n; i++) {
            CostSouth[i][j] += CostSouth[i-1][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j++) {
            CostEast[i][j] += CostEast[i][j-1];
        }
    }

    vector<vector<long long>> dp(n, vector<long long>(m, INF_LL));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i > 0){
                long long cost = dp[i-1][j] + CostSouth[i-1][j];
                if (cost < dp[i][j]) dp[i][j] = cost;
            }
            if(j > 0){
                long long cost = dp[i][j-1] + CostEast[i][j-1];
                if (cost < dp[i][j]) dp[i][j] = cost;
            }
        }
    }
    cout << dp[n-1][m-1] << "\n";
  }
}
