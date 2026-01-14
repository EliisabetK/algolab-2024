#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> xs(n);
        for (int i = 0; i < n; i++) cin >> xs[i];
        int evens = 1;
        int odds = 0;
        int prefix = 0;
        long long result = 0;

        for (int x : xs) {
            prefix += x;
            if (prefix % 2 == 0) {
                result += evens;
                evens++;
            } else {
                result += odds;
                odds++;
            }
        }

        cout << result << "\n";
    }
}
