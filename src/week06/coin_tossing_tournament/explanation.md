#### Explanation
A coin-tossing game is played among n players. However we lost track of the results, so each game has three possible outcomes:
1. Player A wins.
2. Player B wins.
3. The outcome is unknown (we forgot to track it down because we were high as fuck).
Given the final scores of the players that your friends told you, determine whether it is possible for the outcomes to match the desired scores.

Approach:
1. Represent the games as edges between the players: label the nodes 1 to m as the games, m+1 to m + n as the players, add source node 0 and sink node m + n + 1
2. Add edges from a source node to each game node with capacity 1, add an edge from games to the winner with capacity 1 (or two edges for each player if unknown), and edges from each player node to the sink, with capacity equal to their final score.
3. Compute the maximum flow: if the total flow equals the number of games AND m equals the total score, the sum of the desired scores, it is possible.