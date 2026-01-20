Explanation:
There is a map of streets, the street between each intersection has length d and width c. The task is to find how many people can run the race, beginning at intersection s and ending at f, if there can be c people in a street. Assume all runners want to pick the shortest path, therefore only the streets that are in a shortest path are relevant. Trick is to use Dijktra and max flow to find the streets and test the flow.

Easy task but requires some fucking around with the typedefs and iterators.

Solution:
1. Read the streets into a graph G. You need a weight map and a width map, you have to add it to the typedefs, both as a width_map with edge_capacity and to the weighted graph type inside the boost::property. Make 2 edge descriptions and add each street both ways (a to b and b to a);
2. Run dijkstra from start and from the finish and save the results in two vectors. Calculate the minimum distance of these two paths (so from start to finish and finish to start)
3. Iterate through the edges in the graph G. Find the source and target vertices u and v and check if the distance from start to u + weight(edge) + distance from v to f is equal to the minimum distance. If yes, then that means that it is an edge in one of the shortest paths. Add it to a new graph G2.
4. Run max flow from start to finish to find the maximum number of runners.

