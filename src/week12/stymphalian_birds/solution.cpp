///4

using namespace std;
#include<bits/stdc++.h>

int main(){
  int T; cin >> T;
  while(T--){
    int n; cin >> n;
    vector<int> birds(n);
    for(int i = 0; i < n; i++) cin >> birds[i];
    for(int i = 1; i < n; i++){
      int bird = birds[i];
      int parent = birds[floor((i*1.0-1)/(2*1.0))];
      birds[i] = min((parent-1), bird);
    }
    sort(birds.begin(), birds.end());
    bool possible = true;
    for(int i = 0; i < n; i++){
      if(i >= birds[i]) {
        cout << "no" << endl;
        possible = false;
        break;
      }
    }
    if(possible) cout << "yes" << endl;
  }
}