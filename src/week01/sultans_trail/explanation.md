#### Explanation
1. Read all intervals in as pairs {point, 1/-1}, -1 if it opens, +1 if it closes (counterintuitively to sort it right)
2. Sort the pairs
2. Go through all pairs, keep a sum and best variable. Subtract pair.second from the sum (because it is -1 so we are actually adding) and if its larger than best, update best.