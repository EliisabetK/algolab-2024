Problem: We are in a ship between asteroids, we want to shoot the asteroids with blasts of different sizes and energys, but we cant make the blasts too big, because then the bounty hunters will notice (ie if it reaches them). We need to find out if we can destroy all asteroids with given total energy e and without notifying the bounty hunters.

Solution:
1. Save asteroids, shots and bountys into vectors, add bountys into triangulation.
2. For each shot find its maximum radius by checking what isn the distance to the nearest bounty in the triangulation.
3. For each asteroidd find the distance between asteroid j and shot i and if its smaller than max radius of the shot, then add the shot to the lp. 
    * Basically its one row per asteroid with energy amounts as variables, we need to check if the sum of the energys is more than density.
    * Our LP is a equations with up to s variables, the right hand side of the equation is the density of the asteroid. The coefficents of the energys is the distance equation thingy.
    * We need to check if its bigger than density, therefore we need to multiply the coefficents and b by -1.
    * Our objective is per each i to minimize the total energy.
4. After we check if the solution is optimal and if the solution value is smaller or equal to e.

Tips:
IMPORTANT: use GMPQ because of the division in the coefficent. Also use ET, since double and long arent exact enough.