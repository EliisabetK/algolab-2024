#### Explanation
Key idea: 1:1 correspondence between points being connected (connected components in EMST) <==> we can move between the disks of the points (for a radius >= 2 * minimal distance betw. them, making s = 4r^2 very convenient, since comparing 2r all squared) 
Can copy code from the EMST template, and adapt:

- two UF structures, one for given initial radius with s, one for radius needed to get k
- for first problem (max bones): For each component of tree, store the number of bones reachable (i.e. 4 *distance to closest point <= s)
This can be done via a simple array, as UF comp. have index <= n
Upon merging, add together the numbers. At the end (when all edges <= s considered) look for max
- for second problem (min. radius b to get k): Have additional edges from each bone to closest point with edge weight 4 * dist. vectoSort as usual, then do same procedure as above (i.e. UF) until one comp has >= k bones
Then the latest edge considered has minimal radius needed

Solution:
1) Read n, m, s, k: #tree, #bones, s = 4*r^2 where r is the radius of a tree, k = min number of bones in the same region
2) Read tree positions, build Delaunay. Make an edge_vector for the bones->tree linking. Make a sizes array to keep how many bones each tree has.
3) For each bone, find nearest oak tree, decide if it is in its shadow
   - find nearest tree vertex in Delaunay
   - if bone is within radius r: 4 * dist <= s, then increase the number of bones in the tree vector with index [v->info()]. Push the triple of vertex, n+i(bone index) and distance.
4) Make an edges array. Iterate through the triangulation like in the emst file.
5) Sort edges by their length like in the emst file.
6) UNION-FIND #1: largest number of bones for radius r
  - copy the code from the emst file but add the distance that you get with this: get<2>(*e). If the distance is less than s then link the two things c1 and c2. 
  - get their sizes from the sizes array and set the new linked components index as the size of s1+s2 in the sizes vector.
  - merge the two components into the new representative (if condition is satisfied)
  - no need to continue if edges exceed s.
  - a = maximum bones in any connected component (get the max element from sizes array)
7) UNION-FIND #2: find minimal radius => edges + oak-to-bone
  - make a new sizes array sized n+m
  - add all bone edges to the original edges array and add the sizes to the new vector
  - sort again
  - we have n + m total "vertices" => 0..n-1 for oaks, n..n+m-1 for bones; where each bone-vertex has 1 bone
  - do the same union find structure as before, no need to check distance tho. Check if the new component has >= k bones, store that distance and break