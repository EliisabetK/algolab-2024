#### Explanation
There are n friends, each with strength s corresponding to the maximum weight they can carry.  
There are m boxes, each weighing w. Each friend can carry only one box at a time, and friends cannot cooperate to carry a single box.  

The times to bring the boxes and to return are fixed: 2 minutes to carry and 1 minute to return.  
We need to find the minimum time to bring all the boxes (if possible).  

Hence the procedure is:
1. Sort both the strenghts and weights in descending order and check if it is possible, ie if strength[0] >= weights[0]
2. Create a multiset for the weights and a time variable.
3. In a while loop, iterate through the people vector using an iterator until the box multiset is empty.
4. For each person, get the weight of the biggest box they can lift by using an upper bound and remove that box (upperboud - 1) from the multiset. Increase the iterator. Check if there are any boxes left.
5. IF the upper bound returns the beginning of the list, then the person cant lift any box. Remove their iterator from the people vector and continue with the next person.
6. After the for loop, increase the time by 2 minutes.
7. Check if there are any boxes left, if not, break from the while loop and print the total time. If there are, increase the time by 1 minute for them to go back up.