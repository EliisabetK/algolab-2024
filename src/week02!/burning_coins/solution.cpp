///3

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; 
  cin >> T;
  while (T--) {
    int n; 
    cin >> n;
    vector<int> coins(n);
    for (int i = 0; i < n; i++)  cin >> coins[i];
    vector<vector<int>> dp(n, vector<int>(n,0));
    for(int i = n-1; i >= 0; i--){
      for(int j = i; j < n; j++){
        dp[i][i] = coins[i]; // only one coin
        if(j-i == 1){
          dp[i][j] = max(coins[i], coins[j]); //. two coins, take the max
        }
        else{
          int both_left, both_right, me_left_op_right;
          if(i+2 < n) both_left = dp[i+2][j]; else both_left = 0;
          if(i+1 < n && j-1 >= 0) me_left_op_right = dp[i+1][j-1]; else me_left_op_right = 0;
          if(j-2 >= 0) both_right = dp[i][j-2]; else both_right = 0;
          
          int left = coins[i] + min(both_left, me_left_op_right);
          int right = coins[j] + min(both_right, me_left_op_right);
          dp[i][j] = max(left, right);
        }
      }
    }
    cout << dp[0][n-1] << endl;
  }
}
