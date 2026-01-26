///2

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;
    while (T--) {
        int n, k, w; 
        cin >> n >> k >> w;

        vector<int> men(n);
        for (int i = 0; i < n; i++) {
            cin >> men[i];
        }
        vector<vector<int>> ways(w); // vector of costs

        for (int i = 0; i < w; i++) {
          int l;
          cin >> l;
          vector<int> route(l);
          for (int j = 0; j < l; j++) {
              cin >> route[j];
          }

          // convert route of island indices into costs
          ways[i].resize(l);
          for (int j = 0; j < l; j++) {
              ways[i][j] = men[route[j]];
          }
        }
        
        int bestA = 0; // case: only one waterway
        for(auto& way : ways){
          int sum = 0; int left = 0;
          for(int right = 0; right < way.size(); right++){
            sum += way[right];
            while(sum > k){
              sum -= way[left++];
            }
            if (sum == k) bestA = max(bestA, right-left+1);
          }
        }
        
        int bestB = 0; // case: different waterways
        vector<vector<int>> prefixes;
        
        for (int j = 0; j < w; j++) {
          int sum = 0, l = 0;
          for (int i = 0; i < ways[j].size(); i++) {
              sum += ways[j][i];
              l++;
              if (sum > k + men[0]) continue;
              prefixes.push_back({sum, l, j});
          }
        }
        sort(prefixes.begin(), prefixes.end(), [](auto &a, auto &b){
            return a[0] < b[0];
        });

        
        int L = 0; int R = prefixes.size()-1; int s = 0;
        while (L < R){
          s = prefixes[L][0] + prefixes[R][0];
          if (s < k + men[0]) L++;
          else if (s > k + men[0]) R--;
          else { // equal sums
            int sumL = prefixes[L][0], sumR = prefixes[R][0];
            int lL = L, rR = R;
            while (lL <= R && prefixes[lL][0] == sumL) lL++;
            while (rR >= L && prefixes[rR][0] == sumR) rR--;
            for (int i = L; i < lL; i++) {
                for (int j = R; j > rR; j--) {
                    if (prefixes[i][2] != prefixes[j][2]) {
                        bestB = max(bestB, prefixes[i][1] + prefixes[j][1] - 1);
                    }
                }
            }
            L = lL;
            R = rR;
          }
        }
        int answer = max(bestA, bestB);
        cout << answer << "\n";
    }
}
