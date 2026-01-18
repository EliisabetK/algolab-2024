///3
using namespace std;
#include <bits/stdc++.h>
#include <vector>

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while(T--){
    int n,m;
    cin >> n >> m;
    vector<int> people(n);
    for(int i = 0; i < n; i++) cin >> people[i];
    vector<int> boxes(m);
    for(int i = 0; i < m; i++) cin >> boxes[i];
    sort(people.begin(), people.end(), greater<int>());
    sort(boxes.begin(), boxes.end(), greater<int>());
    if(people[0] < boxes[0]) {
      cout << "impossible" << endl;
      continue;
    }
    multiset<int> weights(boxes.begin(), boxes.end());
    int total_time = 0;
    while(weights.size() > 0){
      for(vector<int>::iterator it = people.begin(); it != people.end();){
        auto it2 = weights.upper_bound(*it); // first element > person
        if (it2 == weights.begin()) {
            it = people.erase(it);
            continue;
        } else {
          --it2;               // now *it <= person (largest liftable)
           weights.erase(it2);  // erase that one box
           ++it;
        }
        if(weights.size() == 0) break;
      }
      total_time += 2;
      if(weights.size() == 0) break;
      total_time++;
    }
    cout << total_time << endl;
  }
}
