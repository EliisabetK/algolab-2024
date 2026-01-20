#### Explanation
Simulate the growth of bacteria in a rectangular dish. Each bacterium grows quadratically over time, and its growth stops when it touches another bacterium or the dish boundary.  
Determine the time when:
1. The first bacterium dies.
2. Less than half of the bacteria remain alive.
3. The last bacterium dies.

Key Observations:
1. Bacteria grow at a rate described by rho(t) = t^2 + 0.5, where t is the time elapsed.
2. Use a Delaunay triangulation to compute proximity relationships efficiently.
3. For each bacterium:
   - Calculate the minimum distance to the dish boundary.
   - Use incident edges to find the minimum distance to neighbouring bacteria.

More detailed procedure:
1. Read the boundaries of the dish and the coordinates of the bacteria, at the same time for each bacteria find the distance to the nearest border and keep that in a vector of death distances (square them also). Save also the index when saving the bacteria positions.
2. Iterate through the edges and find for each pair of vertices calculate the squared_distance between them and divide by 4 to get the max radius before touching another bacteria. Add it ( for both vertices) to the death distances vector IF it is less than the distance to the border.
3. Find the minimum time corresponding to the death of the bacterium: sqrt(max(0.0,sqrt(death_distances[i])-0.5)). You need the max 0.0 bit for avoiding it becoming negative.
5. The three solutions at the respective indices: 0, n/2, n-1.

Tips:
Not too hard, but annoying to get the syntax correct. Careful with double and long long. 
Also you need three things to get the vertices: 
* auto u = e->first->vertex((e->second+1)%3); 
* int i1 = e->first->vertex((e->second+1)%3)->info(); 
* auto v1 = u->point();
