#### Topic
UnionFind with BS

#### Explanation

Story summarised:
There are n planets and "everyday we start from one planet of your choice" and travel to some planets in the nearby to conquer them based on the operation range r.
However also the enemies are conquering the planets "one per day", and we do not want to visit a planet that is either conquered already or will be conquered before we finish our plan.
In particular we know the plans of the enemies, i.e. the order of the planets (including them all), as well as their coordinates.
We want the maximum number of planets conquered, which means given planets p_0, ..., p_n-1, we want the maximum number of planets conquered among those already not visited, p_k, ..., p_n-1. 

TIP: copy the emst file, it gives a good base for the union find and imports.

Approach: 
- We read the number of planets, the range, and store the planets with their indices.
- We want to find k, that is them maximum number of planets conquered, which has a 1 to 1 correspondence with the number of days passed (since we conquer one planet per day).
- We look for the ideal k using binary search, starting with left = 2 and right = n/2, since right > n/2 will be irrelevant (since the enemies would have reached us)
- We therefore insert planets from mid onwards inside the triangulation, and initialise the union-find data structure.
- Inside the binary search, we initialize the union find, ALSO make a sizes vector, merge the two edge iterators together from emst, then get the indexes, the length of the edge, get which components the indexes are in, check if length is less than r2 and if so, then merge the components into c3 and put c3s size into the sizes.
- After the union find, find the max element of the sizes array, if its better than mid, then increase left, if worse then decrease right.
- After binary search is finished, return high.