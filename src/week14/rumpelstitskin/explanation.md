Explanation:

We have n islands, which contain a spinning wheel, each island has one wheel with a preference score that can spin 1 yarn. We need straw from islands G and H. The islands have their straw in castle with index 0. There are roads between cities in the islands G and H (not between G and H) and between the cities and islands, they have capacities.

Very easy except that the graph can be unintuitive, like the edges between cities in H being backwards.
Solution:
1. Make a graph like this: source -> G(0) -> other cities in 0 -> islands_in -> islands_out -> cities in H -> H(0) -> sink.
2. Add an edge from source to G(0) with capacity straw G. Add edges between cities G u and v with capacity c and cost 0. Add edges from cities to islands. Add edges between islands_in (duplicate the nodes to enforce that each island is used once) with capacity 1 and cost maxPreference - preference. Add edges from islands to cities. Add cities between cities in H V -> U (IMPORTANT THAT ITS BACKWARDS) and then from city with index 0 to sink with capacity equal to straw H.
3. Run max flow and find cost. Actual cost is flow * maxP - cost.