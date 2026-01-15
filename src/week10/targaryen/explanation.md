#### Explanation
There are n intersections (nodes), m roads (edges), b barracks (intersections from which infinite troops can leave), p plazas (special kind of intersection), and d distance (maximum that can be travelled by troops).
We want to build as many safe roads as possible, where a safe road is a road where the two respective intersections joined have build on such road a barricade.
Typically regular intersections allow at most one road to construct the barricade, but for a plaza is at most two.
Hence we can solve this problem using dijkstra + edmonds:

1. Store the barracks as vectors and plazas as maps with <plaza, n + i>
2. Read the graph (weighted and undirected, CHANGE THE DEFINITIONS) and store the edges separately as well in a vector edge_descs
3. Make a ""reachable" array and initialize it with false. Use dijkstra from each barrack and track down all the nodes that are reachable (i.e. dist_map[i] <= d)
4. Make another graph, size n+p, because we are doubling the nodes that are plazas. Iterate through the edges array, find for each edge the source and target vertex. If both are reachable, add this edge to the new graph. 
5. Check if source or target nodes are plazas by checking if the plazas map contains the source or target. If yes, then add a new edge from plazas[source] to target or vice versa.
6. Run the maximum matching function and save the matching size, which corresponds to the number of safe streets.