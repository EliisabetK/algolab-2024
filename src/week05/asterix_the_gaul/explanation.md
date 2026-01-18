#### Explanation
Panoramix is at distance D from Asterix, while the Romans need T seconds to reach Panoramix.  
Asterix has a list of n possible moves, each consisting of a distance d executed in time t.  
Asterix can perform each movement at most once, and he can take at most m sips from a magic potion. Each sip allows him to cover an additional distance, s_j for each move.

We need to output the minimum number of sips needed for Asterix to reach Panoramix in less than T time, if it's not possible, output "captured".  
It is valid to go beyond D, which makes it tempting to solve this greedily. However, such an approach fails because it cannot satisfy both T and D constraints simultaneously, and the boost is moves dependent.  
This is a subset-sum-like and knapsack-like problem. Since n is small (n < 30) and D is very large (D < 2^50), we use Split and List.

Approach:
- Store the moves and the sips, and try to solve(*) it without sips first (if we succed, we stop).
- Binary search the minimum number of potions that solves the problem (we need to add the potion effect to all the moves, and subtract it after our trial).

1. Read the inputs. Read the moves as pairs and create a subsets vector that holds Subset structs{d,t,count}.
2. Split the list by making a subsets vector for left and right.
	3. Using recursion generate all subsets of moves for left and right:
		* generate_subsets(0, n/2, moves, 0,0,0,left);
		* generate_subsets(n/2, n, moves, 0,0,0,right);
	4. Sort the right subsets vector by time.
5. Create a matrix of pairs to group the right subsets.
	6. For every subset in the right, group together times and distances by their count.
	7. Go through the matrix, if a vector of a certain count is empty, skip it. Otherwise sort the right_by_count  i-th array. Make a variable to keep the max distance. Go through every pair in the array and find the max.
8. Initialize min_gulps to -1 (or a very large number) to track the best solution. 
9. Iterate through every subset in the left vector: Check if its time l.t is already >= T. If so, skip it. Calculate the remaining time budget: T - 1 - l.t.
10. For each left subset, iterate through every r_count bucket (0 to n - n/2): 
	* Use binary search (upper_bound) on right_by_count[r_count] to find the largest distance maxrd that fits within the time budget.
	* Calculate the total distance (l.d + maxrd) and total movements (l.count + r_count).
11. Check the Potion Requirement: If total_distance >= D, Astérix needs 0 gulps. Otherwise, calculate the needed boost per movement:boost = ceil((D - total_distance) / total_moves).
12. Use binary search (lower_bound) on the sorted sips array to find the smallest number of gulps that provides at least this boost. Update min_gulps with the smallest valid number of sips found across all combinations. 
13. Optimization: If min_gulps reaches 0, break all loops early (you can't do better than 0).
14. Final Output: After checking all combinations, if min_gulps is still -1, print "Panoramix captured"; otherwise, print the value of min_gulps.
