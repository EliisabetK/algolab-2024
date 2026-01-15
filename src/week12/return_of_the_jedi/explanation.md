#### Topic
Second best MST

#### Explanation

Story summarised:
- The Rebels need a robust warp network to ensure secure communication between all planets. Each planet is assigned a unique number based on its importance. The network needs to satisfy two conditions:
   - All planets must be connected either directly or indirectly.
   - The total cost of constructing the warp network must be minimized.
- Princess Leia uses Kruskal’s algorithm to find the cheapest warp network, which forms a Minimum Spanning Tree (MST). 
- However, R2-D2 suspects that Emperor Palpatine might exploit this predictable network, and proposes to calculate the cost of the second best MST, which is slightly different from Leia's MST and still connects all planets.
- The second best MST is defined as the cheapest MST that differs from the original MST by at least one edge.

General idea:
Build the MST (minimum total weight).
Then find the smallest possible increase (or change) to get a different spanning tree by swapping one non-MST edge in and removing the most expensive edge on the induced cycle.

Approach: 
1. Read the graph using two for loops i...n and j = i+1 ... n. We need a graph and a cost matrix where cost[i][j] = cost from i to j;
2. Construct the MST using Kruskals algorithm.
3. Make the following variables:
   * Make a matrix to keep if edge matrix[i][j] is in the MST or not. True if is.
   * Make a variable to keep the cost of the MST
   * Make a matrix to make the mst again but in a matrix format
4. Iterate thorugh the edges of the mst_edges list. Find the source and target and weight. Add the weight to the cost variable and add the target to the source array of the mst matrix and the source to the target array of the matrix (mst[u].push_back(v);)'
5. Make a matrix to keep the most expensive edge between nodes in the MST.
6. Using DFS, iterate through nodes u
   * Make a stack to keep the current nodes in and make a vector to keep track of which nodes are visited.
   * Push node u to the stack
   * While the stack is not empty do the following:
      - Get the next node v from the top of the stack. POP the stack. Mark v as visited.
      - For every neighbouring node k, check if k is visited, if it is continue. If not, push k to the stack.
      - Calculate the most expensive way to get from u to k. This is the maximum of most_expensive[u][v] and costs[v][k]
7. Make a big variable cost_to_change. Loop through the nodes i = 0...n-1 and j = i+1....n. If the edge[i][j] is in the MST, then continue, if it is not, then the cost to change it is the minimum of current cost_to_change and the cost from i to j - most_expensive path from i to j. Basically you add an edge and remove the most expensive edge in that cycle, so subtract the values.
8. Output the sum of the MST cost and the cost to change and edge.

