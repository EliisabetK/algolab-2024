#### Explanation
You and a friend alternately pick coins from the ends of a line (you starting). 
The goal is to calculate the maximum guaranteed win, assuming both play optimally, which means assuming both you and your friend play optimally (you try to maximize you and he tries to minimize yours).  
Looking for the local optimal solution doesn't work because choosing the current best coin doesn't guarantee choosing the best in the next turn.  

1. Make a n x n dp table, fill it from bottom up.
2. Loop through i (n-1...0) and j (1 ... n). The diagonal element is just the coin. If there is 2 coins left, pick the maximum. 
3. Then in the else case, calculate three options:
    * both players pick left coin, then the both_left option is dp[i+2][j]
    * one player picks left, one picks right, then the option is dp[i+1][j-1]
    * both players pick right coin, then the both_left option is dp[i+1][j-1]
4. Then get the two cases, if we pick right coin and if we pick left. This is the sum of the coin being picked from either index and correspondingly the minimum of the dps:
    * left = coin[i] + min(both_left, one right one left)
5. Get the maximum of left and right cases, which is the new dp[i][j]
6. The final result is the top right element. 