#### Explanation
- In a cave structured as a grid layout with m columns and n rows, we have k knights inside that want to escape. However, all the hallways (edges) fall after one knight passes, whereas the intersections (nodes) are more robust and resist to C knights.

Solution:
1. Make all possible intersections in a map of coordinates and and integer showing if a knight is there, then read in the positions of the knights and increase the map coordinate count.
2. Make a graph that has 2+2*n*m nodes, source node, two rows of intersections and sink node. The edges are between source and intersection with capacity 1, if the intersection has a knight. Then there is an edge between vertices in and out with capacity c, like between i and i + n*m. Then from each out vertex, and edge with capacity 1 goes from there to the possible next intersection_in if it is in bounds (if you increase the row by, then the index is i+m, if you increase the column, then it is i+1). 
3. Then add an edge from intersection_out to the sink node if the intersection is at an exit (ie if one coordinate is 0 or n-1 etc). Count the exits, like each possible direction is an additional exit, put the number of exits as the capacity.
4. The number of knights who can escape is the flow.