#### Explanation
In this problem, there is a network of planets, where the first k are warehouses and some planets are teleport planets. You can teleport from these planets to other planets that are in the same strongly connected component with time scc.size()-1.
The task is to find if there is a path from an optimal warehouse to the target node in under 1 second.

Approach:
1. Build a graph with all planets and read in the teleport planets indexes.
2. Use the strong_components algorithm (can copy most of it from connected comments sample)
3. Make a map <index of component, vector of teleports in that component> by going through the vector of teleports
    - the key is the component, which can be found in the component map with index of the teleport. 
    - network[component_map[tel]].push_back(tel);
3. Go through the map and for each component, make a hub by adding a new vertex. Connect every teleport location in that component to the hub with cost scc.size()-1. Add a node from the hub to the teleport location with cost 0. 
3. Make a fake node and connect it to all warehouses with cost 0 to find the optimal warehouse.
4. Use Dijkstra’s algorithm on the graph and find the distance from the fake node to node n-1, which is the target.