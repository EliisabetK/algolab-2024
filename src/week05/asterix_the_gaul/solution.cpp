///4
using namespace std;
#include<bits/stdc++.h>

struct Subset{
  long long d, t;
  int count;
};

void generate_subsets(int i, int end, const vector<pair<long long,long long>>& movements, 
long long current_dist, long long current_time, long long current_count, vector<Subset>& subsets){
  if(i == end){
    subsets.push_back({current_dist, current_time, current_count});
    return;
  }
  generate_subsets(i+1, end, movements, current_dist, current_time, current_count, subsets);
  generate_subsets(i+1, end, movements, current_dist+movements[i].first, current_time+movements[i].second, current_count+1, subsets);
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int test;
  cin >> test;
  while(test--){
    int n,m; long long D,T;
    cin >> n >> m >> D >> T;
    vector<pair<long long,long long>> moves(n);
    for(int i = 0; i < n; i++){
      cin >> moves[i].first >> moves[i].second;
    }
    vector<long long> sips(m);
    for(int i = 0; i < m; i++) cin >> sips[i];
    vector<Subset> left, right;
    generate_subsets(0, n/2, moves, 0,0,0,left);
    generate_subsets(n/2, n, moves, 0,0,0,right);
    sort(right.begin(), right.end(), [](Subset a, Subset b) { return a.t < b.t; });

    vector<vector<pair<long long, long long>>> right_by_count(n+1);
    for(auto& sub : right){
      right_by_count[sub.count].push_back({sub.t, sub.d});
    }
    for(int i = 0; i <= n; i++){
      if(right_by_count[i].empty()) continue;
      sort(right_by_count[i].begin(), right_by_count[i].end());
      long long maxd = -1;
      for(auto& p : right_by_count[i]){
        maxd = max(maxd, p.second);
        p.second = maxd;
      }
    }
    long long min_gulps = -1;
    for(auto& l : left){
      if(l.t >= T) continue;
      long long time_budget = T-1-l.t;
      for(int r_count = 0; r_count <= (n-n/2); r_count++){
        auto& group = right_by_count[r_count];
        if(group.empty()) continue;
        auto it = upper_bound(group.begin(), group.end(), make_pair(time_budget, (long long) 2e18));
        if(it != group.begin()){
          long long maxrd = prev(it)->second;
          long long total_d = l.d + maxrd;
          int total_moves = l.count + r_count;
          long long needed = D - total_d;
          if(needed <= 0){
            min_gulps = 0;
          }
          else{
            if(m > 0 && total_moves > 0){
              long long required = (needed + total_moves -1) / total_moves;
              auto sip_it = lower_bound(sips.begin(), sips.end(), required);
              if(sip_it != sips.end()){
                int gulps = (int) (sip_it - sips.begin()) + 1;
                if(min_gulps == -1 || gulps < min_gulps){
                  min_gulps = gulps;
                }
              }
            }
          }
        }
      }
      if (min_gulps == 0) break;
    }
    if(min_gulps == -1) cout << "Panoramix captured" << endl;
    else cout << min_gulps << endl;
  }
}