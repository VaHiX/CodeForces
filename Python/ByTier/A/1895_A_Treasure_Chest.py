# Problem: CF 1895 A - Treasure Chest
# https://codeforces.com/contest/1895/problem/A

"""
Purpose: 
This code solves the problem of finding the minimum time required for Monocarp to open a treasure chest, 
given the positions of the chest, key, and Monocarp's stamina limit for carrying the chest.

Approach:
The key insight is to determine the optimal path for Monocarp:
1. If Monocarp is at or beyond the chest position, he can directly go to the chest and open it.
2. Otherwise, he needs to consider strategies involving picking up the key and carrying the chest.
   - If he can carry the chest to a point where he can pick up the key, he does so.
   - If he cannot carry the chest far enough, he needs to drop the chest early and pick up the key
     before returning to the chest.

Time Complexity: O(1) - constant time due to simple comparisons and arithmetic.
Space Complexity: O(1) - only using a fixed number of variables.
"""

t = input()
t = int(t)
for i in range(t):
    x, y, k = input().split(" ")
    x, y, k = int(x), int(y), int(k)
    if x >= y:
        # If Monocarp is already at or beyond the chest position, he just needs to go there
        print(x)
    else:
        # If he can carry the chest to a point where he can reach the key
        if x + k >= y:
            # He can carry the chest to the key's location and then open the chest
            print(y)
        else:
            # He must drop the chest before picking up the key
            # The total time is the time to reach the chest + time to go back to the key + time to return to chest
            print(y + (y - (x + k)))


# https://github.com/VaHiX/CodeForces/