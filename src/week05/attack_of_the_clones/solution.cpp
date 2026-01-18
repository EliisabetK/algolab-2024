///3
using namespace std;
#include<bits/stdc++.h>

struct Jedi{
  int a, b, id;
};

int solve_linear(const vector<Jedi>& jedis, int start, int end, int m){
  int count = 0;
  int current = start;
  for(const auto& j : jedis){
    if(j.a > current && j.b < end){
      count++;
      current = j.b;
    }
  }
  return count;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T; cin >> T;
  while(T--){
    int n,m;
    cin >> n >> m;
    vector<Jedi> jedis;
    map<int,int> diff;
    for(int i = 0; i < n; i++){
      int a,b;
      cin >> a >> b;
      jedis.push_back({a,b,i});
      diff[a]++;
      diff[b+1]--;
      if(a > b) diff[1]++;
    }
    
    int best_segment = 1, min_coverage = n+1, current_coverage = 0;
    for(auto const& [pos, d] : diff){
      if(pos > m) break;
      current_coverage += d;
      if(current_coverage < min_coverage){
        min_coverage = current_coverage;
        best_segment = pos;
      }
    }
    vector<Jedi> linear, covers_s;
    for(auto j : jedis){
      int new_a = (j.a - best_segment + m) % m + 1;
      int new_b = (j.b - best_segment + m) % m + 1;
      if(new_a > new_b) covers_s.push_back({new_a, new_b+m, j.id});
      else {
        linear.push_back({new_a, new_b, j.id});
        linear.push_back({new_a+m, new_b+m, j.id});
      }
    }
    sort(linear.begin(), linear.end(), [] (const Jedi& x, const Jedi& y){ return x.b < y.b;});
    
    int max_jedi = solve_linear(linear,0,m+1,m);
    for(auto const& j : covers_s){
      max_jedi = max(max_jedi, 1+solve_linear(linear, j.b -m, j.a,m));
    }
    cout << max_jedi << endl;
  }
}