#### Topic
Greedy

#### Explanation

Story: There are birds that form a triangle, you can only kill a bird whose birds below it are dead. Every bird has a plunge time after which it plunges. You can shoot 1 bird per second.
The goal is to find out if all the birds can be killed before they plunge.

Approach: 

1. Read in the birds vector and go through it. Assign a new killing time to the birds, which is the minimum of the parents plung time - 1 and the birds plunge time.
2. You can find the parent of the bird[i] in index floor((i-1)/2);
3. Sort the list of birds with the new values and go through it.
4. A bird is killable if the index i is greater than birds[i]. If there is a bird that is not killable, output "No" and break.
5. If all birds are killable, output yes.