///1
using namespace std;
#include<bits/stdc++.h>

int main(){
  int T; cin >> T;
  while(T--){
    int n; cin >> n;
    vector<int> words(n);
    int total = 0;
    for(int i = 0; i < n; i++){
      int x; cin >> x;
      words[i] = x;
      total+= x;
    }
    vector<pair<int,int>> mapping;
    for(int i = 0; i < n; i++){
      for(int j = 0; j < words[i]; j++){
        int pos; cin >> pos;
        mapping.push_back({pos, i});
      }
    }
    sort(mapping.begin(), mapping.end());
    vector<int> freq(n, 0);
    long best = 100000000000000;
    int have = 0;
    int left = 0;
    for(int right = 0; right < total; right++){
      int currentWord = mapping[right].second;
      if(freq[currentWord] == 0) have++;
      freq[currentWord]++;
      while(have == n && left <= right){
        if (mapping[right].first - mapping[left].first + 1 < best) best = mapping[right].first - mapping[left].first + 1;
        int currentWordLeft = mapping[left].second;
        freq[currentWordLeft]--;
        if(freq[currentWordLeft] == 0) have--;
        left++;
      }
    }
    cout << best << endl;
  }
}