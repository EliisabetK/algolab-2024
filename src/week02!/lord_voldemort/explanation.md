Find m non-overlapping intervals that sum up to k.

1. Build an array to keep the starts of intervals, like index i has the index of the start of the interval that sums up to k, or -1 if no interval of length k ends there.
2. Make a prefix array of length n+1 which holds what is the best m intervals up to index i. Then loop through every m, initialize a new dp vector with NEG_INF and then for each i <= n, get the dp of index j-1 (dont take the segment at i-1).
3. Then get the the start position "a" from the starts array at i-1. This is the option to take the segment that ends at i-1.
4. Check if a is not -1 and the dp at a is not NEG_INF, which checks whether its possible to pick j-1 segments before index a. 
    *If its possible, then the dp is max of dp[i-1] and prev[a] + (i-a).
5. Swap dp and prefix arrays.
6. After the looping is done, the answer will be at prefix[n];