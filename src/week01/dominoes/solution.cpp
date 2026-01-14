using namespace std;
#include<bits/stdc++.h>

int main(){
  int T; cin >> T;
  while(T--){
    int n; cin >> n;
    vector<int> heights(n);
    for(int i = 0; i<n; i++){
      cin >> heights[i];
    }
    int fallen = 1;
    int reach = heights[0];
    for(int i = 1; i < n && i < reach; i++){
      reach = max(reach, i + heights[i]);
      fallen++;
    }
    cout << fallen << endl;
  }
}