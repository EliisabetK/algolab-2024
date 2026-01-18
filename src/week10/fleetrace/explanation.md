Task: 
You have boats and sailors that can participate in a race. Every boat can have 1 sailor and every sailor can participate in one race, however they dont have to. There is a list of boat and sailor pairings with a spectacle coefficient. The task is to find the maximum sum of specacles, however not every boat has to participate in the race.

The only trick here is the opt out edge.

1. Make a graph with 2 + b + s nodes. Connect source node to boats with capacity 1 and cost 0. Also add an opt out edge from the boats straight to the sink with cost 5000. This allows us to not use every boat if that helps.
2. For each boat-sailor pairing, add an edge from boat to sailor with capacity 1 and cost 5000 - spectacle.
3. From each sailor add an edge to the sink with capacity 1 and cost 0.
4. Run max flow and find the min cost. The maximum specacle is 5000*flow-cost.