#### Explanation
Identify critical edges (bridges) in an undirected graph. A bridge is an edge that, if removed, disconnects the graph.  
As explained in the biconnected component part, in order to find the bridges we compute the biconnected components, and check which of the components has only one edge, such edge is a bridge.

Approach:
1. Read the edges of the graph.
2. Make a map <edge_desc,int> to keep which edge is in what component. Run bcc with the map to populate it.
3. Make a vector of counts for each component, initialize with 0.
4. Go through every pair in the edge map and increase the count of the component the edge is in.
5. Initialize k with 0 (number of bridges) and make a set of pairs to keep the bridge vertices.
6. A bridge is a biconnected component that has only one edge. We iterate through the edge map again and if the count is 1 then:
   - We increase k
   - We find the source and target vertice
   - We insert the vertices to the bridges set, but the first of the pair is the smaller one, so use {min, max}
7. Go through the bridges set and output the result