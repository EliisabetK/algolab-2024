///1
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<pair<int,int>> points(2*n);
    for(int i = 0; i < n; i++){
      int open, close;
      cin >> open >> close;
      points.push_back({open, -1});
      points.push_back({close, +1});
    }
    int best = -1;
    int sum = 0;
    sort(points.begin(), points.end());
    for(auto& pair : points){
      sum -= pair.second;
      if(sum > best) best = sum;
    }
    cout << best << endl;
  }
}
