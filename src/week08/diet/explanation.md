#### Explanation
Given:
1. n nutrients, each with minimum and maximum daily requirements.
2. m foods, each with a price and nutrient content.  
Determine the minimum cost of a diet that satisfies all constraints. If no diet exists, output "No such diet."

Approach:
It's a set of linear equations, there are m variables and 2n equations (1 for max and 1 for min). The objective is to minimize cost. Each equation is in the form of a a0*x0 + a1*x1 .... <= max (or <= -min). So a....an is the amount of nutrients in food j and and xj​=amount of food j eaten.
1. Read in the constraints, ie that minimum amount of nutrients is 1500 and max is 2500 (to ensure that something is larger than minimum, you have to make it negative).
2. Read in the costs of each and then for each nutrient in that food do: 
    * lp.set_a(j, i, -amount); meaning that you add variable xj in row i with the amount (right here its negative since we are checking its larger than the minimum)
3. After reading in the nutrients, in the outer loop do: lp.set_c(j, cost); which will minimize the cost.
4. After check that the solution is feasable and output the floored value.

