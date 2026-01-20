Task:
There is a network of paths, each path has a subnetwork of rabbit tunnels, where the rabbits carry carrots from their home at node 0 to the opening to the path at node ni-1.
The task is to find the minimum amount of carrots that need to be removed for the graph to become disconnected and the minimum amount of gold to pay to remove the carrots (each rabbit gets 1 coin whose carrots you touch). Basically the task is to find a minimum cut and then find the minimum amount of edges to be removed.

Solution: 
1. For each rabbit, build their graph and find using dijsktra how many carrots are disposed at the opening, it ci - path length. Important to check if the path is INTEGER max value because its connected. Save the amounts of carrots per rabbit in a vector.
2. Then build two graphs to solve the two questions. Both are r*2 + 2 sized. First build the rabbit tunnels. You have to split the nodes, so 2 nodes per rabbit opening, connect corresponing pairs of rabbt_in and rabbit_out nodes with edge capacity carrots[i] (or in the case of graph 2, capacity is min(1, carrots[i])). Remember that rabbit node indexes start from 1.
3. Then go through all edges in the garden path. Check for each u,v if u == 0, then connect it with capacity INF, because the source node has no carrots and from there you can go to the start of the rabbit paths. If the node is > 0, then connect each u + rabbits_out to v+rabbits_in with capacity INF (we only enforce the carrot count in the split nodes before.) Add the edges to graph 2 as well.
4. Then run max flow on graph 1 to get the min amount of carrots (min cut = max flow). If d == 1, then also run it on graph 2 to get minimum amount of edges to cut.

Tips:
* rabbits_out starts from r+2, since r+1 is the sink
