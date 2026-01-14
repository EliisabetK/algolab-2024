#### Explanation
1. Build a m_0+...+m_n-1 pair vector, first element is the word appearance number, second element is the index of which word it came from (which row it was read from as input)
2. Sort by the first element.
3. With a sliding window look through the second row to find the smallest interval where all words are covered. Keep track of the smallest b-a which come from the first row! Need variables for "have" and "best". 
    - use a frequency vector to track the words
    - for loop for the right index, begins at 0
    - increase right until all words are covered
    - then in a while loop check if b-a+1 is smaller than current best, then decrease the frequency of the word at the left, if it becomes zero, remove one from the have tracker.increase left until left reaches right or words arent covered anymore
4. Print b-a+1