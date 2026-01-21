Task is to find the minimum cost of emptying packages from two stacks A and B, you can take at least 1 or more packages from the piles but they must run out at the same time.

Solution:
1. Read in the vectors and reverse them to make the stacks. Make them into prefix sum arrays, so index i holds the sum of all elements before it (subtract 1 from every element you add due to the weird formula)
2. Make a 2d dp array of size n+1, initialize it with a large number. DP[i][j] = minimum cost after i packages from A and j packages from B have been removed.
3. Using two for loops, i being the index of the packages removed from stack A and j being stack B, iterate through the stacks with two cases:
    * case 1: remove k packages from A and 1 package from b. Make a loop to look through the k values, the dp value is the minimum of dp and the cost of removing 1 package from B * removing k packages from A + dp[k][j-1].
    * case 2: remove 1 package from A and k packages from b. Exact same thing as case 1, but now loop through k = 1...j and use dp[i-1][k]
4. The final result is at dp[n][n];