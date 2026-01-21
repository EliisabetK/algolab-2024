///3

using namespace std;
#include <bits/stdc++.h>

int rec(vector<int>& A, vector<int>& B, int sum, int i, int j, int n){
  if(i == 0 && j != 0 || i != 0 && j == 0){
    return -1;
  }
  if(i == 0 && j == 0) return sum;
  for(int k = 1; k < n-i; k++){ 
    // take k from A and 1 from B
  }
  //case take 
}

const int INF = 1000000000;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  while(T--){
    int n; 
    cin >> n;
    vector<int> A(n), B(n);
    for(int i = 0; i < n; i++) cin >> A[i];
    for(int i = 0; i < n; i++) cin >> B[i];
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    vector<int> prefA(n+1, 0);
    vector<int> prefB(n+1, 0);
    for(int i = 0; i < n; i++){
      prefA[i+1] = A[i] - 1 + prefA[i]; // subtract 1 as per the formula
      prefB[i+1] = B[i] - 1 + prefB[i];
    }
    
    vector<vector<int>> dp(n+1, vector<int>(n+1, INF)); // dp[i][j]: taken i packages from A and j packages from B
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++){
      for(int j = 1; j <= n; j++){
        //case 1: take k from A and 1 from B
        int costB = prefB[j] - prefB[j-1];
        for(int k = 0; k < i; k++){
          dp[i][j] = min(dp[i][j], costB * (prefA[i]-prefA[k]) + dp[k][j-1]);
        }
        //case 2: take 1 from A and k from B
        int costA = prefA[i] - prefA[i-1];
        for(int k = 0; k < j; k++){
          dp[i][j] = min(dp[i][j], costA * (prefB[j]-prefB[k]) + dp[i-1][k]);
        }
      }
    }
    cout << dp[n][n] << endl;
  }
}