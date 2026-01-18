#### Topic
Minimum Cut
#### Explanation

There is a game with two teams. Each cub has an affinity to play on a certain team as well as wishes to be on the same team as their friends, if they are on the wrong team or not on a team with their friends, they get a negative value added to the global dissatisfaction. If they are on the correct team or with their friends, global happiness is increases. Simba and nala, cubs k and m need to be on different teams.

The idea is that we connect every cub to their wished team and connect cubs with their friends, and then the dissatisfaction is equal to the minimum cut cost, which is equal to max flow.

1. Read in the inputs and sum the total happiness (only one per friendship pair, so divide it in half) and total absolute affinities. Add them together
2. Build a G(n+2) sized graph. The source node is team A and sink is team B. Make two different cases. Case 1, Simba is on team A and Nala on team B. Connect them to the corresponding source and sink nodes with capacity INF to make sure it isnt cut in the min cut. Case 2 is the opposite.
3. Go thorugh all friendships, add two edges per pair of friends with capacity of the friendship value.
4. Calculate the flows for graph 1 and 2, the minimum of them is the total dissatisfaction.
5. To get the total happiness, subtract 2*flow from total happiness.