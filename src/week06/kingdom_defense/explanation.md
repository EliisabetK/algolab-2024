#### Explanation
In a kingdom map, each location has a demand and supply of knights, while paths between locations have both lower and upper flow limits.  
In particular we have L locations l and P paths p, then each l with g and d (the given knights and the minimum number of knights needed) and each p with f, t, c, C (the path going from f to t has minimum flow c and maximum C).

1. Initialize a flow variable to track the needed flow.
2. Create a graph with l+2 nodes. Connect the source node to the locations with capcaity g and connect the location to the sink with capacity t. Add d to the flow.
3. For every path, add an edge between vertices f and t with capcaity C-c. Connect t to source with capacity c to enforce minimum. Connect f to sink with capacity c to enforce maximum. Add c to the flow_needed variable.
4. Check if total flow from source to sink is greater or equal to the flow needed.