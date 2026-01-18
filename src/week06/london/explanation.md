#### Explanation
There is a newspaper with letters on both sides. You have to check if a word can be assembled using tiles cut out of the newspaper.

Idea is to use max flow to map tiles to letters of the word and check if the flow is equal to the word length.

Key steps:
1. Read the input string and get the frequencies of each letter. 
2. Make a map to hold all possible letter combinations, so 26*26 pairs. Read in the input into tiles and add each tile to the map and count the frequency of each pair.
3. Make a graph with 2 + 26*26 + different letters in the word amount of nodes. The mapping is from the source to each tile with capacity being tile frequency. Then map each tile to a letter of the word. An edge from the tile for both letters, or if they are the same letter then only one edge. The capacity is again the frequency of the tiles. Then map each letter of the word to the sink, capacity is the frequency of the letters in the word.
4. Run the max flow algorithm and find if flow = word.size(). If yes, then its possible.w

Tips:
* Read the input first into a matrix sized 2h*w to get the tiles easier.
* Iterate through the map as pairs but keep variables for the index i and j when needed.
* Subtract 'A' from each character to get them as integers