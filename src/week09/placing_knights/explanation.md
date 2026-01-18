#### Explanation
- Given a board of size n, with holes (represented by 0, where we cannot place a knight), we need to find the maximum number of knights so that no knights threatens each other.
- This problem means to find the maximum independent set of knights so no two knights are attacking each other, very analogous to MaxIS.
- Each square with x = 1 → a vertex, put an edge between two vertices if the knights attack each other, we want the maximum independent set (MIS)

A knight always moves from white to black or black to white - the attack graph is bipartite.
Maximum Independent Set = |V| − Minimum Vertex Cover. Minimum Vertex Cover = Maximum Matching = Flow.

1. Model the graph like so: 
    * An edge from source to white nodes (i+j is even) with capacity 1.
    * An edge from black nodes to sink.
    * An edge from each WHITE node and the nodes it can attack.
2. Skip nodes that are unplaceable.
3. Count the total number of placeable locations. The number of knights that can be placed is total - flow.