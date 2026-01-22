Tips for lp:

1.  You basically build a matrix of a values, so however many rows that there are equations and columns as there are variables (lp.set_a). Then you make the other side that is the vector of b values (lp.set_b). For the objective you use lp.set_c and upper bound is with lp.set_u.
 LP solver by default only minimizes, so to maximize you minimize -(ax - by) to get b·y − a·x. Don't forget to flip the sign after in the solution also.
2. It can only do smaller or equal sign ⩽ , can't do greater.
3. To get the ceil function from the floor function, flip the order of the while loops and flip the signs and equations.