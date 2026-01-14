#include <iostream>
#include <vector>
using namespace std;

int main() {
    int tests;
    cin >> tests;

    while (tests--) {
        int n;
        cin >> n;
        
        vector<vector<int>> matrix(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> matrix[i][j];
            }
        }
        
        int result = 0;
        for (int i = 0; i < n; i++) { 
          vector<int> columnSum(n);
          for (int j = i; j < n; j++) { 
            int prefix = 0;
            int evens = 1;
            int odds = 0;
            for (int k = 0; k < n; k++){
              columnSum[k] = (columnSum[k] + matrix[j][k]) % 2;
              prefix = (prefix + columnSum[k]) % 2;
              if (prefix == 0){
                result += evens;
                evens += 1;
              }
              else {
                result += odds;
                odds += 1;
              }
            }
            
          }
        }
        cout << result << "\n";
    }
}