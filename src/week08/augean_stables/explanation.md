Problem:
## Problem

We have `n` stalls with some filth and some value that it must be to be
considered clean. We can open some holes $h_1, h_2, h_3$ to let water get
through that positively or negatively impacts the cleanliness per stall.
Furthermore, we can dig for 2 rivers to get water to the stalls, which makes
the stalls cleaner by some amount. For every hour we work some predetermined
amount of more water flows through $a_{0:24},p_{0:24}$. We can work at most 24
hours on each river. The amount of filth removed from the $i$-th stall is 

$$
(k_i + a^2) h_1 + (\ell_i + p^2) h_2 + (m_i + ap) h_3
$$

What is the minimum amount of hours we need to work to
consider every stall clean.

Solution:
Basically a combo of binary search and LP: 
1. I made a function for the LP with inputs of flow from river A, flow from B and the stables. We have three variables h1,h2,h3 with lowe bound 0 and upper 1. We want to check if we can clean enough shit for it to be less than c, so we read in the three coefficents and set b as c-f (also we need to make the coeficents all negative). Then return true if it is feasible and false if not.
2. Then we read in the stables and make prefix sum arrazs for the rivers.
3. Then we check if its even possible with 48 hours to make the stables clean.
4. Then we do a binary search, low = 0, high = 48 and we try to find the smallest amount of hours.
    * its almost like a normal binarÿ search, ie mid = low + (high - low) / 2, however after we find mid, we brute force find all combinations of i and j that add up to mid
    * we only need 1 for loop between (i=max(0, mid - 24) and i = min(24, mid)) and inside the loop we make j be mid - i; 
    * we then check if the solution is feasible with those hours and if yes, then we update the best variable and break from the loop since we onlz need one valid combination.
    * after the loop we decrease high if the solution is possible or increase low if not.
