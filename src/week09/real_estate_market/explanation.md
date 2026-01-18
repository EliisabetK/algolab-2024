#### Explanation
There are N buyers, each that submits bids for each of the M houses but can buy only one. What complicates the problem is that each house belongs to one state out of S different states, where each state has individual restrictions on how many houses can be sold there.
We can divide this problem into different layers:

L1 - source to buyers, where capacity = 1 (each buyer can buy at most one house) and cost = 0 (no benefit from which buyer buys)
L2 - buyers to houses, where capacity = 1 (each buyer has only one bid per house) and cost = INF-bid (since we want to maximise it)
L3 - houses to states, where capacity = 1 (each house can be bought by at most once buyer) and cost = 0 (no benefit from which house is bought)
L4 - states to sink, where capacity = the limit of how many states can be sold in that state and cost = 0 

Then we run max flow to get the number of sites sold and then we find the cost. The actual cost is: flow * INF - cost.

Tips: 
The site -> state row in the input is starting from index 1, so dont forget that.
Run this after calculating the flow: boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
