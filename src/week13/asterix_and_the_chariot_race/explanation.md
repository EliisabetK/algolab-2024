#### Topic
Dynamic programming

#### Explanation

Story summarised:
There are n cities with n-1 roads between them, structured like a tree. To save a city we need to repair either itself or at least one of its neighbours cities. However each city has a different cost, and we want to find the minimum cost to save every city.

Approach: 
Note: multiple approaches are tempting, such as a min vector cover or a min cost max flow, however due to the cost being on the vertices (cities) and being different, we need to go with a DP approach.
- We define a struct city that attributes three states to each node: 
   * fix: the minimum cost of repairing such node.
   * save: the minimum cost of covering the node without repairing it, hence having at least of its children repaired.
   * ignore: the minimum cost of neither repairing this one or covering one of its children.

1. Read in the graph as a vector of vectors, at index i is the list of its children nodes. If a node is 0 then its a leaf.
2. Make a cost function that returns a city with parameters index current, graph and costs vector.
3. Check if the current node is a leaf (its empty) and if so, return a struct of costs of current node and then 0 as the ignore price.
4. Initialize the following variables: fix_children, save_children, min_diff. Then iterate through the nodes children. Call the costs function with the neighbour index to get the city recursively.
5. Add the ignore and save prices of the current node (ie city.ignore, city.save) to the variables we made outside the loop to track the best costs. For min_diff, its the minimum of the current min_diff value and the diference between the city fix and save price.
   - save_sum increases by the cost of saving it (without necessarily repairing it)
   - ignore_sum increases by the cost of not saving it (neither fixing it or saving it)
   - min_fix_diff storing the overall minimum difference to change one of its children from saved to fixed
6. After the loop, get the new fix, save and ignore values:
   * the min price to fix the node is the cost of fixing it from the costs vector and ignoring the children.
   * the min price to save the node is min(fix_cost, save_cost + min_selected_diff) - meaning if fixing this is cheaper, do it, else we can take the cost of saving the children while fixing the least expensive.
   * the price for ignoring is the minimum of saving the children or fixing the node (since ignore does not care just about the current, but below they are saved).
7. Return a struct of these costs. The value we are looking for is the save field of the city struct.