Problem:

You have a balloon in a forest. You have to move it to a suitable location for take off.
Basically you need Delaunays algorithm to check if there exists a triangle thats big enough to fit the balloon for takeoff or if the balloon can escape to infinity.

Solution:
1. Read the trees into the triangulation.
2. Then initialize a priority queue where you keep the gate widths and face handles as pairs. Iterate through the faces and for each face, if its infinite, push width infinity to the priority queue, otherwise find the circumcenter of the triangle and push the distance from the center to one of the vertices as the distance.
3. Then while the priority queue is not empty, pop the top element and get its with and face. Iterate through the three neighbours of the face, find the vertices of the original face handle and check if their faces are infinite, if they are, then set the new width to INF, if its not, find the distance between the vertices.
4. The new width is the minimum of the new width and old width. If the new width is bigger than the current neighbours width, update the neighbours width with that value and push it (width and neigbour) to the queue.
5. Then for each balloon, first check if the distance to the nearest vertex is bigger than (r+s)2, if it is not, then output "n" since the balloon cant be inflated. If it isnt, then locate the starting face that the balloon is in and check whether its width is bigger than 4 * (r+s)2, if yes, output "y", else no.
