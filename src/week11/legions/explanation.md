Problem: 

You are surrounded by lines of people that will start running toward you in different speeds and you need to find the furthest point from them without crossing them.

Solution:

1. Make an lp that has an equation for every line, it has 3 variables X, Y and D and the objective is to maximize D (ie minimize -D)
2. The trick is to fuck around with the formulas and get the coefficents to X and Y and then D, where you also need to account for the speed (ie multiply coefficent of D by v). Then the other side of the equation is c.
3. You need to check that the distance from the original point to the line is with the same sign as the new point and line, as to not cross the lines. You calculate the distance from original point to line: 
    * case positive: D is positive and you need to minimize -D, ax + by + c = D -> -ax -by -c = -D -> -ax -by + D = c. So the coefficents are (neg, neg, pos, pos).
    * case D is negative: need to minimize D, which is already negative: ax + by + c = -D -> ax + by + D = -c.
4. Set the lower bound to D as 0, as distance can't be negative. Set the objective to (D, -1) ie minimize -D.
5. The answer is -objective value, floor it to get the final answer.
