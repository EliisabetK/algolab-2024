#### Explanation
Given a rectangular grid, determine whether it is possible to cover all empty cells (denoted by `.`) with 2x1 tiles.  
Note: filled cells are marked as `x` and cannot be covered. We can solve this by adding an edge for every possible position, and then run maximum matching to see if the matching was exact (= 2 * free spots).

Approach:
1. Read the input as maps of pairs and indexes: map<pair<int,int>, int>.
2. Go through the nodes and add an edge between every possible node. Do that by checking with 4 if statements if from a node you can go to another neighbouring node.
3. Run maximum matching to see if the size is excactly 2*n, where n is the number of possible positions.
