#### Explanation
In this problem, multiple species of ants contribute to building a network between a source and a target node in a forest. Each species can only use specific paths, forming a unique graph.  
The task is to find the shortest path from the source to the target if all species collaborate.

Approach:
1. Use a vector(s+1) of graphs and a vector(s+1) of weights to keep each species graphs and weight maps
2. Build a graph for each species with their respective paths and weights.
3. Make a vector of MSTs. Compute the MST (Minimum Spanning Tree) for each species, as ants can only traverse these edges.
3. Merge all MSTs into a combined graph by adding all MST edges with corresponding weights to graph s.
4. Use Dijkstra’s algorithm on the combined graph to find the shortest path between the source and target.