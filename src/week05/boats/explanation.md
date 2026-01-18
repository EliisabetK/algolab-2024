#### Explanation
There are n boats, each defined by a length l and the position p of the ring that holds the boat.  
No two boats can overlap (but they can barely touch), and the ring should be inside the length of the boat.  
We need to output the maximum number of boats that can fit.  

This problem is identical to the event scheduling problem (greedily solved by sorting events by their finishing time) and it is one of the most common greedy problems.
Basically eeasy but have to remember the while loop.

Key steps:
1. Read in the boats as pairs, first is position and second is length.
2. Sort the boats by their position (for the greedy approach).
3. Create a count variable and a variable for the endpoint. Initialize the count with 1 and endpoint with the first boats end position.
4. In a for loop (no i++), iterate throught the next n boats. create a variable to store the next boats end position.
   5. In the for loop create a while loop, conditions are that i < n and the next_end variable value is greater than the boat[i]'s end position.
   6. The new next_end position is the minimum of the current next end and the maximum of the current endpoint + length and boat[i]s end. Increase the iterator
7. Outside of the while loop a boat is placed, set the new end point as the next_end and increase the count.