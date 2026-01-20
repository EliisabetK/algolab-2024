#### Explanation
Given a set of n infected people, determine which of other m individuals can escape without getting infected (defined by x, y, d: squared distance to be mantained).

Approach:
1. Create a Delaunay triangulation of the infected people's locations: t.insert(pts.begin(), pts.end())
2. For every face (node) find the widest possible escape path. Each shared edge is a gate with weight = width. Path capacity is the minimum edge weight on the path, we need the maximum of this minimum (maximum bottleneck).
3. We make a priority queue with a pair of double and face_handle. We iterate through the faces of the triangulation. We check if the face is infinite and if it is, we set its info field as INF and push  {INF, f} to the priority queue. Else we mark f-> info() as -1 to make it unvisited.
4. We perform DFS:
   * Get the top of the queue and pop the queue. Get the value and the face from the top.
   * If value is smaller than the value of the face, continue.
   * Else iterate through the 3 neighbour faces of the face. If the current neightbours value is greater or equal to the current value, continue.
   * Else get the two nodes of the shared edge of the faces. Calculate the squared distance of the vertices (gate width). The path capacity (new value) is the minimum of the current value and the gate width. If this value is larger than the old one of the neighbour, then set it as the new value and push the pair of {new value, neightbour} to the PQ.
5. For each person, check:
   - The squared distance to the nearest infected person. If its less than d, then output no.
   - If sufficient, get the start_face of the person using locate(person). Get the info from the face and check if it is more than 4.0*d.